extern kernel_main

section .text
bits 64

global long_mode_start
long_mode_start:
	; load 0 into all data segment registers
	xor ax, ax
	mov ss, ax
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	jmp kernel_main

	hlt
