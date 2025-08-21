/*----------------*\
|Nanite OS         |
|Copyright (C) 2025|
|Tyler McGurrin    |
\*----------------*/
#include "timer.h"

#include <stdint.h>

#include <dri/serial.h>

extern uint16_t DEBUG_COM_PORT;

int uptime;
void Timer_Handler()
{
    uptime++;
}

void Timer_Wait(int time)
{
    int tmp;
    tmp = uptime;
    while(0 == 0) {
        if(uptime - tmp == time) return;
    } 
}