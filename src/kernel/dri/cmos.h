/*----------------*\
|Nanite OS         |
|Copyright (C) 2025|
|Tyler McGurrin    |
\*----------------*/
#pragma once

#include <stdint.h>

void CMOS_RTC_Handler();
int Master_FDD_Detect();
int Slave_FDD_Detect();
uint8_t Read_CMOS(uint8_t Register);

enum CMOSRegisters
{
    CMOS_Floppy_Register                = 0x10
};

/* RTC Registers
Register  Contents            Range
 0x00      Seconds             0–59
 0x02      Minutes             0–59
 0x04      Hours               0–23 in 24-hour mode, 
                               1–12 in 12-hour mode, highest bit set if pm
 0x06      Weekday             1–7, Sunday = 1
 0x07      Day of Month        1–31
 0x08      Month               1–12
 0x09      Year                0–99
 0x32      Century (maybe)     19–20?
 0x0A      Status Register A
 0x0B      Status Register B

*/