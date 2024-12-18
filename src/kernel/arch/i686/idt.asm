;/////////////////////;
;Nanite OS            ;
;COPYRIGHT (C) 2024   ;
;Tyler McGurrin       ;
;/////////////////////;
[bits 32]

;void __attribute__((cdecl)) i686_IDT_Load(IDTDescriptor* idtDescriptor);
global i686_IDT_Load
i686_IDT_Load:
    ; make new call frame
    push ebp             ; save old call frame
    mov ebp, esp         ; initialize new call frame

    ; load IDT
    mov eax, [ebp + 8]
    lgdt [eax]



    ; restore old call frame
    mov esp, ebp
    pop ebp
    ret