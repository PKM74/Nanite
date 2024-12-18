/*----------------*\
|Nanite OS         |
|Copyright (C) 2024|
|Tyler McGurrin    |
\*----------------*/
#include <stdint.h>
#include <stdio.h>
#include <memory.h"

#define LOGO "    _   _____    _   __________________\n   / | / /   |  / | / /  _/_  __/ ____/\n  /  |/ / /| | /  |/ // /  / / / __/   \n / /|  / ___ |/ /|  // /  / / / /___   \n/_/ |_/_/  |_/_/ |_/___/ /_/ /_____/   \n"
#define VERSION "v0.0.1"

extern uint8_t __bss_start;
extern uint8_t __end;

 void __attribute__((section(".entry"))) start(uint16_t bootDrive) {
    clrscr();
    printf("%s", LOGO);
    printf("The Nano OS                   %s\n-------------------------------------\n", VERSION);
    printf("Kernel Loaded!");

end:
    for (;;);
}


