/*----------------*\
|Nanite OS         |
|Copyright (C) 2025|
|Tyler McGurrin    |
\*----------------*/
#include "keyboard.h"

#include <stdint.h>
#include <stdbool.h>
#include <arch/i686/irq.h>
#include <arch/i686/io.h>
#include <arch/i686/basicfunc.h>
#include <dri/serial.h>
#include <stdio.h>

bool _keyboard_disable;
bool _numlock, _capslock, _scrolllock;
bool _ctrl, _alt, _shift;

uint8_t _keyboard_scancode;

extern uint16_t DEBUG_COM_PORT;

void Keyboard_Handler()
{
   _keyboard_scancode = inb(KEYBOARD_ENC_INPUT_BUF);
   Serial_Printf(DEBUG_COM_PORT, "KEYBOARD:> Scancode %u\n", _keyboard_scancode);

   // CTRL + ALT + SHIFT Handlers
   if(_keyboard_scancode == 29) _ctrl = true;
   if(_keyboard_scancode == 157) _ctrl = false;
   if(_keyboard_scancode == 56) _alt = true;
   if(_keyboard_scancode == 184) _alt = false;
   if(_keyboard_scancode == 42) _shift = true;
   if(_keyboard_scancode == 170) _shift = false;

   // If CTRL+ALT+DEL Reboot
   if(_keyboard_scancode == 224 && _ctrl == true && _alt == true) Reboot();
}

uint8_t Keyboard_Controller_Status() 
{
	return inb (KEYBOARD_CTRL_STATS_REG);
}

uint8_t Keyboard_Read_Encoder_Buffer()
{ 
	return inb (KEYBOARD_ENC_INPUT_BUF);
}

void Keyboard_Controller_Send_Command(uint8_t command)
{ 
	// wait for controller input buffer to be clear
   Serial_Printf(DEBUG_COM_PORT, "KEYBOARD:> Sending Command %u To Controller.\n", command);
	while (1)
		if ( (Keyboard_Controller_Status() & KEYBOARD_CTRL_STATS_MASK_IN_BUF) == 0)
			break;
	outb (KEYBOARD_CTRL_CMD_REG, command);
}

void Keyboard_Encoder_Send_Command(uint8_t command)
{ 
	// wait for controller input buffer to be clear
   Serial_Printf(DEBUG_COM_PORT, "KEYBOARD:> Sending Command %u To Encoder.\n", command);
	while (1)
		if ( (Keyboard_Controller_Status() & KEYBOARD_CTRL_STATS_MASK_IN_BUF) == 0)
			break;
 
	// send command byte to KEYBOARD encoder
	outb (KEYBOARD_ENC_CMD_REG, command);
}

void Keyboard_Set_Lock_LEDs(bool num, bool caps, bool scroll)
{
	uint8_t data = 0;

	data = (scroll) ? (data | 1) : (data & 1);
	data = (num) ? (num | 2) : (num & 2);
	data = (caps) ? (num | 4) : (num & 4);
	Keyboard_Encoder_Send_Command(KEYBOARD_ENC_CMD_SET_LED);
	Keyboard_Encoder_Send_Command(data);
}

bool Keyboard_Self_Test()
{
	Keyboard_Controller_Send_Command(KEYBOARD_CTRL_CMD_SELF_TEST);
 
	while (1)
		if (Keyboard_Controller_Status() & KEYBOARD_CTRL_STATS_MASK_OUT_BUF)
			break;
 
	return (Keyboard_Read_Encoder_Buffer() == 0x55) ? true : false;
}

void Keyboard_Disable() 
{ 
	Keyboard_Controller_Send_Command(KEYBOARD_CTRL_CMD_DISABLE);
	_keyboard_disable = true;
   Serial_Printf(DEBUG_COM_PORT, "KEYBOARD:> Disabled Input.\n");
}

void Keyboard_Enable() 
{ 
	Keyboard_Controller_Send_Command(KEYBOARD_CTRL_CMD_ENABLE);
	_keyboard_disable = false;
   Serial_Printf(DEBUG_COM_PORT, "KEYBOARD:> Enabled Input.\n");
}

void Keyboard_Reset_System()
{
	//! writes 11111110 to the output port (sets reset system line low)
	Keyboard_Controller_Send_Command(KEYBOARD_CTRL_CMD_WRITE_OUT_PORT);
	Keyboard_Encoder_Send_Command(0xfe);
}

void Keyboard_Init()
{
	// set lock keys and led lights
	_numlock = _scrolllock = _capslock = false;
	Keyboard_Set_Lock_LEDs(false, false, false);
 
	// shift, ctrl, and alt keys
	_shift = _alt = _ctrl = false;
}

