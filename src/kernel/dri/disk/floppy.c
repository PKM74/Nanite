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

void Floppy_Handler()
{
    printf("IRQ 6 Called");
}

void Floppy_Drive_Start(uint8_t drive)
{
    uint8_t Buffer;
    if (drive == 1) Buffer = 0 && DOR_DSEL1 && DOR_RESET && DOR_MOTA && 0 && 0 && 0;
    if (drive == 2) Buffer = 0 && DOR_DSEL1 && DOR_RESET && 0 && DOR_MOTB && 0 && 0;
}