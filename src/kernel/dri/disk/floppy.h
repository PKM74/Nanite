/*----------------*\
|Nanite OS         |
|Copyright (C) 2025|
|Tyler McGurrin    |
\*----------------*/
#pragma once

#include <stdint.h>
#include <stdbool.h>

#define FLOPPY_SECTORS_PER_TRACK 18 // Yes this makes it ONLY work with 3.5 inch drives, honestly i dont give a fuck

typedef struct {
    uint8_t id;
    uint16_t cylinders;
    uint16_t sectors;
    uint16_t heads;
} FLOPPY_DISK;

void Floppy_Handler();
void Floppy_Drive_Init(uint8_t drive);
void Floppy_IRQ_Wait();
void Floppy_Init_DMA();
void Floppy_DMA_Read();
void Floppy_DMA_Write();
void Floppy_Write_DOR(uint8_t value);
void Floppy_Write_CCR(uint8_t value);
void Floppy_Send_Command(uint8_t command);
void Floppy_LBA2CHS(int lba,int *head,int *track,int *sector);
void Floppy_Read_Sector_CHS(uint8_t head, uint8_t track, uint8_t sector);
void Floppy_Drive_Data(uint32_t stepr, uint32_t loadt, uint32_t unloadt, bool dma);
void Floppy_Check_INT(uint32_t* st0, uint32_t* cyl1);
void Floppy_Disable_Controller();
void Floppy_Enable_Controller();
void Floppy_Reset();
void Floppy_Init();
void Floppy_Motor_Control(bool enable);
uint8_t Floppy_Read_Status();
uint8_t Floppy_Read_Data();
uint8_t* Floppy_Read_Sector(int sectorLBA);
int Floppy_Check_Busy();
int Floppy_Calibrate(uint32_t drive);
int Floppy_Seek(uint32_t cyl, uint32_t head);

/* When i Said i was Rewriting this POS i meant it */

enum FLOPPY_IO {
 
	FLOPPY_DOR		                 	= 0x3f2,
	FLOPPY_MSR		                 	= 0x3f4,
	FLOPPY_FIFO		                 	= 0x3f5,	//data register
	FLOPPY_CTRL		                 	= 0x3f7
};

enum FLOPPY_DOR_MASK {
 
	FLOPPY_DOR_MASK_DRIVE0			    = 0,	    //00000000
	FLOPPY_DOR_MASK_DRIVE1			    = 1,	    //00000001
	FLOPPY_DOR_MASK_DRIVE2			    = 2,	    //00000010
	FLOPPY_DOR_MASK_DRIVE3			    = 3,	    //00000011
	FLOPPY_DOR_MASK_RESET			    = 4,	    //00000100
	FLOPPY_DOR_MASK_DMA			        = 8,	    //00001000
	FLOPPY_DOR_MASK_DRIVE0_MOTOR		= 16,		//00010000
	FLOPPY_DOR_MASK_DRIVE1_MOTOR		= 32,		//00100000
	FLOPPY_DOR_MASK_DRIVE2_MOTOR		= 64,		//01000000
	FLOPPY_DOR_MASK_DRIVE3_MOTOR		= 128		//10000000
};

enum FLOPPY_MSR_MASK {
 
	FLOPPY_MSR_MASK_DRIVE1_POS_MODE		= 1, 		//00000001
	FLOPPY_MSR_MASK_DRIVE2_POS_MODE		= 2,	    //00000010
	FLOPPY_MSR_MASK_DRIVE3_POS_MODE		= 4,	    //00000100
	FLOPPY_MSR_MASK_DRIVE4_POS_MODE		= 8,	    //00001000
	FLOPPY_MSR_MASK_BUSY			    = 16,		//00010000
	FLOPPY_MSR_MASK_DMA			      	= 32,		//00100000
	FLOPPY_MSR_MASK_DATAIO			    = 64, 		//01000000
	FLOPPY_MSR_MASK_DATAREG		   		= 128		//10000000
};

// Yes i know i know 0b numbers are nonstandard (fuck off)
enum FLOPPY_CCR_SPEEDS {

    FLOPPY_CCR_SPEED_500K 				= 0b00,
    FLOPPY_CCR_SPEED_250K 				= 0b10,
    FLOPPY_CCR_SPEED_300K 				= 0b01,
    FLOPPY_CCR_SPEED_1M 				= 0b11
};

enum FLOPPY_CMD {
	
	FLOPPY_CMD_READ_TRACK				= 2,
	FLOPPY_CMD_SPECIFY					= 3,
	FLOPPY_CMD_CHECK_STAT				= 4,
	FLOPPY_CMD_WRITE_SECT				= 5,
	FLOPPY_CMD_READ_SECT				= 6,
	FLOPPY_CMD_CALIBRATE				= 7,
	FLOPPY_CMD_CHECK_INT				= 8,
	FLOPPY_CMD_WRITE_DEL_S				= 9,
	FLOPPY_CMD_READ_ID_S				= 0xa,
	FLOPPY_CMD_READ_DEL_S				= 0xc,
	FLOPPY_CMD_FORMAT_TRACK				= 0xd,
	FLOPPY_CMD_SEEK						= 0xf
};

enum FLOPPY_CMD_EXT {
 
	FLOPPY_CMD_EXT_SKIP					= 0x20,		//00100000
	FLOPPY_CMD_EXT_DENSITY				= 0x40,		//01000000
	FLOPPY_CMD_EXT_MULTITRACK			= 0x80		//10000000
};

enum FLOPPY_GAP3_LENGTH {
 
	FLOPPY_GAP3_LENGTH_STD				= 42,
	FLOPPY_GAP3_LENGTH_5_14				= 32,
	FLOPPY_GAP3_LENGTH_3_5				= 27
};

enum FLOPPY_SECTOR_DTL {
	FLOPPY_SECTOR_DTL_128				= 0,
	FLOPPY_SECTOR_DTL_256				= 1,
	FLOPPY_SECTOR_DTL_512				= 2,
	FLOPPY_SECTOR_DTL_1024				= 4
};