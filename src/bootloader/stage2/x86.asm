;/////////////////////;
;Nanite OS            ;
;COPYRIGHT (C) 2024   ;
;Tyler McGurrin       ;
;/////////////////////;
bits 16

section _TEXT class=CODE

;
;void _cdecl x86_div64_32(uint64_t dividend, uint32_t divisor, uint64_t* quotentOut, uint32_t* remainderOut);
;

global _x86_div64_32
_x86_div64_32
	;make new call frame
	push bp			;save old call frame
	mov bp, sp		;init new call frame

	push bx

	;divide upper 32 bits
	mov eax, [bp + 4]	;eax is upper 32 bits of divedend
	mov ecx, [bp + 12]	;ecx is the divisor
	xor edx, edx
	div ecx				;eax - quot, edx - remainder

	;store upper 32 bits
	mov ebx, [bp + 16]
	mov [bx + 4], eax

	;divide lower 32 bits
	mov eax, [bp + 4]	;eax is the lower 32 bits of the dividend
						;edx is old remainder
	div ecx

	;store results
	mov [bx], eax
	mov bx, [bp + 18]
	mov [bx], edx

	pop bx

	;restore old call frame
	mov sp, bp
	pop bp
	ret




global _x86_Video_WriteCharTeletype
_x86_Video_WriteCharTeletype:

	push bp
	mov bp,sp

	push bx

	mov ah, 0Eh
	mov al, [bp + 4]
	mov bh, [bp + 6]

	int 10h

	pop bx

	mov sp, bp
	pop bp
	ret


;
;void _cdecl x86_Disk_Reset(uint8_t drive);
;
global _x86_Disk_Reset
_x86_Disk_Reset:
	;make new call frame
	push bp			;save old call frame
	mov bp, sp		;init new call frame

	

	;restore old call frame
	mov sp, bp
	pop bp
	ret


;
;void _cdecl x86_Disk_Read(uint8_t drive,
;						  uint16_t cylinder,
;						  uint16_t head,
;						  uint16_t sector,
;						  uint8_t count,
;						  uint8_t far * dataout);
;
;void _cdelc x86_Disk_GetDriveParams(uint8_t drive,
;									uint8_t* driveTypeOut,
;									uint16_t* cylindersOut,
;									uint16_t* sectorsOut,
;									uint16_t* headsOut);
