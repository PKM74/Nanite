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
uint8_t __attribute__((cdecl)) EnableInterrupts();
uint8_t __attribute__((cdecl)) DisableInterrupts();

void iowait();
void __attribute__((cdecl)) kernel_panic();
