/*----------------*\
|Nanite OS         |
|Copyright (C) 2024|
|Tyler McGurrin    |
\*----------------*/
#include "page.h"

#include <stdio.h>
#include <stdint.h>
#include <dri/serial.h>
#include <arch/i686/util.h>

extern uint16_t DEBUG_COM_PORT;

unsigned long* Page_Directory = (unsigned long*) 0x9c000;
unsigned long* Page_Table = (unsigned long*) 0x9d000;

void Memory_Page_Init()
{
    unsigned long address = 0;
    unsigned int i;

    Serial_Printf(DEBUG_COM_PORT, "MEMORY:> Mapping First 4MB of Memory.\n");
    for(i=0; i<1024; i++) {
    Page_Table[i] = address | 3;
    address = address + 4096; // 4096 = 4kb
    }
    Serial_Printf(DEBUG_COM_PORT, "MEMORY:> Inititalizing Page Directory and Table.\n");

    // fill the first entry of the page directory
    // Page_Directory[0] = Page_Table; 
    Page_Directory[0] = Page_Directory[0] | 3; // attribute set to: supervisor level, read/write
    for(i=1; i<1024; i++) {
    Page_Directory[i] = 0 | 2; // attribute set to: supervisor level, read/write
    }
    Write_CR3(Page_Directory);
    Write_CR0(Read_CR0() | 0x80000000); // set the paging bit in CR0 to 1
}