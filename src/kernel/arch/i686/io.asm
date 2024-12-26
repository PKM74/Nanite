;/////////////////////;
;Nanite OS            ;
;COPYRIGHT (C) 2024   ;
;Tyler McGurrin       ;
;/////////////////////;

global outb
outb:
    [bits 32]
    mov dx, [esp + 4]
    mov al, [esp + 8]
    out dx, al
    ret

global inb
inb:
    [bits 32]
    mov dx, [esp + 4]
    xor eax, eax
    in al, dx
    ret

global i686_panic
i686_panic:
    cli
    hlt
