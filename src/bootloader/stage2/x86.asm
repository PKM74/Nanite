;/////////////////////;
;Nanite OS            ;
;COPYRIGHT (C) 2024   ;
;Tyler McGurrin       ;
;/////////////////////;
bits 16

section _TEXT class=CODE

;
; U4D
;
; Operation:      Unsigned 4 byte divide
; Inputs:         DX;AX   Dividend
;                 CX;BX   Divisor
; Outputs:        DX;AX   Quotient
;                 CX;BX   Remainder
; Volatile:       none
;
global __U4D
__U4D:
    shl edx, 16         ; dx to upper half of edx
    mov dx, ax          ; edx - dividend
    mov eax, edx        ; eax - dividend
    xor edx, edx

    shl ecx, 16         ; cx to upper half of ecx
    mov cx, bx          ; ecx - divisor

    div ecx             ; eax - quot, edx - remainder
    mov ebx, edx
    mov ecx, edx
    shr ecx, 16

    mov edx, eax
    shr edx, 16

    ret
;
; U4M
;
; Operation:      Interger 4 Byte Multiplication
; Inputs:         DX;AX   INT M1
;                 CX;BX   INT M2
; Outputs:        DX;AX   Product
; Volatile:		  CX;BX   Destroyed
;
global __U4M
__U4M:
	shl edx, 16		;DX to upper 1/2 of EDX
	mov dx, ax
	mov eax, edx

	shl ecx, 16
	mov cx, bx

	mul ecx
	mov edx, eax
	shr edx, 16

	ret



;
;void _cdecl x86_div64_32(uint64_t dividend, uint32_t divisor, uint64_t* quotentOut, uint32_t* remainderOut);
;

global _x86_div64_32
_x86_div64_32:
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
; bool _cdecl x86_Disk_Reset(uint8_t drive);
;
global _x86_Disk_Reset
_x86_Disk_Reset:
	;make new call frame
	push bp			;save old call frame
	mov bp, sp		;init new call frame

	mov ah, 0
	mov dl, [bp + 4]; dl - drive
	std
	int 13h

	mov ax, 1
	sbb ax, 0		; 1 is true 0 is false

	;restore old call frame
	mov sp, bp
	pop bp
	ret


;
; bool _cdecl x86_Disk_Read(uint8_t drive,
;						  uint16_t cylinder,
;						  uint16_t head,
;						  uint16_t sector,
;						  uint8_t count,
;						  uint8_t far * dataout);
;
global _x86_Disk_Read
_x86_Disk_Read:
	;make new call frame
	push bp			;save old call frame
	mov bp, sp		;init new call frame

	;setup args
	mov dl, [bp + 4]; dl - drive

	mov ch, [bp + 6]; ch - cylinder (lower 8 bits)
	mov cl, [bp + 7]; cl - cylinder to to bits 6-7
	shl cl, 6

	mov dh, [bp + 10]; dh - head

	mov al, [bp + 8]; cl - sectory to bits 0-5
	and al, 3Fh
	or cl, al		

	mov al, [bp + 12]; count

	mov bx, [bp + 16]; es:bx - far pointer to data out
	mov es, bx
	mov bx, [bp + 14]

	; call
	mov al, 02h
	std
	int 13h

	mov ax, 1
	sbb ax, 0		; 1 is true 0 is false

	; restore old call frame
	mov sp, bp
	pop bp
	ret



; bool _cdelc x86_Disk_GetDriveParams(uint8_t drive,
;									uint8_t* driveTypeOut,
;									uint16_t* cylindersOut,
;									uint16_t* sectorsOut,
;									uint16_t* headsOut);
global _x86_Disk_GetDriveParams
_x86_Disk_GetDriveParams:
	; make new call frame
	push bp				; save old frame
	mov bp, sp			; init new frame

	; save regs
	push es
	push bx
	push si
	push di

	; call int13h
	mov dl, [bp + 4]	;dl - drive
	mov ah, 08h
	mov di, 0			;es:di - 0000:0000
	mov es, di
	stc
	int 13h

	; return
	mov ax, 1
	sbb ax, 0

	; out params
	mov si, [bp + 6]	; drive type
	mov [si], bl

	mov bl, ch			; cyl - lower bits in ch
	mov bh, cl			; cyl - upper bits in ch (6-7)
	shr bh, 6
	mov si, [bp + 8]
	mov [si], bx

	xor ch, ch			; sectors - lower 5 bits of cl
	and cl, 3Fh
	mov si, [bp + 10]
	mov [si], cx

	mov cl, dh
	mov si, [bp + 12]
	mov [si], cx

	; restore regs
	pop di
	pop si
	pop bx
	pop es

	; restore old call frame
	mov sp, bp
	pop bp
	ret