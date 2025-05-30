/*----------------*\
|Nanite OS         |
|Copyright (C) 2025|
|Tyler McGurrin    |
\*----------------*/
#include "floppy.h"

#include <stdint.h>
#include <util/binary.h>
#include <arch/i686/io.h>
#include <arch/i686/irq.h>

#define PORT_FLOPPY_TYPE 0x10

int Master_FDD_Detect()
{
    int Buffer;
    int FDDType;
    /* FDD Drive Values
    Value:  Drive Type:
     00h 	 no drive
     01h 	 360 KB 5.25 Drive
     02h	 1.2 MB 5.25 Drive
     03h 	 720 KB 3.5 Drive
     04h 	 1.44 MB 3.5 Drive
     05h     2.88 MB 3.5 drive*/
    Buffer = i686_inb(PORT_FLOPPY_TYPE);

    int bit = Byte_Parse(Buffer, 0); 
    int i = 1;
    while(i < 4) {
        FDDType = bit & bit;
        bit = Byte_Parse(Buffer, i);
        i++;
    }
    return FDDType;
}