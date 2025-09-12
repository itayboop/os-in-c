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

    pop rax
    pop rbx
    ; zero-extend 32-bit magic/info to 64-bit registers
    mov rdi, rax      ; magic number -> first arg
    mov rsi, rbx      ; multiboot2 info pointer -> second arg

	call kernel_main

	hlt
