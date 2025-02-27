/*----------------*\
|Nanite OS         |
|Copyright (C) 2024|
|Tyler McGurrin    |
\*----------------*/
#include <stdint.h>
#include <stdio.h>
#include <memory.h>
#include <hal/hal.h>
#include <arch/i686/io.h>
#include <arch/i686/irq.h>
#include <arch/i686/basicfunc.h>
#include "../version.h"

extern uint8_t __bss_start;
extern uint8_t __end;

void timer(Registers* regs)
{
    printf(".");
}

void __attribute__((section(".entry"))) start(uint16_t bootDrive) {

    // print logo
    clrscr();
    printf("%s", LOGO);
    printf("The Nano OS                   %s\n-------------------------------------\n", VERSION);
    printf("Loaded Kernel!\n");

    // init HAL
    printf("Initializing HAL...\n");
    HAL_Initialize();
    movecursorpos(19, 8);
    printf("Done!\n\n\n\n\n");

    i686_IRQ_RegisterHandler(0, timer);


end:
    for (;;);
}


