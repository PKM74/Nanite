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

#define PORT_FLOPPY_TYPE 0x10

void Floppy_Handler()
{
    printf("IRQ 6 Called");
}





// I cannot get this to work for the life of me,
// OSDEV Wiki says its meant to be CMOS Register 0x10, which seems to be 0xFF for me...
// 0xFF, is NOT a vaild value at all...
// Basically Gonna hard-code the driver for 1.44MB Drives
// Since Nanite is only capable of running off one without modifications to the bootloader, 
// this is not an issue... but its sure as shit annoying
// Correction im stupid...

// Moved to CMOS Driver.