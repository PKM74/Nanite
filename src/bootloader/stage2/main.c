/*----------------*\
|Nanite OS         |
|Copyright (C) 2024|
|Tyler McGurrin    |
\*----------------*/
#include "stdint.h"
#include "stdio.h"
#include "disk.h"
#include "fat.h"

#define VERSION "v0.0.1"

void _cdecl cstart_(uint16_t bootDrive) {

    printf("Loading NANITE %s\r\n\r\n", VERSION);

    printf("Initializing FAT Driver...");
    DISK disk;
    if (!DISK_Initialize(&disk, bootDrive)) {
        printf("Failed!\r\nDisk Init Error!");
        goto end;
    }
    else {
        printf("Done!\r\n");
    }

    // list files in root DIR
    printf("Listing Files in Root Directory...");
    FAT_File far* fd = FAT_Open(&disk, "/");
    FAT_DirectoryEntry entry;
    while (FAT_ReadEntry(&disk, fd, &entry)) {
        printf("  ");
        for (int i = 0; i < 11; i++)
            putc(entry.Name[i]);
        printf("\r\n");
    }
    FAT_Close(fd);
    printf("Done!\r\n");


end:
    for (;;);
}


