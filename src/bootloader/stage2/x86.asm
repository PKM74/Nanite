%macro x86_EnterRealMode 0
    [bits 32]
    jmp work 18h:.pmode16

.pmode16:
    [bits 16]
    mov eax, cr0
    and al, ~1
    mov cr0, eax

    jmp word 00h:.rmode

.rmode:
    mov ax, 0
    mov ds, ax
    mov ss, ax

    sti

%endmacro

%macro x86_EnterProtectedMode 0
    cli
    ; set PMODE enable flag in CR0
    mov eax, CR0
    or al, 1
    mov cr0, eax

    ; far jmp into PMODE
    jmp dword 08h:.pmode

.pmode:
    ; we are now in protected mode!
    [bits 32]
    
    ; 6 - setup segment registers
    mov ax, 0x10
    mov ds, ax
    mov ss, ax


%endmacro


global x86_outb
x86_outb:
    [bits 32]
    mov dx, [esp + 4]
    mov al, [esp + 8]
    out dx, al
    ret

global x86_inb
x86_inb:
    [bits 32]
    mov dx, [esp + 4]
    xor eax, eax
    in al, dx
    ret

global x86_realmode_putc
x86_realmode_putc:
    ; setup stack frame
    push ebp
    mov ebp, esp

    x86_EnterRealMode

    mov al, [sp + 8]
    mov ah, 0xe
    int 10h

    x86_EnterProtectedMode

    mov esp, ebp
    pop ebp
    ret
