;/////////////////////;
;Nanite OS            ;
;COPYRIGHT (C) 2025   ;
;Tyler McGurrin       ;
;/////////////////////;
[bits 32]

global Reboot
Reboot:
    XOR         AL, AL
    IN          AL, 0x64
    TEST        AL, 0x02
    JNZ         Reboot

    MOV         AL, 0xFC
    OUT         0x64, AL
