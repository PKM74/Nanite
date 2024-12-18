/*----------------*\
|Nanite OS         |
|Copyright (C) 2024|
|Tyler McGurrin    |
\*----------------*/
#include <stdint.h>
#include "stdio.h"
#include "x86.h"
#include "disk.h"
#include "fat.h"
#include "memdefs.h"
#include "memory.h"

#define LOGO "    _   _____    _   __________________\n   / | / /   |  / | / /  _/_  __/ ____/\n  /  |/ / /| | /  |/ // /  / / / __/   \n / /|  / ___ |/ /|  // /  / / / /___   \n/_/ |_/_/  |_/_/ |_/___/ /_/ /_____/   \n"
#define VERSION "v0.0.1"


uint8_t* KernelLoadBuffer = (uint8_t*)MEMORY_LOAD_KERNEL;
uint8_t* Kernel = (uint8_t*)MEMORY_KERNEL_ADDR;

typedef void (*KernelStart)();

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
    printf("The Nano OS                   %s\n-------------------------------------\n", VERSION);

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
        printf("Failed!\nDisk Initialization Error!\n");
        goto end;
    }
    printf("Done!\n");
    DISK_ReadSectors(&disk, 0, 1, g_data);
    // print_buffer("> Boot Sector Data: ", g_data, 512);

    printf("Initializing FAT Driver...");
    if (!FAT_Initialize(&disk)) {
        printf("Failed!\nDisk Initialization Error!\n");
        goto end;
    }
    printf("Done!\n");

    // test fat driver
    printf("Testing FAT Driver...");
        // read test.txt
    FAT_File* ft = FAT_Open(&disk, "/");
    char buffer[100];
    uint32_t testread;
    ft = FAT_Open(&disk, "test.txt"); // move test.txt in MISC folder later (TM)
    while ((testread = FAT_Read(&disk, ft, sizeof(buffer), buffer)))
    {
        for (uint32_t i = 0; i < testread; i++)
        {
            if (buffer[i] == '\n')
                putc('\r');
            putc(buffer[i]);
        }
    }
    FAT_Close(ft);

    // load kernel from disk
    printf("Loading Kernel...");
    FAT_File* fd = FAT_Open(&disk, "/kernel.bin"); // move to /boot later????? (TM)
    uint32_t read;
    uint8_t* kernelBuffer = Kernel;
    while ((read = FAT_Read(&disk, fd, MEMORY_LOAD_SIZE, KernelLoadBuffer)))
    {
        memcpy(kernelBuffer, KernelLoadBuffer, read);
        kernelBuffer += read;
    }
    FAT_Close(fd);

    // execute kernel
    KernelStart kernelStart = (KernelStart)Kernel;
    kernelStart();




end:
    for (;;);
}


