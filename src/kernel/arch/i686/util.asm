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

global Read_CR0
Read_CR0:
	mov eax, cr0
	retn

global Write_CR0
Write_CR0:
	push ebp
	mov ebp, esp
	mov eax, [ebp+8]
	mov cr0,  eax
	pop ebp
	retn

global Read_CR3
Read_CR3:
	mov eax, cr3
	retn

global Write_CR3
Write_CR3:
	push ebp
	mov ebp, esp
	mov eax, [ebp+8]
	mov cr3, eax
	pop ebp
	retn
