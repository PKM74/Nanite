/*----------------*\
|Nanite OS         |
|Copyright (C) 2025|
|Tyler McGurrin    |
\*----------------*/
#pragma once

#include <stdint.h>

// You can really only trust the first and 2nd COM port addresses...
// fun.
enum COMPorts
{
    COM1_PORT               = 0x3F8,
    COM2_PORT               = 0x2F8,
    COM3_PORT               = 0x3E8,
    COM4_PORT               = 0x2E8,
    COM5_PORT               = 0x5F8,
    COM6_PORT               = 0x4F8,
    COM7_PORT               = 0x5E8,
    COM8_PORT               = 0x4E8
};

void COM1_Serial_Handler();
int Serial_Received(uint16_t COM_Port);
char Read_Serial(uint16_t COM_Port);
int Serial_Transmit_Empty(uint16_t COM_Port);
void Write_Serial(uint16_t COM_Port, char a);
int Serial_Init(uint16_t COM_Port, int Baud);
void Serial_Printf(uint16_t COM_Port, const char* fmt, ...);