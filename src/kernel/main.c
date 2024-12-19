/*----------------*\
|Nanite OS         |
|Copyright (C) 2024|
|Tyler McGurrin    |
\*----------------*/
#include <stdint.h>
#include <stdio.h>
#include <memory.h>
#include <hal/hal.h>
#include "../version.h"

extern uint8_t __bss_start;
extern uint8_t __end;

 void __attribute__((section(".entry"))) start(uint16_t bootDrive) {

    // print logo
    clrscr();
    printf("%s", LOGO);
    printf("The Nano OS                   %s\n-------------------------------------\n", VERSION);
    printf("Loaded Kernel!\n");

    // init HAL
    printf("Initializing HAL...\n");
    int halx, haly = 0;
    HAL_Initialize();
    movecursorpos(19, 8);
    printf("Done!\n\n\n\n");
    printf("Testing Interrupts...\n");
    __asm("int $0x2");
    printf("Testing Interrupts...\n");
    __asm("int $0x3");
    printf("Testing Interrupts...\n");
    __asm("int $0x4");




end:
    for (;;);
}


