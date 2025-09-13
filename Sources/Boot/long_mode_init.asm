extern kernel_main
extern mb_magic
extern mb_info

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

    mov rdi, [mb_magic]      ; magic number -> first arg
    mov rsi, [mb_info]      ; multiboot2 info pointer -> second arg

	call kernel_main

	hlt
