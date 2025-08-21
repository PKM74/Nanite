/*----------------*\
|Nanite OS         |
|Copyright (C) 2025|
|Tyler McGurrin    |
\*----------------*/

// Architecture specific

#include <arch/i686/io.h>
#include <arch/i686/irq.h>
#include <arch/i686/util.h>

// stdlibs

#include <stdint.h>
#include <stdio.h>
#include <memory.h>

// Drivers

#include <dri/keyboard.h>
#include <dri/cmos.h>
#include <dri/timer.h>
#include <dri/serial.h>
#include <dri/fat.h>
#include <dri/disk/floppy.h>
#include <dri/disk/ata.h>
#include <dri/sound/pcspeaker.h>

// Core

#include <core/hal/hal.h>
#include <core/memory/page.h>

// Utilities

#include <util/param.h>
#include <util/util.h>
#include <util/binary.h>

// Other

#include <version.h>

// Declarations

extern uint8_t __bss_start;
extern uint8_t __end;

extern int uptime;

uint16_t DEBUG_COM_PORT = COM1_PORT;
void start(unsigned long multiboot_magic, unsigned long multiboot_addr) {

    // Print logo
    clrscr();
    printf("%s", LOGO);
    printf("The Nano OS                  %s\n-------------------------------------\n", VERSION);
    
    // Init Drivers
    printf("Initializing Basic Drivers...");
    // HAL
    HAL_Initialize();
    // Register IRQs
    IRQ_RegisterHandler(0, Timer_Handler);
    IRQ_RegisterHandler(1, Keyboard_Handler);
    IRQ_RegisterHandler(4, COM1_Serial_Handler);
    IRQ_RegisterHandler(6, Floppy_Handler);
    IRQ_RegisterHandler(8, CMOS_RTC_Handler);
    // Other Stuff
    Serial_Init(DEBUG_COM_PORT, 9600);
    Keyboard_Init();
    // Storage
    // Floppy_Init(); // This should always be last; its slow as fuck
    printf("Done!\n");

    printf("Initializing Memory Paging...");
    Memory_Page_Init();
    printf("Done!\n");

    // Multiboot Debug Info
    Serial_Printf(DEBUG_COM_PORT, "Multiboot Magic: %d\n", multiboot_magic);
    Serial_Printf(DEBUG_COM_PORT, "Multiboot Address: %d\n", multiboot_addr);

    // Finish Up
    printf("The Current Time and Date Is: %d:%d:%d %d/%d/%d%d\n", 
        BCD2BIN(Read_CMOS(CMOS_RTC_Hours)), 
        BCD2BIN(Read_CMOS(CMOS_RTC_Minutes)), 
        BCD2BIN(Read_CMOS(CMOS_RTC_Seconds)), 
        BCD2BIN(Read_CMOS(CMOS_RTC_Month)),
        BCD2BIN(Read_CMOS(CMOS_RTC_Day)),
        BCD2BIN(Read_CMOS(CMOS_RTC_Century)),
        BCD2BIN(Read_CMOS(CMOS_RTC_Year)));
    // Beep!
    PCSP_Beep();

end:
    for (;;);
}


