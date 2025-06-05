/*----------------*\
|Nanite OS         |
|Copyright (C) 2024|
|Tyler McGurrin    |
\*----------------*/
#pragma once

#include <stdint.h>

void __attribute__((cdecl)) Reboot();
void __attribute__((cdecl)) Read_CR0();
void __attribute__((cdecl)) Write_CR0(uint8_t value);
void __attribute__((cdecl)) Read_CR3();
void __attribute__((cdecl)) Write_CR3(uint8_t value);
