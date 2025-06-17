[BITS 64]

[GLOBAL load_interrupt_descriptor_table]
; extern void load_interrupt_descriptor_table(void* _interrupt_descriptor_table_ptr)
load_interrupt_descriptor_table:
   lidt [rdi] ; load the IDT pointer.
   ret