/*----------------*\
|Nanite OS         |
|Copyright (C) 2024|
|Tyler McGurrin    |
\*----------------*/
#include "stdint.h"
#include "stdio.h"
#include "disk.h"
#include "fat.h"

void far* g_data = (void far*)0x00500200;
#define LOGO "    _   _____    _   __________________\r\n   / | / /   |  / | / /  _/_  __/ ____/\r\n  /  |/ / /| | /  |/ // /  / / / __/   \r\n / /|  / ___ |/ /|  // /  / / / /___   \r\n\\/_/ |_/_/  |_/_/ |_/___/ /_/ /_____/   \r\n"
#define VERSION "v0.0.1"

void _cdecl cstart_(uint16_t bootDrive) {
    printf("%s", LOGO);
    printf("                               %s\r\n--------------------------------------\r\n", VERSION);
    
    printf("Initializing FAT Driver...");
    DISK disk;
    if (!DISK_Initialize(&disk, bootDrive)) {
        printf("Failed!\r\nDisk Initialization Error\r\n");
        goto end;
    }

    DISK_ReadSectors(&disk, 19, 1, g_data);

    if (!FAT_Initialize(&disk)) {
        printf("Failed!\r\nDisk Initialization Error\r\n");
        goto end;
    }
    printf("Done!\r\n");
    // printf("Listing Root DIR...\r\n");
    // // browse files in root
    FAT_File far* fd = FAT_Open(&disk, "/");
    FAT_DirectoryEntry entry;
    int i = 0;
    // while (FAT_ReadEntry(&disk, fd, &entry) && i++ < 5) {
    //     printf("  ");
    //     for (int i = 0; i < 11; i++)
    //         putc(entry.Name[i]);
    //     printf("\r\n");
    // }
    // FAT_Close(fd);

    printf("Testing FAT Driver...");
        // read test.txt
    char buffer[100];
    uint32_t read;
    fd = FAT_Open(&disk, "misc/test.txt");
    while ((read = FAT_Read(&disk, fd, sizeof(buffer), buffer)))
    {
        for (uint32_t i = 0; i < read; i++)
        {
            if (buffer[i] == '\n')
                putc('\r');
            putc(buffer[i]);
        }
    }
    FAT_Close(fd);

end:
    for (;;);
}


