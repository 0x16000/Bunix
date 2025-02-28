    .global load_idt
load_idt:
    lidt [rdi]      ; Load the IDT pointer into the IDT register (using 64-bit registers)
    ret
