/*----------------*\
|Nanite OS         |
|Copyright (C) 2025|
|Tyler McGurrin    |
\*----------------*/
#pragma once

#include <stdint.h>

void Floppy_Handler();
void Floppy_Drive_Start(uint8_t drive);


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
   DOR_MOTD                         = 0x80,
   DOR_MOTC                         = 0x40,
   DOR_MOTB                         = 0x20,
   DOR_MOTA                         = 0x10,
   DOR_IRQ                          = 0x08,
   DOR_RESET                        = 0x04,
   DOR_DSEL1                        = 0x01
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
   MSR_RQM                          = 0x80, // Set if it's OK (or mandatory) to exchange bytes with the FIFO IO port
   MSR_DIO                          = 0x40, // Set if FIFO IO port expects an IN opcode
   MSR_NDMA                         = 0x20, // Set in Execution phase of PIO mode read/write commands only.
   MSR_CB                           = 0x10, // Command Busy: set when command byte received, cleared at end of Result phase
   MSR_ACTD                         = 0x08, // Drive 3 is seeking
   MSR_ACTC                         = 0x04, // Drive 2 is seeking
   MSR_ACTB                         = 0x02, // Drive 1 is seeking
   MSR_ACTA                         = 0x01, // Drive 0 is seeking
};

// Bottom 2 Bits of DSR match CCR
enum FloppyRegisters
{
   STATUS_REGISTER_A                = 0x3F0, // read-only
   STATUS_REGISTER_B                = 0x3F1, // read-only
   DIGITAL_OUTPUT_REGISTER          = 0x3F2,
   TAPE_DRIVE_REGISTER              = 0x3F3, // Basically Useless, unless for some reason you have a tape drive
   MAIN_STATUS_REGISTER             = 0x3F4, // read-only
   DATARATE_SELECT_REGISTER         = 0x3F4, // write-only
   DATA_FIFO                        = 0x3F5,
   DIGITAL_INPUT_REGISTER           = 0x3F7, // read-only
   CONFIGURATION_CONTROL_REGISTER   = 0x3F7  // write-only
};

enum FloppyCommands
{
   READ_TRACK =                 2,	// generates IRQ6
   SPECIFY =                    3,      // * set drive parameters
   SENSE_DRIVE_STATUS =         4,
   WRITE_DATA =                 5,      // * write to the disk
   READ_DATA =                  6,      // * read from the disk
   RECALIBRATE =                7,      // * seek to cylinder 0
   SENSE_INTERRUPT =            8,      // * ack IRQ6, get status of last command
   WRITE_DELETED_DATA =         9,
   READ_ID =                    10,	// generates IRQ6
   READ_DELETED_DATA =          12,
   FORMAT_TRACK =               13,     // *
   DUMPREG =                    14,
   SEEK =                       15,     // * seek both heads to cylinder X
   VERSION =                    16,	// * used during initialization, once
   SCAN_EQUAL =                 17,
   PERPENDICULAR_MODE =         18,	// * used during initialization, once, maybe
   CONFIGURE =                  19,     // * set controller parameters
   LOCK =                       20,     // * protect controller params from a reset
   VERIFY =                     22,
   SCAN_LOW_OR_EQUAL =          25,
   SCAN_HIGH_OR_EQUAL =         29
};