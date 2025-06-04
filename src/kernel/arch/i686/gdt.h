/*----------------*\
|Nanite OS         |
|Copyright (C) 2024|
|Tyler McGurrin    |
\*----------------*/
#pragma once

#define GDT_CODE_SEGMENT 0x8
#define GDT_DATA_SEGMENT 0x10

void GDT_Initialize();