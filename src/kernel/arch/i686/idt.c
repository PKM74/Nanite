/*----------------*\
|Nanite OS         |
|Copyright (C) 2024|
|Tyler McGurrin    |
\*----------------*/
#include "idt.h"
#include <stdint.h>
#include <util/binary.h>

typedef struct {
    uint16_t BaseLow;
    uint16_t SegmentSelector;
    uint8_t Reserved;
    uint8_t Flags;
    uint16_t BaseHigh;
} __attribute__((packed)) IDTEntry;

typedef struct {
    uint16_t Limit;
    IDTEntry* Ptr;

} __attribute__((packed)) IDTDescriptor;


IDTEntry g_IDT[256];

IDTDescriptor g_IDTDescriptor = {sizeof(g_IDT) -1, g_IDT};

void __attribute__((cdecl)) i686_IDT_Load(IDTDescriptor* idtDescriptor);

void i686_IDT_SetGate(int interupt, void* base, uint16_t segmentDescriptor, uint8_t flags) {
    g_IDT[interupt].BaseLow = ((uint32_t)base) & 0xFFFF;
    g_IDT[interupt].SegmentSelector = segmentDescriptor;
    g_IDT[interupt].Reserved = 0;
    g_IDT[interupt].Flags = flags;
    g_IDT[interupt].BaseHigh = ((uint32_t)base >> 16) & 0xFFFF;
}

void i686_IDT_EnableGate(int interupt) {
    FLAG_SET(g_IDT[interupt].Flags, IDT_FLAG_PRESENT);
}

void i686_IDT_DisableGate(int interupt) {
    FLAG_UNSET(g_IDT[interupt].Flags, IDT_FLAG_PRESENT);
}

void i686_IDT_Initialize() {
    i686_IDT_Load(&g_IDTDescriptor);
}

