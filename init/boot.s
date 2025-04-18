section .multiboot
align 4
    dd 0x1BADB002              ; Magic number
    dd 0x00000003              ; Flags
    dd -(0x1BADB002 + 0x03)    ; Checksum

section .text
global _start
extern main
global multiboot_info_ptr      ; Make this symbol globally visible

_start:
    ; Set up stack
    mov esp, stack_top
    
    ; Save multiboot info pointer
    mov [multiboot_info_ptr], ebx
    
    ; Call kernel main
    call main
    
    ; If main returns, halt
    cli
    hlt

section .bss
align 16
stack_bottom:
    resb 16384                 ; 16KB stack
stack_top:
multiboot_info_ptr: 
    resd 1

section .note.GNU-stack noalloc noexec nowrite progbits
