/*----------------*\
|Nanite OS         |
|Copyright (C) 2024|
|Tyler McGurrin    |
\*----------------*/
#include <stdint.h>
#include "stdio.h"
#include "x86.h"
#include "disk.h"
#include "fat.h"

#define LOGO "    _   _____    _   __________________\n   / | / /   |  / | / /  _/_  __/ ____/\n  /  |/ / /| | /  |/ // /  / / / __/   \n / /|  / ___ |/ /|  // /  / / / /___   \n/_/ |_/_/  |_/_/ |_/___/ /_/ /_____/   \n"
#define VERSION "v0.0.1"

void* g_data = (void*)0x20000;

 void puts_realmode(const char* str) {
    while (*str) {
        x86_realmode_putc(*str);
        ++str;
    }
 }

 void __attribute__((cdecl)) start(uint16_t bootDrive) {
printf("Done!\n"); // done msg for load kernel (LEAVE HERE)

end:
    for (;;);
}


