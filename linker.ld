ENTRY(start)

SECTIONS {
    . = 1M;

    .multiboot2_header :
    {
        /* ensure that the multiboot header is at the beginning */
        KEEP(*(.multiboot2_header))
    }

    .bootdata : {
       *(.bootdata)
    }

    .text :
    {
        *(.text .text.*)
    }

    /* TODO: do i really need this? looks like its for rust only. https://os.phil-opp.com/allocating-frames/ */
    .rodata : {
        *(.rodata .rodata.*)
    }

    .data.rel.ro : {
        *(.data.rel.ro.local*) *(.data.rel.ro .data.rel.ro.*)
    }

    .bss : {
        *(.bss)
        *(COMMON)
        __end = .;
    }
}