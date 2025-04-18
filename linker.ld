ENTRY(_start)

PHDRS {
    headers PT_PHDR PHDRS ;
    text PT_LOAD FILEHDR PHDRS FLAGS((1 << 0) | (1 << 2)); /* RX */
    rodata PT_LOAD FLAGS(1 << 2);                          /* R */
    data PT_LOAD FLAGS((1 << 1) | (1 << 2));               /* RW */
    bss PT_LOAD FLAGS((1 << 1) | (1 << 2));                /* RW */
}

SECTIONS {
    . = 1M;

    /* Multiboot header must be at the very start */
    .boot : {
        *(.multiboot)
        *(.boot)
    } :text

    .text : ALIGN(4K) {
        *(.text*)
    } :text

    .rodata : ALIGN(4K) {
        *(.rodata*)
    } :rodata

    .data : ALIGN(4K) {
        *(.data)
    } :data

    .bss : ALIGN(4K) {
        *(COMMON)
        *(.bss)
        *(.stack)
    } :bss

    /* Bitmap section */
    . = ALIGN(4K);
    __bitmap_start = .;
    . += 4K;

    /DISCARD/ : {
        *(.comment)
        *(.eh_frame)
    }
}
