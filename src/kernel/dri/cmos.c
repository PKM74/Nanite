/*----------------*\
|Nanite OS         |
|Copyright (C) 2025|
|Tyler McGurrin    |
\*----------------*/
#include "cmos.h"

#include <stdio.h>
#include <stdint.h>

#include <arch/i686/io.h>
#include <arch/i686/irq.h>

#include <util/binary.h>

#define CMOS_ADDPORT 0x70
#define CMOS_DATAPORT 0x71

int CMOS_Timer;

void CMOS_RTC_Handler()
{
    outb(0x70, 0x0C);	// select register C
    inb(0x71);		    // just throw away contents
    CMOS_Timer++;
}

void Write_CMOS(uint8_t Register)
{

}

uint8_t Read_CMOS(uint8_t Register)
{   
   uint8_t data;
   outb(CMOS_ADDPORT, Register);
   data = inb(CMOS_DATAPORT);
   return data;
}

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
    Buffer = BCD2BIN(Read_CMOS(CMOS_Floppy_Register));

    int bit = Get_Bit(Buffer, 1); 
    int i = 2;
    while(i < 5) {
        FDDType = bit & bit;
        bit = Get_Bit(Buffer, i);
        i++;
    }
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
    Buffer = BCD2BIN(Read_CMOS(CMOS_Floppy_Register));

    int bit = Get_Bit(Buffer, 4); 
    int i = 5;
    while(i < 9) {
        FDDType = bit & bit;
        bit = Get_Bit(Buffer, i);
        i++;
    }
    return FDDType;
}
