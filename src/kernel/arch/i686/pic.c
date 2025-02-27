/*----------------*\
|Nanite OS         |
|Copyright (C) 2024|
|Tyler McGurrin    |
\*----------------*/
#include "pic.h"
#include "io.h"

#define PIC1_COMMAND_PORT       0x20
#define PIC2_COMMAND_PORT       0xA0
#define PIC1_DATA_PORT          0x21
#define PIC2_DATA_PORT          0xA1

enum {
    PIC_ICW1_ICW4           = 0x01,
    PIC_ICW1_SINGLE         = 0x02,
    PIC_ICW1_INTERVAL4      = 0x02,
    PIC_ICW1_LEVEL          = 0x08,
    PIC_ICW1_INITITALIZE    = 0x10
} PIC_ICW1;

enum {
    PIC_ICW4_8086           = 0x1,
    PIC_ICW4_AUTO_EDI       = 0x2,
    PIC_ICW4_BUFFER_MASTER  = 0x4,
    PIC_ICW4_BUFFER_SLAVE   = 0x0,
    PIC_ICW4_BUFFERRED      = 0x8,
    PIC_ICW4_SFNM           = 0x10
} PIC_ICW4;

enum {
    PIC_CMD_END_OF_INTERRUPT    = 0x20,
    PIC_CMD_READ_IRR            = 0x0A,
    PIC_CMD_READ_ISR            = 0x0B
} PIC_CMD;

void i686_PIC_Configure(uint8_t offsetPic1, uint8_t offsetPic2)
{
    // init control word 1
    i686_outb(PIC1_COMMAND_PORT, PIC_ICW1_ICW4 | PIC_ICW1_INITITALIZE);
    i686_iowait();
    i686_outb(PIC2_COMMAND_PORT, PIC_ICW1_ICW4 | PIC_ICW1_INITITALIZE);
    i686_iowait();

    // init control word 2 
    i686_outb(PIC1_DATA_PORT, offsetPic1);
    i686_iowait();
    i686_outb(PIC2_DATA_PORT, offsetPic2);
    i686_iowait();

    // init control word 3
    i686_outb(PIC1_DATA_PORT, PIC_ICW4_BUFFER_MASTER);     // tell PIC 1 it has slave at IRQ 2
    i686_iowait();
    i686_outb(PIC2_DATA_PORT, PIC_ICW4_BUFFER_SLAVE);     // tell PIC 2 its cascade ID
    i686_iowait();

    // init control word 4
    i686_outb(PIC1_DATA_PORT, PIC_ICW4_8086);
    i686_iowait();
    i686_outb(PIC2_DATA_PORT, PIC_ICW4_8086);
    i686_iowait();

    // clear data registers
    i686_outb(PIC1_DATA_PORT, 0);
    i686_iowait();
    i686_outb(PIC2_DATA_PORT, 0);
    i686_iowait();
}

void i686_PIC_Mask(int irq)
{
    uint8_t port;

    if (irq < 8)
    {
        port = PIC1_DATA_PORT;
    }
    else
    {
        irq -=8;
        port = PIC2_DATA_PORT;
    }
    uint8_t mask = i686_inb(port);
    i686_outb(port, mask | (1 << irq));
}

void i686_PIC_Unmask(int irq)
{
    uint8_t port;

    if (irq < 8)
    {
        port = PIC1_DATA_PORT;
    }
    else
    {
        irq -=8;
        port = PIC2_DATA_PORT;
    }
    uint8_t mask = i686_inb(port);
    i686_outb(port, mask & ~(1 << irq));
}

void i686_PIC_Disable()
{
    i686_outb(PIC1_DATA_PORT, 0xFF);
    i686_iowait();
    i686_outb(PIC2_DATA_PORT, 0xFF);
    i686_iowait();
}

void i686_PIC_SendEndOfInterrupt(int irq)
{
    if (irq >= 8)
        i686_outb(PIC2_COMMAND_PORT, PIC_CMD_END_OF_INTERRUPT);
    i686_outb(PIC1_COMMAND_PORT, PIC_CMD_END_OF_INTERRUPT);
}

uint16_t i686_PIC_ReadIRQRequestRegister()
{
    i686_outb(PIC1_COMMAND_PORT, PIC_CMD_READ_IRR);
    i686_outb(PIC2_COMMAND_PORT, PIC_CMD_READ_IRR);
    return i686_inb(PIC2_COMMAND_PORT) | (i686_inb(PIC2_COMMAND_PORT) << 8);
}

uint16_t i686_PIC_ReadInServiceRegister()
{
    i686_outb(PIC1_COMMAND_PORT, PIC_CMD_READ_ISR);
    i686_outb(PIC2_COMMAND_PORT, PIC_CMD_READ_ISR);
    return i686_inb(PIC2_COMMAND_PORT) | (i686_inb(PIC2_COMMAND_PORT) << 8);
}