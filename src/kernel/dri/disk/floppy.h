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

void FLPDSK_Handler();
void FLPDSK_Drive_Init(uint8_t drive);




/* DOR Command Table
Mnemonic bit number 	value 	meaning/usage
   MOTD 	7 	0x80 	Set to turn drive 3's motor ON
   MOTC 	6 	0x40 	Set to turn drive 2's motor ON
   MOTB 	5 	0x20 	Set to turn drive 1's motor ON
   MOTA 	4 	0x10 	Set to turn drive 0's motor ON
   IRQ 	3 	8 	Set to enable IRQs and DMA
   RESET 2 	4 	Clear = enter reset mode, Set = normal operation
   DSEL1 and 0 	0, 1 	3 	"Select" drive number for next access 
*/
enum FloppyDORBitflags
{
   FLOPPY_DOR_MOTD                         = 0x80,
   FLOPPY_DOR_MOTC                         = 0x40,
   FLOPPY_DOR_MOTB                         = 0x20,
   FLOPPY_DOR_MOTA                         = 0x10,
   FLOPPY_DOR_IRQ                          = 0x08,
   FLOPPY_DOR_RESET                        = 0x04,
   FLOPPY_DOR_DSEL1                        = 0x01
};
/* MSR Commands
Mnemonic 	Bit Value
   RQM 	   7 	 0x80 	
   DIO 	   6 	 0x40 	
   NDMA 	   5 	 0x20 	
   CB 	   4 	 0x10 	
   ACTD 	   3 	 8 	   
   ACTC 	   2 	 4 	   
   ACTB 	   1 	 2 	   
   ACTA 	   0 	 1 	    
*/
enum FloppyMSRBitflags
{
   FLOPPY_MSR_RQM                          = 0x80, // Set if it's OK (or mandatory) to exchange bytes with the FIFO IO port
   FLOPPY_MSR_DIO                          = 0x40, // Set if FIFO IO port expects an IN opcode
   FLOPPY_MSR_NDMA                         = 0x20, // Set in Execution phase of PIO mode read/write commands only.
   FLOPPY_MSR_CB                           = 0x10, // Command Busy: set when command byte received, cleared at end of Result phase
   FLOPPY_MSR_ACTD                         = 0x08, // Drive 3 is seeking
   FLOPPY_MSR_ACTC                         = 0x04, // Drive 2 is seeking
   FLOPPY_MSR_ACTB                         = 0x02, // Drive 1 is seeking
   FLOPPY_MSR_ACTA                         = 0x01, // Drive 0 is seeking
};

// Bottom 2 Bits of DSR match CCR
enum FloppyRegisters
{
   FLOPPY_STATUS_REGISTER_A                = 0x3F0, // read-only
   FLOPPY_STATUS_REGISTER_B                = 0x3F1, // read-only
   FLOPPY_DIGITAL_OUTPUT_REGISTER          = 0x3F2,
   FLOPPY_TAPE_DRIVE_REGISTER              = 0x3F3, // Basically Useless, unless for some reason you have a tape drive
   FLOPPY_MAIN_STATUS_REGISTER             = 0x3F4, // read-only
   FLOPPY_DATARATE_SELECT_REGISTER         = 0x3F4, // write-only
   FLOPPY_DATA_FIFO                        = 0x3F5,
   FLOPPY_DIGITAL_INPUT_REGISTER           = 0x3F7, // read-only
   FLOPPY_CONFIGURATION_CONTROL_REGISTER   = 0x3F7  // write-only
};

enum FloppyCommands
{
   FLOPPY_READ_TRACK =                 2,	// generates IRQ6
   FLOPPY_SPECIFY =                    3,      // * set drive parameters
   FLOPPY_SENSE_DRIVE_STATUS =         4,
   FLOPPY_WRITE_DATA =                 5,      // * write to the disk
   FLOPPY_READ_DATA =                  6,      // * read from the disk
   FLOPPY_RECALIBRATE =                7,      // * seek to cylinder 0
   FLOPPY_SENSE_INTERRUPT =            8,      // * ack IRQ6, get status of last command
   FLOPPY_WRITE_DELETED_DATA =         9,
   FLOPPY_READ_ID =                    10,	// generates IRQ6
   FLOPPY_READ_DELETED_DATA =          12,
   FLOPPY_FORMAT_TRACK =               13,     // *
   FLOPPY_DUMPREG =                    14,
   FLOPPY_SEEK =                       15,     // * seek both heads to cylinder X
   FLOPPY_VERSION =                    16,	// * used during initialization, once
   FLOPPY_SCAN_EQUAL =                 17,
   FLOPPY_PERPENDICULAR_MODE =         18,	// * used during initialization, once, maybe
   FLOPPY_CONFIGURE =                  19,     // * set controller parameters
   FLOPPY_LOCK =                       20,     // * protect controller params from a reset
   FLOPPY_VERIFY =                     22,
   FLOPPY_SCAN_LOW_OR_EQUAL =          25,
   FLOPPY_SCAN_HIGH_OR_EQUAL =         29
};