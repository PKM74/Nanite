/*----------------*\
|Nanite OS         |
|Copyright (C) 2025|
|Tyler McGurrin    |
\*----------------*/
#pragma once

#define FLAG_SET(x, flag) x |= (flag)
#define FLAG_UNSET(x, flag) x &= ~(flag)

uint8_t Get_Bit(uint8_t bits, uint8_t pos);

//int Byte_Parse(int8_t byteFlag, int whichBit);