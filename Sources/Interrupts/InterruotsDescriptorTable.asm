[BITS 64]

[GLOBAL load_idt]
; extern void load_idt(void* idt_ptr)
load_idt:
   lidt [rdi] ; load the IDT pointer.
   ret