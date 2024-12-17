/*----------------*\
|Nanite OS         |
|Copyright (C) 2024|
|Tyler McGurrin    |
\*----------------*/
#include <stdint.h>
#include "stdio.h"
#include "x86.h"
#include "disk.h"
// #include "fat.h"

#define LOGO "    _   _____    _   __________________\n   / | / /   |  / | / /  _/_  __/ ____/\n  /  |/ / /| | /  |/ // /  / / / __/   \n / /|  / ___ |/ /|  // /  / / / /___   \n\\/_/ |_/_/  |_/_/ |_/___/ /_/ /_____/   \n"
#define VERSION "v0.0.1"

void* g_data = (void*)0x20000;

 void puts_realmode(const char* str) {
    while (*str) {
        x86_realmode_putc(*str);
        ++str;
    }
 }

 void __attribute__((cdecl)) start(uint16_t bootDrive) {
    // Clear screen and Print Startup logo
    clrscr();
    printf("%s", LOGO);
    printf("                               %s\n--------------------------------------\n", VERSION);

    // Test Real Mode
    printf("Testing Real Mode...");
    puts_realmode(" ");
    printf("Ok!\n");

    // get drive params (Test for Disk driver)
    printf("Getting Drive Params...");
    uint8_t driveType;
    uint16_t cyls, sects, heads;
    x86_Disk_GetDriveParams(bootDrive, &driveType, &cyls, &sects, &heads);
    printf("Done!\n");
    printf("> Drive Type: %u\n> Cylinders: %u\n> Sectors: %u\n> Heads: %u\n", driveType, cyls, sects, heads);

    // init disk
    printf("Initializing Disk...");
    DISK disk;
    if (!DISK_Initialize(&disk, bootDrive)) {
        printf("Failed!\nDisk Initialization Error\n");
        goto end;
    }
    printf("Done!\n");
    DISK_ReadSectors(&disk, 0, 1, g_data);
    print_buffer("> Boot Sector Data: ", g_data, 512);

//     printf("Initializing FAT Driver...");
//     if (!FAT_Initialize(&disk)) {
//         printf("Failed!\nDisk Initialization Error\n");
//         goto end;
//     }
//     printf("Done!\n");
//     // printf("Listing Root DIR...\n");
//     // // browse files in root
//     FAT_File far* fd = FAT_Open(&disk, "/");
//     FAT_DirectoryEntry entry;
//     int i = 0;
//     // while (FAT_ReadEntry(&disk, fd, &entry) && i++ < 5) {
//     //     printf("  ");
//     //     for (int i = 0; i < 11; i++)
//     //         putc(entry.Name[i]);
//     //     printf("\n");
//     // }
//     // FAT_Close(fd);

//     printf("Testing FAT Driver...");
//         // read test.txt
//     char buffer[100];
//     uint32_t read;
//     fd = FAT_Open(&disk, "misc/test.txt");
//     while ((read = FAT_Read(&disk, fd, sizeof(buffer), buffer)))
//     {
//         for (uint32_t i = 0; i < read; i++)
//         {
//             if (buffer[i] == '\n')
//                 putc('');
//             putc(buffer[i]);
//         }
//     }
//     FAT_Close(fd);

end:
    for (;;);
}


