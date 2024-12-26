[bits 32]

global reboot
reboot:
    XOR         AL, AL
    IN          AL, 0x64
    TEST        AL, 0x02
    JNZ         reboot

    MOV         AL, 0xFC
    OUT         0x64, AL
