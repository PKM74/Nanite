/*----------------*\
|Nanite OS         |
|Copyright (C) 2024|
|Tyler McGurrin    |
\*----------------*/
#include "isr.h"
#include "idt.h"
#include "gdt.h"
#include "io.h"
#include <stdio.h>
#include <stddef.h>
#include <dri/serial.h>

extern uint16_t DEBUG_COM_PORT;

ISRHandler g_ISRHandlers[256];

static const char* const g_Exceptions[] = {
    "Divide by zero error",
    "Debug",
    "Non-maskable Interrupt",
    "Breakpoint",
    "Overflow",
    "Bound Range Exceeded",
    "Invalid Opcode",
    "Device Not Available",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Invalid TSS",
    "Segment Not Present",
    "Stack-Segment Fault",
    "General Protection Fault",
    "Page Fault",
    "",
    "x87 Floating-Point Exception",
    "Alignment Check",
    "Machine Check",
    "SIMD Floating-Point Exception",
    "Virtualization Exception",
    "Control Protection Exception ",
    "",
    "",
    "",
    "",
    "",
    "",
    "Hypervisor Injection Exception",
    "VMM Communication Exception",
    "Security Exception",
    ""
};

void ISR_InitializeGates();

void ISR_Initialize() {
    ISR_InitializeGates();
    for (int i = 0; i < 256; i++)
        IDT_EnableGate(i);

    // IDT_DisableGate(50);
}

void __attribute__((cdecl)) ISR_Handler(Registers* regs) {
    if (g_ISRHandlers[regs->interrupt] != NULL)
        g_ISRHandlers[regs->interrupt](regs);

    else if (regs->interrupt >= 32)
        Serial_Printf(DEBUG_COM_PORT, "Unhandled Interrupt %d\n", regs->interrupt);
    else {
        Serial_Printf(DEBUG_COM_PORT, "Unhandled Exception %d %s\n", regs->interrupt, g_Exceptions[regs->interrupt]);
        Serial_Printf(DEBUG_COM_PORT, "  EAX=%x EBX=%x ECX=%x EDX=%x ESI=%x EDI=%x\n",  regs->eax, regs->ebx, regs->ecx, regs->edx, regs->esi, regs->edi);
        Serial_Printf(DEBUG_COM_PORT, "  ESP=%x EBP=%x EIP=%x EFLAGS=%x CS=%x DS=%x SS=%x\n",  regs->esp, regs->ebp, regs->eip, regs->eflags, regs->cs, regs->ds, regs->ss);
        Serial_Printf(DEBUG_COM_PORT, "  INTERRUPT=%x ERRORCODE=%x\n", regs->interrupt, regs->error);
        Serial_Printf(DEBUG_COM_PORT, "KERNEL PANIC!\n");
        kernel_panic();
    }

}
void ISR_RegisterHandler(int interrupt, ISRHandler handler)
{
    g_ISRHandlers[interrupt] = handler;
    IDT_EnableGate(interrupt);
}