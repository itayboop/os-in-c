[BITS 64]

[GLOBAL load_interrupt_descriptor_table]
; extern void load_interrupt_descriptor_table(InterruptDescriptorTablePtr *ptr)
load_interrupt_descriptor_table:
   lidt [rdi] ; load the IDT pointer.
   ret