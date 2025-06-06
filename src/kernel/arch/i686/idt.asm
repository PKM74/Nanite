;/////////////////////;
;Nanite OS            ;
;COPYRIGHT (C) 2024   ;
;Tyler McGurrin       ;
;/////////////////////;
[bits 32]

; void __attribute__((cdecl)) IDT_Load(IDTDescriptor* idtDescriptor);
global IDT_Load
IDT_Load:

    ; make new call frame
    push ebp             ; save old call frame
    mov ebp, esp         ; initialize new call frame
    
    ; load idt
    mov eax, [ebp + 8]
    lidt [eax]

    ; restore old call frame
    mov esp, ebp
    pop ebp
    ret