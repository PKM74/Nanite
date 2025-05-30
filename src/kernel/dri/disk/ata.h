/*----------------*\
|Nanite OS         |
|Copyright (C) 2025|
|Tyler McGurrin    |
\*----------------*/
#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef struct {
    uint8_t id;
    uint16_t cylinders;
    uint16_t sectors;
    uint16_t heads;
} DISK;

bool ATA_Drive_Init(DISK* disk, uint8_t driveNumber);
void ATA_LBA2CHS(DISK* disk, uint32_t lba, uint16_t* cylinderOut, uint16_t* sectorOut, uint16_t* headOut);
bool ATA_Get_Drive_Params(uint8_t disk, uint8_t* driveType, uint16_t* cylinders, uint16_t* sectors, uint16_t* heads);