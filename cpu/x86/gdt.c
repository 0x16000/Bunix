#include "gdt.h"

// Global Descriptor Table (GDT) entries
struct gdt_entry gdt[5];
struct gdt_ptr gdtp;

// Function to set a GDT entry
void gdt_set_gate(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) {
    gdt[num].limit_low = limit & 0xFFFF;
    gdt[num].base_low = base & 0xFFFF;
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].access = access;
    gdt[num].granularity = (limit >> 16) & 0x0F;
    gdt[num].granularity |= gran & 0xF0;
    gdt[num].base_high = (base >> 24) & 0xFF;
    gdt[num].reserved = 0;
    gdt[num].base_upper = (base >> 32) & 0xFFFFFFFF;
    gdt[num].reserved2 = 0;
}

// Initialize the GDT for x86_64 (64-bit)
void init_gdt() {
    gdtp.limit = (sizeof(struct gdt_entry) * 5) - 1;
    gdtp.base = (uint32_t)&gdt;

    // Null descriptor (necessary for GDT)
    gdt_set_gate(0, 0, 0, 0, 0);

    // Code segment (0x08)
    gdt_set_gate(1, 0, 0xFFFFFFFFFFFFF, 0x9A, 0xCF);  // 0x9A = present, code, read/write, 64-bit

    // Data segment (0x10)
    gdt_set_gate(2, 0, 0xFFFFFFFFFFFFF, 0x92, 0xCF);  // 0x92 = present, data, read/write, 64-bit

    // User-mode code segment (0x18)
    gdt_set_gate(3, 0, 0xFFFFFFFFFFFFF, 0xFA, 0xCF);  // 0xFA = user-mode, code
    // User-mode data segment (0x20)
    gdt_set_gate(4, 0, 0xFFFFFFFFFFFFF, 0xF2, 0xCF);  // 0xF2 = user-mode, data

    // Load the GDT pointer into the GDTR
    gdt_flush((uint32_t)&gdtp);
}

// Flush the GDT by loading the GDT pointer into the GDTR
void gdt_flush(uint32_t gdtp) {
    __asm__ volatile(
        "lgdt [%0]"              // Load the GDT descriptor table register
        :
        : "r"(gdtp)
    );
}
