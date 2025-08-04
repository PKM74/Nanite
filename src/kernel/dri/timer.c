/*----------------*\
|Nanite OS         |
|Copyright (C) 2025|
|Tyler McGurrin    |
\*----------------*/
#include "timer.h"

int uptime;
void Timer_Handler()
{
    uptime++;
}

void Timer_Wait(int cycles) // Seems to not work? i'll fix it later.
{
    int tmp;
    tmp = uptime;
    while(uptime - tmp <= cycles) return;
}