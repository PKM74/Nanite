/*----------------*\
|Nanite OS         |
|Copyright (C) 2025|
|Tyler McGurrin    |
\*----------------*/
#include "floppy.h"

#include <stdint.h>
#include <stdio.h>
#include <util/binary.h>
#include <arch/i686/io.h>
#include <arch/i686/irq.h>

#define PORT_FLOPPY_TYPE 0x10

void Floppy_Handler()
{

}





// I cannot get this to work for the life of me,
// OSDEV Wiki says its meant to be CMOS Register 0x10, which seems to be 0xFF for me...
// 0xFF, is NOT a vaild value at all...
// Basically Gonna hard-code the driver for 1.44MB Drives
// Since Nanite is only capable of running off one without modifications to the bootloader, 
// this is not an issue... but its sure as shit annoying
int Master_FDD_Detect()
{
    uint8_t Buffer;
    int FDDType;
    int bit1, bit2, bit3, bit4;
    /* FDD Drive Values
    Value:  Drive Type:
     00h 	 no drive
     01h 	 360 KB 5.25 Drive
     02h	 1.2 MB 5.25 Drive
     03h 	 720 KB 3.5 Drive
     04h 	 1.44 MB 3.5 Drive
     05h     2.88 MB 3.5 drive*/
    Buffer = i686_inb(PORT_FLOPPY_TYPE);

    // bit1 = Byte_Parse(Buffer, 0);
    // bit2 = Byte_Parse(Buffer, 1);
    // bit3 = Byte_Parse(Buffer, 2);
    // bit4 = Byte_Parse(Buffer, 3);
    // printf("Bits: %d, %d, %d, %d\n", bit1, bit2, bit3, bit4);
    printf("Buffer: %s", Buffer);
    // int bit = Byte_Parse(Buffer, 0); 
    // int i = 1;
    // while(i < 4) {
    //     FDDType = bit & bit;
    //     bit = Byte_Parse(Buffer, i);
    //     i++;
    //     printf("MFDD Bit %d: %d\n", i, bit);
    // }
    FDDType = bit1 & bit2 & bit3 & bit4;
    return FDDType;
}

int Slave_FDD_Detect()
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

    int bit = Byte_Parse(Buffer, 3); 
    int i = 4;
    while(i < 8) {
        FDDType = bit & bit;
        bit = Byte_Parse(Buffer, i);
        i++;
        printf("SFDD Bit %d: %d\n", i, bit);
    }
    return FDDType;
}