/*----------------*\
|Nanite OS         |
|Copyright (C) 2025|
|Tyler McGurrin    |
\*----------------*/
#include "serial.h"

#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include <arch/i686/io.h>

char Serial_Read_Buffer;
char Serial_Write_Buffer;

/*
IO Port Offset 	Setting of DLAB 	I/O Access 	Register mapped to this port
    +0 	0 	    Read 	            Receive buffer.
    +0 	0       Write 	            Transmit buffer.
    +1 	0       Read/Write 	        Interrupt Enable Register.
    +0 	1       Read/Write 	        With DLAB set to 1, this is the least significant byte of the divisor value for setting the baud rate.
    +1 	1       Read/Write 	        With DLAB set to 1, this is the most significant byte of the divisor value.
    +2 	-       Read 	            Interrupt Identification
    +2 	-       Write 	            FIFO control registers
    +3 	-       Read/Write 	        Line Control Register. The most significant bit of this register is the DLAB.
    +4 	-       Read/Write 	        Modem Control Register.
    +5 	-       Read 	            Line Status Register.
    +6 	- 	    Read 	            Modem Status Register.
    +7 	- 	    Read/Write 	        Scratch Register. 
*/


// Cannot Figure out what part of spec triggers this,
// OSDEV wiki just says it exists thats about it...
void COM1_Serial_Handler()
{
    // Serial_Read_Buffer = Read_Serial(COM1_PORT);
    // printf("Serial Read Buffer: %s", Serial_Read_Buffer);
    printf("IRQ 4 Triggered!");
}

int Serial_Init(uint16_t COM_Port, int Baud) 
{
    uint8_t Divisor = 115200 / Baud;

    outb(COM_Port + 1, 0x00);    // Disable all interrupts
    outb(COM_Port + 3, Divisor);    // Enable DLAB (set baud rate divisor)
    outb(COM_Port + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
    outb(COM_Port + 1, 0x00);    //                  (hi byte)
    outb(COM_Port + 3, 0x03);    // 8 bits, no parity, one stop bit
    outb(COM_Port + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
    outb(COM_Port + 4, 0x0B);    // IRQs enabled, RTS/DSR set
    outb(COM_Port + 4, 0x1E);    // Set in loopback mode, test the serial chip
    outb(COM_Port + 0, 0xAE);    // Test serial chip (send byte 0xAE and check if serial returns same byte)

    // Check if serial is faulty (i.e: not same byte as sent)
    if(inb(COM_Port + 0) != 0xAE) {
       return 1;
    }

    // If serial is not faulty set it in normal operation mode
    // (not-loopback with IRQs enabled and OUT#1 and OUT#2 bits enabled)
    outb(COM_Port + 4, 0x0F);
    return 0;
}

int Serial_Received(uint16_t COM_Port) 
{
    return inb(COM_Port + 5) & 1;
}

char Read_Serial(uint16_t COM_Port) 
{
    while (Serial_Received(COM_Port) == 0);

    return inb(COM_Port);
}

int Serial_Transmit_Empty(uint16_t COM_Port) 
{
    return inb(COM_Port + 5) & 0x20;
}

void Write_Serial(uint16_t COM_Port, char a) 
{
    while (Serial_Transmit_Empty(COM_Port) == 0);

    outb(COM_Port,a);
}
// We do the funny...
extern const char g_HexChars[];

void Serial_Puts(uint16_t COM_Port, const char* str)
{
	while(*str)
	{
		Write_Serial(COM_Port, *str);
		str++;
	}
}

void Serial_Printf_Unsigned(uint16_t COM_Port,unsigned long long number, int radix)
{
	char buffer[32];
	int pos = 0;

	//number to ASCII conversion
	do {
		unsigned long long rem = number % radix;
		number /= radix;
		buffer[pos++] = g_HexChars[rem];
	} while (number > 0);

	//print number in reverse order
	while (--pos >= 0) 
	    Write_Serial(COM_Port, buffer[pos]);
}

void Serial_Printf_Signed(uint16_t COM_Port,long long number, int radix)
{
	if (number < 0)
	{
	    Write_Serial(COM_Port, '-');
		Serial_Printf_Unsigned(COM_Port, -number, radix);
	}
	else Serial_Printf_Unsigned(COM_Port, number, radix);

}


#define PRINTF_STATE_NORMAL			 0
#define PRINTF_STATE_LENGTH			 1
#define PRINTF_STATE_LENGTH_SHORT	 2
#define PRINTF_STATE_LENGTH_LONG	 3
#define PRINTF_STATE_SPEC			 4

#define PRINTF_LENGTH_DEFAULT		 0
#define PRINTF_LENGTH_SHORT_SHORT    1
#define PRINTF_LENGTH_SHORT     	 2
#define PRINTF_LENGTH_LONG   		 3
#define PRINTF_LENGTH_LONG_LONG		 4

void Serial_Printf(uint16_t COM_Port, const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    int state = PRINTF_STATE_NORMAL;
    int length = PRINTF_LENGTH_DEFAULT;
    int radix = 10;
    bool sign = false;
    bool number = false;

    while (*fmt)
    {
        switch (state)
        {
            case PRINTF_STATE_NORMAL:
                switch (*fmt)
                {
                    case '%':   state = PRINTF_STATE_LENGTH;
                                break;
                    default:    Write_Serial(COM_Port, *fmt);
                                break;
                }
                break;

            case PRINTF_STATE_LENGTH:
                switch (*fmt)
                {
                    case 'h':   length = PRINTF_LENGTH_SHORT;
                                state = PRINTF_STATE_LENGTH_SHORT;
                                break;
                    case 'l':   length = PRINTF_LENGTH_LONG;
                                state = PRINTF_STATE_LENGTH_LONG;
                                break;
                    default:    goto PRINTF_STATE_SPEC_;
                }
                break;

            case PRINTF_STATE_LENGTH_SHORT:
                if (*fmt == 'h')
                {
                    length = PRINTF_LENGTH_SHORT_SHORT;
                    state = PRINTF_STATE_SPEC;
                }
                else goto PRINTF_STATE_SPEC_;
                break;

            case PRINTF_STATE_LENGTH_LONG:
                if (*fmt == 'l')
                {
                    length = PRINTF_LENGTH_LONG_LONG;
                    state = PRINTF_STATE_SPEC;
                }
                else goto PRINTF_STATE_SPEC_;
                break;

            case PRINTF_STATE_SPEC:
            PRINTF_STATE_SPEC_:
                switch (*fmt)
                {
                    case 'c':   Write_Serial(COM_Port, (char)va_arg(args, int));
                                break;

                    case 's':   
                                Serial_Puts(COM_Port, va_arg(args, const char*));
                                break;

                    case '%':   Write_Serial(COM_Port, '%');
                                break;

                    case 'd':
                    case 'i':   radix = 10; sign = true; number = true;
                                break;

                    case 'u':   radix = 10; sign = false; number = true;
                                break;

                    case 'X':
                    case 'x':
                    case 'p':   radix = 16; sign = false; number = true;
                                break;

                    case 'o':   radix = 8; sign = false; number = true;
                                break;

                    // ignore invalid spec
                    default:    break;
                }

                if (number)
                {
                    if (sign)
                    {
                        switch (length)
                        {
                        case PRINTF_LENGTH_SHORT_SHORT:
                        case PRINTF_LENGTH_SHORT:
                        case PRINTF_LENGTH_DEFAULT:     Serial_Printf_Signed(COM_Port, va_arg(args, int), radix);
                                                        break;

                        case PRINTF_LENGTH_LONG:        Serial_Printf_Signed(COM_Port, va_arg(args, long), radix);
                                                        break;

                        case PRINTF_LENGTH_LONG_LONG:   Serial_Printf_Signed(COM_Port, va_arg(args, long long), radix);
                                                        break;
                        }
                    }
                    else
                    {
                        switch (length)
                        {
                        case PRINTF_LENGTH_SHORT_SHORT:
                        case PRINTF_LENGTH_SHORT:
                        case PRINTF_LENGTH_DEFAULT:     Serial_Printf_Unsigned(COM_Port, va_arg(args, unsigned int), radix);
                                                        break;
                                                        
                        case PRINTF_LENGTH_LONG:        Serial_Printf_Unsigned(COM_Port, va_arg(args, unsigned  long), radix);
                                                        break;

                        case PRINTF_LENGTH_LONG_LONG:   Serial_Printf_Unsigned(COM_Port, va_arg(args, unsigned  long long), radix);
                                                        break;
                        }
                    }
                }

                // reset state
                state = PRINTF_STATE_NORMAL;
                length = PRINTF_LENGTH_DEFAULT;
                radix = 10;
                sign = false;
                number = false;
                break;
        }

        fmt++;
    }

    va_end(args);
}