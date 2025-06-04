/*----------------*\
|Nanite OS         |
|Copyright (C) 2025|
|Tyler McGurrin    |
\*----------------*/
#include "dma.h"

void DMA_Set_Address(uint8_t channel, uint8_t low, uint8_t high)
{
	if ( channel > 8 )
		return;

	unsigned short port = 0;
	switch ( channel ) {
		case 0: {port = DMA0_CHANNNEL0_ADDR_REG; break;}
		case 1: {port = DMA0_CHANNNEL1_ADDR_REG; break;}
		case 2: {port = DMA0_CHANNNEL2_ADDR_REG; break;}
		case 3: {port = DMA0_CHANNNEL3_ADDR_REG; break;}
		case 4: {port = DMA1_CHANNNEL4_ADDR_REG; break;}
		case 5: {port = DMA1_CHANNNEL5_ADDR_REG; break;}
		case 6: {port = DMA1_CHANNNEL6_ADDR_REG; break;}
		case 7: {port = DMA1_CHANNNEL7_ADDR_REG; break;}
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
		case 0: {port = DMA0_CHANNNEL0_COUNT_REG; break;}
		case 1: {port = DMA0_CHANNNEL1_COUNT_REG; break;}
		case 2: {port = DMA0_CHANNNEL2_COUNT_REG; break;}
		case 3: {port = DMA0_CHANNNEL3_COUNT_REG; break;}
		case 4: {port = DMA1_CHANNNEL4_COUNT_REG; break;}
		case 5: {port = DMA1_CHANNNEL5_COUNT_REG; break;}
		case 6: {port = DMA1_CHANNNEL6_COUNT_REG; break;}
		case 7: {port = DMA1_CHANNNEL7_COUNT_REG; break;}
	}
	outb(port, low);
	outb(port, high);
}

void DMA_Set_External_Page_Register(uint8_t register, uint8_t value)
{
	if (register > 14)
		return;

	unsigned short port = 0;
	switch (register) {
		case 1: {port = DMA_PAGE_CHAN1_ADDRBYTE2; break;}
		case 2: {port = DMA_PAGE_CHAN2_ADDRBYTE2; break;}
		case 3: {port = DMA_PAGE_CHAN3_ADDRBYTE2; break;}
		case 4: {return;}// nothing should ever write to register 4
		case 5: {port = DMA_PAGE_CHAN5_ADDRBYTE2; break;}
		case 6: {port = DMA_PAGE_CHAN6_ADDRBYTE2; break;}
		case 7: {port = DMA_PAGE_CHAN7_ADDRBYTE2; break;}
	}
	outb(port, value);
}

void DMA_Set_Mode(uint8_t channel, uint8_t mode)
{
	int dma = (channel < 4) ? 0 : 1;
	int chan = (dma==0) ? channel : channel-4;

	dma_mask_channel (channel);
	outportb ( (channel < 4) ? (DMA0_MODE_REG) : DMA1_MODE_REG, chan | (mode) );
	dma_unmask_all ( dma );
}

// prepares channel for read
void DMA_Set_Read(uint8_t channel)
{
	DMA_Set_Mode(channel, DMA_MODE_READ_TRANSFER | DMA_MODE_TRANSFER_SINGLE | DMA_MODE_MASK_AUTO);
}

//! prepares channel for write
void DMA_Set_Write(uint8_t channel)
{
	DMA_Set_Mode(channel, DMA_MODE_WRITE_TRANSFER | DMA_MODE_TRANSFER_SINGLE | DMA_MODE_MASK_AUTO);
}
