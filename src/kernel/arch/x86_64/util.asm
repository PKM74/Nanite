;/////////////////////;
;Nanite OS            ;
;COPYRIGHT (C) 2025   ;
;Tyler McGurrin       ;
;/////////////////////;
[bits 32]

global Reboot
Reboot:
    xor         al, al
    in          al, 0x64
    test        al, 0x02
    jnz         Reboot

    mov         al, 0xFC
    out         0x64, al

global Read_CR0
Read_CR0:
	mov eax, cr0
	retn

global Write_CR0
Write_CR0:
	push ebp
	mov ebp, esp
	mov eax, [ebp+8]
	push eax
	mov cr0,  eax
	pop eax
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

global Enable_Paging
Enable_Paging:
	mov eax, cr4
	or eax, 0x00000010
	mov cr4, eax
