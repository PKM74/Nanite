/*----------------*\
|Nanite OS         |
|Copyright (C) 2025|
|Tyler McGurrin    |
\*----------------*/
#pragma once

#include <stdint.h>

typedef struct {
    uint8_t id;
    uint16_t cylinders;
    uint16_t sectors;
    uint16_t heads;
} FLOPPY_DISK;

void Floppy_Handler();
void Floppy_Drive_Init(uint8_t drive);


/* When i Said i was Rewriting this POS i meant it */

enum FLOPPY_IO {
 
	FLOPPY_DOR		                  =	0x3f2,
	FLOPPY_MSR		                  =	0x3f4,
	FLOPPY_FIFO		                  =	0x3f5,	//data register
	FLOPPY_CTRL		                  =	0x3f7
};

enum FLOPPY_DOR_MASK {
 
	FLOPPY_DOR_MASK_DRIVE0			   =	0,	   //00000000	= here for completeness sake
	FLOPPY_DOR_MASK_DRIVE1			   =	1,	   //00000001
	FLOPPY_DOR_MASK_DRIVE2			   =	2,	   //00000010
	FLOPPY_DOR_MASK_DRIVE3			   =	3,	   //00000011
	FLOPPY_DOR_MASK_RESET			   =	4,	   //00000100
	FLOPPY_DOR_MASK_DMA			      =	8,	   //00001000
	FLOPPY_DOR_MASK_DRIVE0_MOTOR		=	16,	//00010000
	FLOPPY_DOR_MASK_DRIVE1_MOTOR		=	32,	//00100000
	FLOPPY_DOR_MASK_DRIVE2_MOTOR		=	64,	//01000000
	FLOPPY_DOR_MASK_DRIVE3_MOTOR		=	128	//10000000
};

enum FLOPPY_MSR_MASK {
 
	FLOPPY_MSR_MASK_DRIVE1_POS_MODE	=	1, 	//00000001
	FLOPPY_MSR_MASK_DRIVE2_POS_MODE	=	2,	   //00000010
	FLOPPY_MSR_MASK_DRIVE3_POS_MODE	=	4,	   //00000100
	FLOPPY_MSR_MASK_DRIVE4_POS_MODE	=	8,	   //00001000
	FLOPPY_MSR_MASK_BUSY			   =	16,	//00010000
	FLOPPY_MSR_MASK_DMA			      =	32,	//00100000
	FLOPPY_MSR_MASK_DATAIO			   =	64, 	//01000000
	FLOPPY_MSR_MASK_DATAREG		   =	128	//10000000
};

