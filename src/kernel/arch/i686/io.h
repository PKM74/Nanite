/*----------------*\
|Nanite OS         |
|Copyright (C) 2024|
|Tyler McGurrin    |
\*----------------*/
#pragma once
#include <stdint.h>
#include <stdbool.h>

void __attribute__((cdecl)) outb(uint16_t port, uint8_t value);
uint8_t __attribute__((cdecl)) inb(uint16_t port);

void i686_iowait();
void __attribute__((cdecl)) i686_panic();
