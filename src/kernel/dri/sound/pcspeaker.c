/*----------------*\
|Nanite OS         |
|Copyright (C) 2025|
|Tyler McGurrin    |
\*----------------*/
#include "pcspeaker.h"

#include <stdint.h>

#include <util/binary.h>

#include <arch/i686/io.h>

#include <dri/timer.h>
#include <dri/cmos.h>
#include <dri/serial.h>

extern uint16_t DEBUG_COM_PORT;
 
void PCSP_Play(uint32_t nFrequence)
{
    uint32_t Div;
    uint8_t tmp;

    Div = 1193180 / nFrequence;
    outb(0x43, 0xb6);
    outb(0x42, (uint8_t) (Div) );
    outb(0x42, (uint8_t) (Div >> 8));

    tmp = inb(0x61);
    if (tmp != (tmp | 3)) {
        outb(0x61, tmp | 3);
    }
}

// make it shut up
void PCSP_Mute()
{
    uint8_t tmp = inb(0x61) & 0xFC;
        
    outb(0x61, tmp);
}

// Make a beep
void PCSP_Beep()
{   
    PCSP_Play(1000);
    Timer_Wait(5);
    PCSP_Mute();
}