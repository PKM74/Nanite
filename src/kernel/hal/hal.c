/*----------------*\
|Nanite OS         |
|Copyright (C) 2024|
|Tyler McGurrin    |
\*----------------*/
#include "hal.h"
#include <arch/i686/gdt.h>
#include <arch/i686/idt.h>
#include <arch/i686/isr.h>
#include <arch/i686/irq.h>
#include <stdio.h>

void HAL_Initialize() { 
    // init GDT
    printf("> Initializing GDT...");
    GDT_Initialize();
    printf("Done!\n");
    // init IDT
    printf("> Initializing IDT...");
    IDT_Initialize();
    printf("Done!\n");
    // init ISR
    printf("> Initializing ISR...");
    ISR_Initialize();
    printf("Done!\n");
    // init IRQ
    printf("> Initializing IRQ Handling...");
    IRQ_Initialize();
    printf("Done!\n");

}