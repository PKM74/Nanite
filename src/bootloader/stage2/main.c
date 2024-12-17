/*----------------*\
|Nanite OS         |
|Copyright (C) 2024|
|Tyler McGurrin    |
\*----------------*/
#include <stdint.h>
#include "stdio.h"
// #include "disk.h"
// #include "fat.h"

// void far* g_data = (void far*)0x00500200;
#define LOGO "    _   _____    _   __________________\n   / | / /   |  / | / /  _/_  __/ ____/\n  /  |/ / /| | /  |/ // /  / / / __/   \n / /|  / ___ |/ /|  // /  / / / /___   \n\\/_/ |_/_/  |_/_/ |_/___/ /_/ /_____/   \n"
#define VERSION "v0.0.1"

 void __attribute__((cdecl)) start(uint16_t bootDrive) {
    clrscr();
    printf("%s", LOGO);
    printf("                               %s\n--------------------------------------\n", VERSION);

    for(;;);
    
//     printf("Initializing FAT Driver...");
//     DISK disk;
//     if (!DISK_Initialize(&disk, bootDrive)) {
//         printf("Failed!\nDisk Initialization Error\n");
//         goto end;
//     }

//     DISK_ReadSectors(&disk, 19, 1, g_data);

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

// end:
//     for (;;);
}


