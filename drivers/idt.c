#include "idt.h"
#include "ports.h"
#include "isr.h"  // Interrupt Service Routine handlers (to be created)

// Define the IDT and IDT pointer
struct idt_entry idt[256];
struct idt_ptr idtp;

// Assembly function to load the IDT
extern void load_idt(uint32_t);

// Function to set an IDT entry
void setIDTEntry(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags) {
    idt[num].base_low = base & 0xFFFF;
    idt[num].base_high = (base >> 16) & 0xFFFF;
    idt[num].sel = sel;
    idt[num].always0 = 0;
    idt[num].flags = flags;
}

// Initialize the IDT
void initIDT() {
    idtp.limit = sizeof(struct idt_entry) * 256 - 1;
    idtp.base = (uint32_t)&idt;

    // Set all the interrupt gates to the default handler
    for (int i = 0; i < 256; i++) {
        setIDTEntry(i, (uint32_t)isr_default, 0x08, 0x8E);  // Default ISR handler
    }

    // Set up IRQ1 (keyboard) handler
    setIDTEntry(33, (uint32_t)irq1_handler, 0x08, 0x8E);  // IRQ1 handler for keyboard

    // Load the IDT
    load_idt((uint32_t)&idtp);
}

// Function to initialize the PIC to send interrupts to the CPU
void initPIC() {
    // Initialize PICs to send IRQs to the CPU
    outb(0x20, 0x11);  // Send ICW1 (initialize the PIC)
    outb(0xA0, 0x11);  // Send ICW1 for slave PIC

    outb(0x21, 0x20);  // Set IRQ base for master PIC (0x20)
    outb(0xA1, 0x28);  // Set IRQ base for slave PIC (0x28)

    outb(0x21, 0x04);  // Tell master PIC about the slave
    outb(0xA1, 0x02);  // Tell slave PIC about master PIC

    outb(0x21, 0x01);  // Enable 8086 mode
    outb(0xA1, 0x01);  // Enable 8086 mode for slave PIC

    outb(0x21, 0x00);  // Enable all interrupts on master PIC
    outb(0xA1, 0x00);  // Enable all interrupts on slave PIC
}
