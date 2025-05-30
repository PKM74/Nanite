/*----------------*\
|Nanite OS         |
|Copyright (C) 2025|
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
#include <dri/cmos.h>
#include <dri/fat.h>
#include <dri/disk/floppy.h>
#include <dri/disk/ata.h>
#include <util/param.h>
#include <util/util.h>
#include "../libs/version.h"
#include "../libs/boot/bootparams.h"

#define PS2_KEYBOARD_PORT 0x60

extern uint8_t __bss_start;
extern uint8_t __end;

int masterFDDType;
int slaveFDDType;

int uptime;
void timer(Registers* regs)
{
    uptime++;
    // printf("%d", uptime);
    // movecursorpos(8,14);
}

int keyboard_scancode;
void keyboard()
{
    keyboard_scancode = i686_inb(PS2_KEYBOARD_PORT);
    // Debug Message, need to make a serial output thingy :)
    // printf("Keycode = %d Port = %d\n", keycode, PS2_KEYBOARD_PORT);
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
    i686_IRQ_RegisterHandler(0, timer);
    i686_IRQ_RegisterHandler(8, CMOS_RTC_Handler);

    // Begin Loading Basic Drivers
    printf("Load Keyboard Driver...");
    i686_IRQ_RegisterHandler(1, keyboard);
    printf("Done!\n");

    printf("Load Basic Storage Drivers...");
    i686_IRQ_RegisterHandler(6, Floppy_Handler);
    printf("Done!\n");
    masterFDDType = Master_FDD_Detect();
    slaveFDDType = Slave_FDD_Detect();
    Print_Storage_Types(masterFDDType, slaveFDDType);




    // Debug Info for Memory :3 i REALLY need to make a like serial debug output thingy
    // printf("Boot Device: %x\n", bootParams->BootDevice);
    // printf("Memory Region Count: %x\n", bootParams->Memory.RegionCount);
    // for (int i = 0; i < bootParams->Memory.RegionCount; i++) {shell example
    //     printf("Memory: start=0x%llx length=0x%llx type=0x%x\n", 
    //     bootParams->Memory.Regions[i].Begin, bootParams->Memory.Regions[i].Length, bootParams->Memory.Regions[i].Type);
    // }



end:
    for (;;);
}


