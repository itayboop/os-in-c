ENTRY(start)

SECTIONS {
    . = 1M;

    .multiboot2_header :
    {
        /* ensure that the multiboot header is at the beginning */
        KEEP(*(.multiboot2_header))
    }

    .text :
    {
        *(.text .text.*)
    }

    .rodata : {
        *(.rodata .rodata.*)
    }

    .data.rel.ro : {
        *(.data.rel.ro.local*) *(.data.rel.ro .data.rel.ro.*)
    }
}