/*----------------*\
|Nanite OS         |
|Copyright (C) 2024|
|Tyler McGurrin    |
\*----------------*/
#pragma once

// 0x00000000 - 0x000003FF - int vector table
// 0x00000400 - 0x000004FF - Bios Data

#define MEMORY_MIN          0x00000500
#define MEMORY_MAX          0x00080000

// 0x00000500 - 0x00010500 - FAT Driver
#define MEMORY_FAT_ADDR     ((void far*)0x00500000) // segment:offset SSSS:OOOO
#define MEMORY_FAT_SIZE     0x00010500

// 0x00020000 - 0x00030000 - stage2

// 0x00030000 - 0x00080000 - free

// 0x00080000 - 0x0009FFFF - Extended BIOS data area
// 0x000A0000 - 0x000C7FFF - Video
// 0x000C8000 - 0x000FFFFF - BIOS
