/*----------------*\
|Nanite OS         |
|Copyright (C) 2024|
|Tyler McGurrin    |
\*----------------*/
#pragma once

#include <stdint.h>
void PIC_Configure(uint8_t offsetPic1, uint8_t offsetPic2);
void PIC_SendEndOfInterrupt(int irq);
void PIC_Disable();
void PIC_Mask(int irq);
void PIC_Unmask(int irq);
uint16_t PIC_ReadIRQRequestRegister();
uint16_t PIC_ReadInServiceRegister();