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
    printf("Initializing HAL...");
    HAL_Initialize();
    printf("Done!\n");

end:
    for (;;);
}


