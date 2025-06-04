/*----------------*\
|Nanite OS         |
|Copyright (C) 2025|
|Tyler McGurrin    |
\*----------------*/
#include <stdint.h>
#include <stdio.h>
#include <memory.h>
#include <arch/i686/io.h>
#include <arch/i686/irq.h>
#include <arch/i686/basicfunc.h>
#include <dri/keyboard.h>
#include <dri/cmos.h>
#include <dri/serial.h>
#include <dri/fat.h>
#include <dri/disk/floppy.h>
#include <dri/disk/ata.h>
#include <core/hal/hal.h>
#include <util/param.h>
#include <util/util.h>
#include "../libs/version.h"
#include "../libs/boot/bootparams.h"

#define PS2_KEYBOARD_PORT 0x60

extern uint8_t __bss_start;
extern uint8_t __end;

uint16_t DEBUG_COM_PORT = COM1_PORT;

int uptime;
void timer(Registers* regs)
{
    uptime++;
    // printf("%d", uptime);
    // movecursorpos(8,14);
}


void __attribute__((section(".entry"))) start(BootParams* bootParams) {

    // print logo
    clrscr();
    printf("%s", LOGO);
    printf("The Nano OS                  %s\n-------------------------------------\n", VERSION);
    printf("Loaded Kernel!\n");

    // init HAL
    printf("Initializing HAL...\n");
    HAL_Initialize();
    movecursorpos(19, 8);
    printf("Done!\n\n\n\n\n");

    // Register IRQs
    printf("Registering IRQs...");
    IRQ_RegisterHandler(0, timer);
    IRQ_RegisterHandler(1, Keyboard_Handler);
    IRQ_RegisterHandler(4, COM1_Serial_Handler);
    IRQ_RegisterHandler(6, Floppy_Handler);
    IRQ_RegisterHandler(8, CMOS_RTC_Handler);
    printf("Done!\n");

    // Init Drivers
    printf("Initializing Basic Drivers...");
    Serial_Init(DEBUG_COM_PORT, 9600);
    Keyboard_Init();
    Floppy_Init(); // This should always be last; its slow as fuck
    printf("Done!\n");




    // Debug Info for Memory
    Serial_Printf(DEBUG_COM_PORT, "MEMORY:> Boot Device: %x\n", bootParams->BootDevice);
    Serial_Printf(DEBUG_COM_PORT, "MEMORY:> Region Count: %x\n", bootParams->Memory.RegionCount);
    for (int i = 0; i < bootParams->Memory.RegionCount; i++) {
        Serial_Printf(DEBUG_COM_PORT, "MEMORY:> start=0x%llx length=0x%llx type=0x%x\n", 
        bootParams->Memory.Regions[i].Begin, bootParams->Memory.Regions[i].Length, bootParams->Memory.Regions[i].Type);
    }

end:
    for (;;);
}


