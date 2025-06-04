/*----------------*\
|Nanite OS         |
|Copyright (C) 2025|
|Tyler McGurrin    |
\*----------------*/
#include "floppy.h"

#include <stdint.h>
#include <stdio.h>
#include <arch/i686/io.h>
#include <arch/i686/irq.h>
#include <dri/serial.h>

extern uint16_t DEBUG_COM_PORT;

volatile unsigned char FloppyIRQRecived = false;

void Floppy_Handler()
{
    FloppyIRQRecived = true;
    Serial_Printf(DEBUG_COM_PORT, "Recived IRQ From Floppy Drive.\n");
}

void Floppy_Drive_Init(uint8_t drive)
{
    uint8_t Buffer;
    if (drive == 1) Buffer = FLOPPY_DOR_DSEL1 && FLOPPY_DOR_DSEL1 && FLOPPY_DOR_RESET && FLOPPY_DOR_MOTA && 0 && 0 && 0;
    if (drive == 2) Buffer = FLOPPY_DOR_DSEL1 && FLOPPY_DOR_DSEL1 && FLOPPY_DOR_RESET && 0 && FLOPPY_DOR_MOTB && 0 && 0;
    i686_outb(FLOPPY_DIGITAL_OUTPUT_REGISTER, Buffer);
    Serial_Printf(DEBUG_COM_PORT, "Started Floppy Drive: %u\n", drive);
}

void Floppy_Send_Command(uint8_t command)
{
    i686_outb(FLOPPY_DATA_FIFO, command);
    Serial_Printf(DEBUG_COM_PORT, "Floppy Command Sent: %u\n", command);
}

void Floppy_LBA2CHS(FLOPPY_DISK* disk, uint32_t lba, uint16_t* cylinderOut, uint16_t* sectorOut, uint16_t* headOut) {
    // sector = (LBA % sectors per track + 1)
    *sectorOut = lba % disk->sectors +1;

    // cylinder = (LBA / sects per track / heads)
    *cylinderOut = (lba / disk->sectors) / disk->heads;

    // head = (LBA / sects per track % heads)
    *headOut = (lba / disk->sectors) % disk->heads;
}