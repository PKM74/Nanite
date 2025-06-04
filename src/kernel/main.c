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
#include <dri/serial.h>
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

uint16_t DEBUG_COM_PORT = COM1_PORT;

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
    Serial_Printf(DEBUG_COM_PORT, "Keycode = %d Port = %d\n", keyboard_scancode, PS2_KEYBOARD_PORT);
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
    Init_Serial(DEBUG_COM_PORT, 9600);
    i686_IRQ_RegisterHandler(0, timer);
    i686_IRQ_RegisterHandler(8, CMOS_RTC_Handler);
    i686_IRQ_RegisterHandler(4, COM1_Serial_Handler);

    // Begin Loading Basic Drivers
    printf("Load Keyboard Driver...");
    i686_IRQ_RegisterHandler(1, keyboard);
    printf("Done!\n");

    printf("Load Basic Storage Drivers...");
    i686_IRQ_RegisterHandler(6, FLPDSK_Handler);
    printf("Done!\n");
    masterFDDType = Master_FDD_Detect();
    slaveFDDType = Slave_FDD_Detect();
    FLPDSK_Drive_Init(1);
    Print_Storage_Types(masterFDDType, slaveFDDType);
    // printf("Kernel Params: %s\n", bootParams->KernelParams);




    // Debug Info for Memory
    Serial_Printf(DEBUG_COM_PORT, "Memory Debug Info:\n");
    Serial_Printf(DEBUG_COM_PORT, "Boot Device: %x\n", bootParams->BootDevice);
    Serial_Printf(DEBUG_COM_PORT, "Memory Region Count: %x\n", bootParams->Memory.RegionCount);
    for (int i = 0; i < bootParams->Memory.RegionCount; i++) {
        Serial_Printf(DEBUG_COM_PORT, "Memory: start=0x%llx length=0x%llx type=0x%x\n", 
        bootParams->Memory.Regions[i].Begin, bootParams->Memory.Regions[i].Length, bootParams->Memory.Regions[i].Type);
    }



end:
    for (;;);
}


