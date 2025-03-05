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
#include <dri/keyboard.h>
#include "../libs/version.h"
#include "../libs/boot/bootparams.h"

extern uint8_t __bss_start;
extern uint8_t __end;

void timer(Registers* regs)
{
    int uptime;
    uptime++;
}

void __attribute__((section(".entry"))) start(BootParams* bootParams) {

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
    printf("Load Keyboard Driver...");
    Keyboard_Init();
    printf("Done!\n");

    // Debug Info for Memory :3
    // printf("Boot Device: %x\n", bootParams->BootDevice);
    // printf("Memory Region Count: %x\n", bootParams->Memory.RegionCount);
    // for (int i = 0; i < bootParams->Memory.RegionCount; i++) {
    //     printf("Memory: start=0x%llx length=0x%llx type=0x%x\n", 
    //     bootParams->Memory.Regions[i].Begin, bootParams->Memory.Regions[i].Length, bootParams->Memory.Regions[i].Type);
    // }



end:
    for (;;);
}


