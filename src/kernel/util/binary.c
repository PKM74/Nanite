/*----------------*\
|Nanite OS         |
|Copyright (C) 2025|
|Tyler McGurrin    |
\*----------------*/

#include <stdint.h>

uint8_t Get_Bit(uint8_t bits, uint8_t pos)
{
   return (bits >> pos) & 0x01;
}

// int Byte_Parse(int8_t byteFlag, int whichBit)
// {
//     if (whichBit > 0 && whichBit <= 8)
//         return (byteFlag & (1<<(whichBit-1)));
//     else
//         return 0;
// }