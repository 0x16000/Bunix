    .global load_idt
load_idt:
    lidt [ebx]       ; Load the IDT pointer into the IDT register
    ret

