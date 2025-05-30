/*----------------*\
|Nanite OS         |
|Copyright (C) 2025|
|Tyler McGurrin    |
\*----------------*/
#include "ata.h"

#include <stdio.h>

#define PORT_DRIVE_NUMBER 502
#define PORT_SECTOR_COUNT 498
#define PORT_SECTOR_NUMBER 499
#define PORT_CYLINDER_LOW 500
#define PORT_CYLINDER_HIGH 501
#define PORT_COMMAND 503

bool ATA_Drive_Init(DISK* disk, uint8_t driveNumber)
{
    uint8_t driveType;
    uint16_t cylinders, sectors, heads;
    
    if (!ATA_Get_Drive_Params(disk->id, &driveType, &cylinders, &sectors, &heads))
        return false;

    disk->id = driveNumber;
    disk->cylinders = cylinders;
    disk->heads = heads;
    disk->sectors = sectors;

    return true;
}

bool ATA_Get_Drive_Params(uint8_t diskID, uint8_t* driveType, uint16_t* cylinders, uint16_t* sectors, uint16_t* heads)
{

}

void ATA_CHS_Read(int number_of_sectors, int drive_number, int buffer)
{

}

void ATA_LBA2CHS(DISK* disk, uint32_t lba, uint16_t* cylinderOut, uint16_t* sectorOut, uint16_t* headOut) {
    // sector = (LBA % sectors per track + 1)
    *sectorOut = lba % disk->sectors +1;

    // cylinder = (LBA / sects per track / heads)
    *cylinderOut = (lba / disk->sectors) / disk->heads;

    // head = (LBA / sects per track % heads)
    *headOut = (lba / disk->sectors) % disk->heads;

    // printf("LBA2CHS: lba=%u sect=%u cyl=%u head=%u disk_sectors=%u disk_heads=%u\n", lba, *sectorOut, *cylinderOut, *headOut, disk->sectors, disk->heads);
}