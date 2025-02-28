#ifndef IDT_H
#define IDT_H

#include "types.h"

// Define the IDT entry structure for x86_64
struct idt_entry {
    uint16_t base_low;      // Lower 16 bits of the address to jump to when this interrupt is triggered
    uint16_t sel;           // Kernel segment selector
    uint8_t  always0;       // Always 0 (unused)
    uint8_t  flags;         // Flags (interrupt gate type, privilege level, etc.)
    uint16_t base_high;     // Upper 16 bits of the address
    uint32_t base_upper;    // Upper 32 bits of the address (for 64-bit addressing)
    uint32_t reserved;      // Reserved field, should be zero
} __attribute__((packed));

// Define the IDT pointer structure for x86_64
struct idt_ptr {
    uint16_t limit;         // Size of the IDT
    uint64_t base;          // Base address of the IDT (64-bit address)
} __attribute__((packed));

// Declare the IDT and the pointer
extern struct idt_entry idt[256];
extern struct idt_ptr idtp;

// Functions for setting up the IDT and loading it
void initIDT();
void setIDTEntry(uint8_t num, uint64_t base, uint16_t sel, uint8_t flags);

#endif // IDT_H
