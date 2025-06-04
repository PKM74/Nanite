/*----------------*\
|Nanite OS         |
|Copyright (C) 2025|
|Tyler McGurrin    |
\*----------------*/
#include "floppy.h"

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <arch/i686/io.h>
#include <arch/i686/irq.h>
#include <dri/serial.h>

extern uint16_t DEBUG_COM_PORT;

volatile int FloppyIRQRecived = 0;

int _CurrentDrive;

// Honestly dont care that most of this is hard-coded, im just done with this shit

void Floppy_Handler()
{
    // IRQ Handler
    FloppyIRQRecived = 1;
    Serial_Printf(DEBUG_COM_PORT, "FLOPPY:> Recived IRQ From FDC.\n");
}

void Floppy_IRQ_Wait()
{
    // Waits until IRQ is recived
    while(FloppyIRQRecived == 0);
    FloppyIRQRecived = 0;
}

// init DMA to use phys addr 1k-64k
void Floppy_Init_DMA() 
{
	outb(0x0a, 0x06);	//mask dma channel 2
	outb(0xd8, 0xff);	//reset master flip-flop
	outb(0x04, 0);     //address=0x1000 
	outb(0x04, 0x10);
	outb(0xd8, 0xff);  //reset master flip-flop
	outb(0x05, 0xff);  //count to 0x23ff (number of bytes in a 3.5" floppy disk track)
	outb(0x05, 0x23);
	outb(0x80, 0);     //external page register = 0
	outb(0x0a, 0x02);  //unmask dma channel 2
}
 
// Prep the DMA for read transfer
void Floppy_DMA_Read() 
{
	outb(0x0a, 0x06); //mask dma channel 2
	outb(0x0b, 0x56); //single transfer, address increment, autoinit, read, channel 2
	outb(0x0a, 0x02); //unmask dma channel 2
}
 
// Prep DMA for write transfer
void Floppy_DMA_Write() 
{
	outb(0x0a, 0x06); //mask dma channel 2
	outb(0x0b, 0x5a); //single transfer, address increment, autoinit, write, channel 2
	outb(0x0a, 0x02); //unmask dma channel 2
}

void Floppy_Write_DOR(uint8_t value) 
{
	// Write the DOR
	outb(FLOPPY_DOR, value);
    Serial_Printf(DEBUG_COM_PORT, "FLOPPY:> Wrote %u To DOR.\n", value);
}

void Floppy_Write_CCR(uint8_t value)
{ 
	// write the configuation control
	outb (FLOPPY_CTRL, value);
	Serial_Printf(DEBUG_COM_PORT, "FLOPPY:> Wrote %u To CCR.\n", value);
}

uint8_t Floppy_Read_Status()
{
	// Returns MSR (simple innit?
	return inb(FLOPPY_MSR);
}

int Floppy_Check_Busy()
{
    // Explains Itself.
    if (Floppy_Read_Status() & FLOPPY_MSR_MASK_BUSY)
    return 1;
    else
    return 0;
}

void Floppy_Send_Command(uint8_t command)
{ 
    // Wait for DOR then send command
	Serial_Printf(DEBUG_COM_PORT, "FLOPPY:> Sending Command %u To Drive\n", command);
	for(int i = 0; i < 500; i++)
		if(Floppy_Read_Status() & FLOPPY_MSR_MASK_DATAREG)
			return outb(FLOPPY_FIFO, command);
}

uint8_t Floppy_Read_Data()
{ 
	// same as above function but returns data register for reading
	for(int i = 0; i < 500; i++)
		if( Floppy_Read_Status() & FLOPPY_MSR_MASK_DATAREG)
			return inb(FLOPPY_FIFO);
}

// Complicated ass driver.
// I mean... could be worse?
void Floppy_Read_Sector_CHS(uint8_t head, uint8_t track, uint8_t sector) 
{
	uint32_t st0, cyl;
 
	// set the DMA for read transfer
	Floppy_DMA_Read();
 
	// read in a sector
	Floppy_Send_Command(FLOPPY_CMD_READ_SECT | FLOPPY_CMD_EXT_MULTITRACK | FLOPPY_CMD_EXT_SKIP | FLOPPY_CMD_EXT_DENSITY);
	Floppy_Send_Command(head << 2 | _CurrentDrive);
	Floppy_Send_Command(track);
	Floppy_Send_Command(head);
	Floppy_Send_Command(sector);
	Floppy_Send_Command(FLOPPY_SECTOR_DTL_512);
	Floppy_Send_Command((( sector + 1 ) >= FLOPPY_SECTORS_PER_TRACK ) ? FLOPPY_SECTORS_PER_TRACK : sector + 1);
	Floppy_Send_Command(FLOPPY_GAP3_LENGTH_3_5);
	Floppy_Send_Command(0xff);
 
	// wait for irq
	Floppy_IRQ_Wait();
 
	// read status info
	for (int j=0; j<7; j++) Floppy_Read_Data();
 
	// let Floppy Controller know we handled interrupt
	Floppy_Check_INT(&st0,&cyl);
}

void Floppy_Drive_Data(uint32_t stepr, uint32_t loadt, uint32_t unloadt, bool dma)
{ 
	uint32_t data = 0;

	Floppy_Send_Command(FLOPPY_CMD_SPECIFY);
 
	data = ( (stepr & 0xf) << 4) | (unloadt & 0xf);
	Floppy_Send_Command(data);
 
	data = (loadt) << 1 | (dma==true) ? 1 : 0;
	Floppy_Send_Command(data);
}

int Floppy_Calibrate(uint32_t drive)
{
	uint32_t st0, cyl;
 
	if (drive >= 4)
		return -2;
 
	// turn on the motor
	Floppy_Motor_Control(true);
 
	for (int i = 0; i < 10; i++) {
 
		// send command
		Floppy_Send_Command(FLOPPY_CMD_CALIBRATE);
		Floppy_Send_Command(drive);
		Floppy_IRQ_Wait();
		Floppy_Check_INT(&st0, &cyl);
 
		// did we fine cylinder 0? if so, we are done
		if (!cyl) {
 
			Floppy_Motor_Control(false);
			return 0;
		}
	}
 
	Floppy_Motor_Control(false);
	return -1;
}

void Floppy_Check_INT(uint32_t* st0, uint32_t* cyl1)
{
	// Checks Drive Info Post-Interupt
	Floppy_Send_Command(FLOPPY_CMD_CHECK_INT);
 
	*st0 = Floppy_Read_Data();
	*cyl1 = Floppy_Read_Data();
}

int Floppy_Seek(uint32_t cyl, uint32_t head)
{ 
	uint32_t st0, cyl0;
 
	if (_CurrentDrive >= 4)
		return -1;
 
	for (int i = 0; i < 10; i++ ) {
 
		// send the command
		Floppy_Send_Command(FLOPPY_CMD_SEEK);
		Floppy_Send_Command((head) << 2 | _CurrentDrive);
		Floppy_Send_Command(cyl);
 
		// wait for IRQ
		Floppy_IRQ_Wait();
		Floppy_Check_INT(&st0,&cyl0);
 
		// found the cylinder?
		if ( cyl0 == cyl)
			return 0;
	}
 
	return -1;
}

void Floppy_Disable_Controller() 
{ 
	Floppy_Write_DOR(0);
}

void Floppy_Enable_Controller()
{ 
	Floppy_Write_DOR(FLOPPY_DOR_MASK_RESET | FLOPPY_DOR_MASK_DMA);
}

void Floppy_Reset() 
{ 
	uint32_t st0, cyl;
 
	// reset the controller
	Floppy_Disable_Controller();
	Floppy_Enable_Controller();
	Floppy_IRQ_Wait();
 
	// send CHECK_INT/SENSE INTERRUPT command to all drives
	for (int i=0; i<4; i++)
		Floppy_Check_INT(&st0,&cyl);
 
	// transfer speed 500kb/s
	Floppy_Write_CCR(0);
 
	// pass mechanical drive info. steprate=3ms, unload time=240ms, load time=16ms
	Floppy_Drive_Data(3,16,240,true);
 
	// calibrate the disk
	Floppy_Calibrate( _CurrentDrive );
}

void Floppy_Init()
{
	// initialize the DMA
	Floppy_Init_DMA();
 
	// reset the fdc
	Floppy_Reset();
 
	// set drive information
	Floppy_Drive_Data(13, 1, 0xf, true);
}

void Floppy_LBA2CHS(int lba,int *head,int *track,int *sector)
{
   *head = ( lba % ( FLOPPY_SECTORS_PER_TRACK * 2 ) ) / ( FLOPPY_SECTORS_PER_TRACK );
   *track = lba / ( FLOPPY_SECTORS_PER_TRACK * 2 );
   *sector = lba % FLOPPY_SECTORS_PER_TRACK + 1;
}

uint8_t* Floppy_Read_Sector(int sectorLBA)
{	
	if (_CurrentDrive >= 4)
		return 0;
	
	// convert LBA sector to CHS
	int head=0, track=0, sector=1;
	Floppy_LBA2CHS(sectorLBA, &head, &track, &sector);
	
	// turn motor on and seek to track
	Floppy_Motor_Control(true);
	if (Floppy_Seek(track, head) != 0)
		return 0;
	
	// read sector and turn motor off
	Floppy_Read_Sector_CHS(head, track, sector);
	Floppy_Motor_Control(false);
	
	// this is a bit hackish, but ofc i dont care. (also still need to implement DMA lolololololol)
	// return (uint8_t*) DMA_BUFFER;
}

void Floppy_Motor_Control(bool enable)
{
	if(enable == true) {
		outb (FLOPPY_DOR, FLOPPY_DOR_MASK_DRIVE0_MOTOR | FLOPPY_DOR_MASK_RESET);
		Serial_Printf(DEBUG_COM_PORT, "FLOPPY:> Starting FDD Motor.\n");
		int i;
		while(i >= 500) i++;
	}
	else {
		Floppy_Reset();
		Serial_Printf(DEBUG_COM_PORT, "FLOPPY:> Stopping FDD Motor, FDC Reseting.\n");
	}

}
