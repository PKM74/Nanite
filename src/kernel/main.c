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
#include <arch/i686/util.h>
#include <dri/keyboard.h>
#include <dri/cmos.h>
#include <dri/serial.h>
#include <dri/fat.h>
#include <dri/disk/floppy.h>
#include <dri/disk/ata.h>
#include <core/hal/hal.h>
#include <core/memory/page.h>
#include <util/param.h>
#include <util/util.h>
#include <version.h>

extern uint8_t __bss_start;
extern uint8_t __end;

uint16_t DEBUG_COM_PORT = COM1_PORT;

void __attribute__((section(".entry"))) start(uint64_t multiboot_magic, void *multiboot_data) {

    // multiboot 2 shit
    // int padded_size = tag->size + ((tag->size % 8)?(8-(tag->size%8)):0);
    // tag = incptr(tag, padded_size);
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
    IRQ_RegisterHandler(0, CPU_Timer);
    IRQ_RegisterHandler(1, Keyboard_Handler);
    IRQ_RegisterHandler(4, COM1_Serial_Handler);
    IRQ_RegisterHandler(6, Floppy_Handler);
    IRQ_RegisterHandler(8, CMOS_RTC_Handler);
    printf("Done!\n");
    
    // Init Drivers
    printf("Initializing Basic Drivers...");
    Serial_Init(DEBUG_COM_PORT, 9600);
    Keyboard_Init();
    // Floppy_Init(); // This should always be last; its slow as fuck
    printf("Done!\n");

    // unsure why this is not working, will look into it later...
    printf("Initializing Memory Paging...");
    Memory_Page_Init();
    printf("Done!\n");
    printf("Multiboot Magic: %d\n", multiboot_magic);

end:
    for (;;);
}


