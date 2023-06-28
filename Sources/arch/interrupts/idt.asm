[BITS 64]

%macro ISR_NOERRCODE 1    ; define a macro, taking one parameter
    [GLOBAL isr%1]        ; %1 accesses the first parameter.
    isr%1:
        push 0
        push %1
        jmp isr_common_stub
%endmacro

%macro ISR_ERRCODE 1
    [GLOBAL isr%1]
    isr%1:
        push %1
        jmp isr_common_stub
%endmacro

ISR_NOERRCODE 0
ISR_NOERRCODE 1
ISR_NOERRCODE 2
ISR_NOERRCODE 3
ISR_NOERRCODE 4
ISR_NOERRCODE 5
ISR_NOERRCODE 6
ISR_NOERRCODE 7
ISR_ERRCODE 8
ISR_NOERRCODE 9
ISR_ERRCODE 10
ISR_ERRCODE 11
ISR_ERRCODE 12
ISR_ERRCODE 13
ISR_ERRCODE 14
ISR_NOERRCODE 15
ISR_NOERRCODE 16
ISR_ERRCODE 17
ISR_NOERRCODE 18
ISR_NOERRCODE 19
ISR_NOERRCODE 20
ISR_NOERRCODE 21
ISR_NOERRCODE 22
ISR_NOERRCODE 23
ISR_NOERRCODE 24
ISR_NOERRCODE 25
ISR_NOERRCODE 26
ISR_NOERRCODE 27
ISR_NOERRCODE 28
ISR_NOERRCODE 29
ISR_ERRCODE 30
ISR_NOERRCODE 31
ISR_NOERRCODE 32
ISR_NOERRCODE 33
ISR_NOERRCODE 34
ISR_NOERRCODE 35
ISR_NOERRCODE 36
ISR_NOERRCODE 37
ISR_NOERRCODE 38
ISR_NOERRCODE 39
ISR_NOERRCODE 40
ISR_NOERRCODE 41
ISR_NOERRCODE 42
ISR_NOERRCODE 43
ISR_NOERRCODE 44
ISR_NOERRCODE 45
ISR_NOERRCODE 46
ISR_NOERRCODE 47

[EXTERN isr_handler]

isr_common_stub:
    push rax

    xor rax, rax
    mov rax, [rsp+(4*8)]
    cmp rax, 0x8
    je .skip
    swapgs                  ; for privilege level switching in kernel.
.skip:
    ; save segment register value on stack.
    xor rax, rax
    mov ax, fs
    push rax

    xor rax, rax
    mov ax, es
    push rax

    xor rax, rax
    mov ax, ds
    push rax

    ; 0x10 represents a data segment selector.
    mov rax, 0x10
    mov fs, ax
    mov ds, ax
    mov ss, ax
    mov es, ax

    push rdi
    push rsi
    push rdx
    push rbx
    push rcx
    push rbp
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15
    mov rdi, rsp                ; move "pointer" from rsp to rdi (first parameter).
    mov rbx, rsp
    and rsp, 0xFFFFFFFFFFFFFFF0 ; clearing LS4B for alignment.
    call isr_handler
    mov rsp, rbx
    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop rbp
    pop rcx
    pop rbx
    pop rdx
    pop rsi
    pop rdi

    ; restore segments register values.
    pop rax
    mov ds, ax

    pop rax
    mov es, ax

    pop rax
    mov fs, ax

    mov ax, [rsp+(4*8)]
    cmp rax, 0x8
    je .skip2
    swapgs
.skip2:
    pop rax
    add rsp, 16
    iretq

[GLOBAL load_idt]
; extern void load_idt(void* idt_ptr)
load_idt:
   mov rax, rdi                 ; Get the pointer to the IDT, passed as a parameter.
   lidt [rax]                   ; Load the IDT pointer.
   ret