/*----------------*\
|Nanite OS         |
|Copyright (C) 2024|
|Tyler McGurrin    |
\*----------------*/
#include "disk.h"
#include "x86.h"
#include "stdio.h"

bool DISK_Initialize(DISK* disk, uint8_t driveNumber) {
    uint8_t driveType;
    uint16_t cylinders, sectors, heads;
    
    if (!x86_Disk_GetDriveParams(disk->id, &driveType, &cylinders, &sectors, &heads))
        return false;

    disk->id = driveNumber;
    disk->cylinders = cylinders;
    disk->heads = heads;
    disk->sectors = sectors;

    return true;
}

void DISK_LBA2CHS(DISK* disk, uint32_t lba, uint16_t* cylinderOut, uint16_t* sectorOut, uint16_t* headOut) {
    // sector = (LBA % sectors per track + 1)
    *sectorOut = lba % disk->sectors +1;

    // cylinder = (LBA / sects per track / heads)
    *cylinderOut = (lba / disk->sectors) / disk->heads;

    // head = (LBA / sects per track % heads)
    *headOut = (lba / disk->sectors) % disk->heads;

    // printf("LBA2CHS: lba=%u sect=%u cyl=%u head=%u disk_sectors=%u disk_heads=%u\n", lba, *sectorOut, *cylinderOut, *headOut, disk->sectors, disk->heads);
}

bool DISK_ReadSectors(DISK* disk, uint32_t lba, uint8_t sectors, void* dataOut) {
    uint16_t cylinder, sector, head;

    DISK_LBA2CHS(disk, lba, &cylinder, &sector, &head);

    for (int i = 0; i < 3; i++)
    {
        if (x86_Disk_Read(disk->id, cylinder, sector, head, sectors, dataOut))
            return true;

        x86_Disk_Reset(disk->id);
    }

    return false;
}
