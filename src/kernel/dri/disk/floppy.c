/*----------------*\
|Nanite OS         |
|Copyright (C) 2025|
|Tyler McGurrin    |
\*----------------*/
#include "floppy.h"

#include <stdint.h>
#include <stdio.h>
#include <arch/i686/io.h>
#include <arch/i686/irq.h>
#include <dri/serial.h>

extern uint16_t DEBUG_COM_PORT;

volatile int FloppyIRQRecived = 0;

// Honestly dont care that most of this is hard-coded, im just done with this shit

void Floppy_Handler()
{
    // IRQ Handler
    FloppyIRQRecived = 1;
    Serial_Printf(DEBUG_COM_PORT, "Recived IRQ From Floppy Drive.\n");
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

void Floppy_Write_DOR(uint8_t command ) 
{
	// Write the DOR
	outb(FLOPPY_DOR, command);
    Serial_Printf(DEBUG_COM_PORT, "Wrote %u To Floppy DOR.\n", command);
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

void Floppy_Send_Command (uint8_t command) 
{ 
    // Wait for DOR then send command
	for(int i = 0; i < 500; i++)
		if(Floppy_Read_Status() & FLOPPY_MSR_MASK_DATAREG)
			return outb(FLOPPY_FIFO, command);
}

// LBA2CHS Lives Forever! Might move it later on tho
void Floppy_LBA2CHS(FLOPPY_DISK* disk, uint32_t lba, uint16_t* cylinderOut, uint16_t* sectorOut, uint16_t* headOut) {
    // sector = (LBA % sectors per track + 1)
    *sectorOut = lba % disk->sectors +1;

    // cylinder = (LBA / sects per track / heads)
    *cylinderOut = (lba / disk->sectors) / disk->heads;

    // head = (LBA / sects per track % heads)
    *headOut = (lba / disk->sectors) % disk->heads;
}