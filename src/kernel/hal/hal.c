/*----------------*\
|Nanite OS         |
|Copyright (C) 2024|
|Tyler McGurrin    |
\*----------------*/
#include "hal.h"
#include <arch/i686/gdt.h>
#include <arch/i686/idt.h>
#include <stdio.h>

void HAL_Initialize() { 
    printf("> Initializing GDT...");
    i686_GDT_Initialize();
    printf("Done!\n");
    printf("> Initializing IDT...");
    i686_IDT_Initialize();
    printf("Done!\n");
}