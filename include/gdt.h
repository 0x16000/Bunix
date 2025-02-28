#pragma once
#include <stdint.h>

// GDT Entry Structure (64-bit compatible)
struct gdt_entry {
    uint16_t limit_low;          // Lower 16 bits of the limit
    uint16_t base_low;           // Lower 16 bits of the base address
    uint8_t base_middle;         // Next 8 bits of the base address
    uint8_t access;              // Access flags (present, ring level, type)
    uint8_t granularity;         // Granularity and higher 4 bits of the limit
    uint8_t base_high;           // Upper 8 bits of the base address
    uint8_t reserved;            // Reserved field (must be 0)
    uint8_t base_upper;          // Upper 8 bits of the base address (64-bit addressing)
    uint32_t reserved2;          // Reserved field (must be 0)
} __attribute__((packed));

// GDT Pointer Structure
struct gdt_ptr {
    uint16_t limit;              // Limit of the GDT (size - 1)
    uint32_t base;               // Base address of the GDT
} __attribute__((packed));

// GDT function prototypes
void init_gdt();
void gdt_flush(uint32_t);

extern struct gdt_entry gdt[5];   // GDT entries (including null descriptor, code, data, etc.)
extern struct gdt_ptr gdtp;       // GDT pointer
