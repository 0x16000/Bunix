#include "isr.h"
#include "vga.h"
#include "ports.h"
#include "kb.h"

// Default ISR handler
void isr_default() {
    // Just acknowledge the interrupt by sending an EOI (End Of Interrupt) to the PIC
    outb(0x20, 0x20);  // Send EOI to PIC1
    outb(0xA0, 0x20);  // Send EOI to PIC2 (if needed)
}

// IRQ1 handler (keyboard interrupt)
void irq1_handler() {
    // Read the scancode from the keyboard controller (0x60)
    kbHandler();

    // Send End Of Interrupt to the PIC to acknowledge the interrupt
    outb(0x20, 0x20);  // Send EOI to PIC1
    outb(0xA0, 0x20);  // Send EOI to PIC2 (if needed)
}

