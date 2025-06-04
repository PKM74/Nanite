/*----------------*\
|Nanite OS         |
|Copyright (C) 2025|
|Tyler McGurrin    |
\*----------------*/
#pragma once

#include <stdint.h>
#include <stdbool.h>

void Keyboard_Handler();
void Keyboard_Init();
void Keyboard_Reset_System();
void Keyboard_Enable();
void Keyboard_Disable();
void Keyboard_Set_Lock_LEDs(bool num, bool caps, bool scroll);
void Keyboard_Encoder_Send_Command(uint8_t command);
void Keyboard_Controller_Send_Command(uint8_t command);
uint8_t Keyboard_Controller_Status();
uint8_t Keyboard_Read_Encoder_Buffer();
bool Keyboard_Self_Test();



enum KEYBOARD_ENCODER_IO {

	KEYBOARD_ENC_INPUT_BUF				= 0x60,
	KEYBOARD_ENC_CMD_REG				= 0x60
};
 
enum KEYBOARD_CTRL_IO {
 
	KEYBOARD_CTRL_STATS_REG				= 0x64,
	KEYBOARD_CTRL_CMD_REG				= 0x64
};

enum KEYBOARD_CTRL_STATS_MASK {
 
	KEYBOARD_CTRL_STATS_MASK_OUT_BUF	= 1,		//00000001
	KEYBOARD_CTRL_STATS_MASK_IN_BUF		= 2,		//00000010
	KEYBOARD_CTRL_STATS_MASK_SYSTEM		= 4,		//00000100
	KEYBOARD_CTRL_STATS_MASK_CMD_DATA	= 8,		//00001000
	KEYBOARD_CTRL_STATS_MASK_LOCKED		= 0x10,		//00010000
	KEYBOARD_CTRL_STATS_MASK_AUX_BUF	= 0x20,		//00100000
	KEYBOARD_CTRL_STATS_MASK_TIMEOUT	= 0x40,		//01000000
	KEYBOARD_CTRL_STATS_MASK_PARITY		= 0x80		//10000000
};

enum KEYBOARD_CTRL_CMD {

	KEYBOARD_CTRL_CMD_DISABLE			= 0xAD,
	KEYBOARD_CTRL_CMD_ENABLE			= 0xAE,
	KEYBOARD_CTRL_CMD_SELF_TEST			= 0xAA,
	KEYBOARD_CTRL_CMD_WRITE_OUT_PORT	= 0xD1
};

enum KEYBOARD_ENC_CMD {

	KEYBOARD_ENC_CMD_SET_LED			= 0xED
};
