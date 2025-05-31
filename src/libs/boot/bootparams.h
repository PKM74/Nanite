/*----------------*\
|Nanite OS         |
|Copyright (C) 2024|
|Tyler McGurrin    |
\*----------------*/
#pragma once

#include <stdint.h>

typedef struct {
    uint64_t Begin, Length;
    uint32_t Type;
    uint32_t ACPI;
} MemoryRegion;

typedef struct
{
    int RegionCount;
    MemoryRegion* Regions;
} MemoryInfo;


typedef struct {
    MemoryInfo Memory;
    char* KernelParams;
    uint8_t BootDevice;
} BootParams;
