;/////////////////////;
;Nanite OS            ;
;COPYRIGHT (C) 2024   ;
;Tyler McGurrin       ;
;/////////////////////;
[bits 32]
section .entry

extern __bss_start
extern __end

extern start
global entry

; My Life is totally funnnn
global entry
entry:
    ; 6 - setup segment registers
    mov ax, 0x10
    mov ds, ax
    mov ss, ax
    mov al, 0
    cld
    rep stosb

    ; clear BSS (uninit data)
    mov edi, __bss_start
    mov ecx, __end
    sub ecx, edi


    xor edx, edx
    push edx
    call start

    cli
    hlt

section .multiboot_header
header_start:
    dd 0xe85250d6                ; magic number
    dd 0                         ; protected mode code
    dd header_end - header_start ; header length
    dd 0x100000000 - (0xe85250d6 + 0 + (header_end - header_start)) ; checksum

    ; required end tag
    dw 0    ; type
    dw 0    ; flags
    dd 8    ; size
header_end: