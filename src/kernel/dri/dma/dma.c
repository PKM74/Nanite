/*----------------*\
|Nanite OS         |
|Copyright (C) 2025|
|Tyler McGurrin    |
\*----------------*/
#include "dma.h"

#include <arch/i686/io.h>
#include <stdint.h>
#include <stdbool.h>

void DMA_Set_Address(uint8_t channel, uint8_t low, uint8_t high)
{
	if (channel > 8)
		return;

	uint16_t port = 0;
	switch (channel) {
		case 0: {port = DMA0_CHANNEL0_ADDR_REG; break;}
		case 1: {port = DMA0_CHANNEL1_ADDR_REG; break;}
		case 2: {port = DMA0_CHANNEL2_ADDR_REG; break;}
		case 3: {port = DMA0_CHANNEL3_ADDR_REG; break;}
		case 4: {port = DMA1_CHANNEL4_ADDR_REG; break;}
		case 5: {port = DMA1_CHANNEL5_ADDR_REG; break;}
		case 6: {port = DMA1_CHANNEL6_ADDR_REG; break;}
		case 7: {port = DMA1_CHANNEL7_ADDR_REG; break;}
	}

	outb(port, low);
	outb(port, high);
}

void DMA_Set_Count(uint8_t channel, uint8_t low, uint8_t high)
{
	if (channel > 8)
		return;

	unsigned short port = 0;
	switch (channel) {
		case 0: {port = DMA0_CHANNEL0_COUNT_REG; break;}
		case 1: {port = DMA0_CHANNEL1_COUNT_REG; break;}
		case 2: {port = DMA0_CHANNEL2_COUNT_REG; break;}
		case 3: {port = DMA0_CHANNEL3_COUNT_REG; break;}
		case 4: {port = DMA1_CHANNEL4_COUNT_REG; break;}
		case 5: {port = DMA1_CHANNEL5_COUNT_REG; break;}
		case 6: {port = DMA1_CHANNEL6_COUNT_REG; break;}
		case 7: {port = DMA1_CHANNEL7_COUNT_REG; break;}
	}
	outb(port, low);
	outb(port, high);
}

void DMA_Set_External_Page_Register(uint8_t reg, uint8_t value)
{
	if (reg > 14) return;

	unsigned short port = 0;
	switch (reg) {
		case 1: {port = DMA_PAGE_CHANNEL1_ADDRBYTE2; break;}
		case 2: {port = DMA_PAGE_CHANNEL2_ADDRBYTE2; break;}
		case 3: {port = DMA_PAGE_CHANNEL3_ADDRBYTE2; break;}
		case 4: {return;}// nothing should ever write to register 4
		case 5: {port = DMA_PAGE_CHANNEL5_ADDRBYTE2; break;}
		case 6: {port = DMA_PAGE_CHANNEL6_ADDRBYTE2; break;}
		case 7: {port = DMA_PAGE_CHANNEL7_ADDRBYTE2; break;}
	}
	outb(port, value);
}

void DMA_Set_Mode(uint8_t channel, uint8_t mode)
{
	int dma = (channel < 4) ? 0 : 1;
	int chan = (dma==0) ? channel : channel-4;

	DMA_Mask_Channel(channel);
	outb((channel < 4) ? (DMA0_MODE_REG) : DMA1_MODE_REG, chan | (mode));
	DMA_Unmask_All(dma);
}

// prepares channel for read
void DMA_Set_Read(uint8_t channel)
{
	DMA_Set_Mode(channel, DMA_MODE_READ_TRANSFER | DMA_MODE_TRANSFER_SINGLE | DMA_MODE_MASK_AUTO);
}

// prepares channel for write
void DMA_Set_Write(uint8_t channel)
{
	DMA_Set_Mode(channel, DMA_MODE_WRITE_TRANSFER | DMA_MODE_TRANSFER_SINGLE | DMA_MODE_MASK_AUTO);
}

void DMA_Mask_Channel(uint8_t channel)
{
	if (channel <= 4)
		outb(DMA0_CHANNELMASK_REG, (1 << (channel-1)));
	else
		outb(DMA1_CHANNELMASK_REG, (1 << (channel-5)));
}

void DMA_Unmask_Channel(uint8_t channel)
{
	if (channel <= 4)
		outb(DMA0_CHANNELMASK_REG, channel);
	else
		outb(DMA1_CHANNELMASK_REG, channel);
}

void DMA_Unmask_All(int dma)
{
	outb(DMA1_UNMASK_ALL_REG, 0xff);
}

// Groan...

void DMA_Reset_Flipflop(int dma)
{
	if (dma < 2)
		return;
	outb( (dma==0) ? DMA0_CLEARBYTE_FLIPFLOP_REG : DMA1_CLEARBYTE_FLIPFLOP_REG, 0xff);
}

void DMA_Reset(int dma)
{
	outb(DMA0_TEMP_REG, 0xff);
}

bool DMA_Init_Floppy(uint8_t* buffer, unsigned length)
{
   union{
      uint8_t byte[4];//Lo[0], Mid[1], Hi[2]
      unsigned long l;
   }a, c;

   a.l=(unsigned)buffer;
   c.l=(unsigned)length-1;

   //Check for buffer issues
   if ((a.l >> 24) || (c.l >> 16) || (((a.l & 0xffff)+c.l) >> 16)){
      return false;
   }

   DMA_Reset(1);
   DMA_Mask_Channel(FLOPPY_DMA_CHANNEL );//Mask channel 2
   DMA_Reset_Flipflop( 1 );//Flipflop reset on DMA 1

   DMA_Set_Address(FLOPPY_DMA_CHANNEL, a.byte[0],a.byte[1]);//Buffer address
   DMA_Reset_Flipflop(1);//Flipflop reset on DMA 1

   DMA_Set_Count(FLOPPY_DMA_CHANNEL, c.byte[0],c.byte[1]);//Set count
   DMA_Set_Read(FLOPPY_DMA_CHANNEL );

   DMA_Unmask_All(1);//Unmask channel 2

   return true;
}
