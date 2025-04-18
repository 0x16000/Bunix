#include "../../include/kernel/panic/panic.h"
#include "../../include/video/vga.h"
#include "../../include/kernel/rtc/rtc.h"

// Register structure with packed attribute
struct __attribute__((packed)) Registers {
    uint32_t eax, ebx, ecx, edx, esi, edi;
    uint32_t ebp, esp, eip, eflags;
    uint32_t cs, ds, es, fs, gs, ss;
};

// Stack frame structure for backtrace
struct StackFrame {
    struct StackFrame* next;
    uint32_t return_addr;
};

// Enhanced register dump
static void dump_registers(const struct Registers* regs) {
    vga_set_color(VGA_COLOR_WHITE, VGA_COLOR_BLUE);
    vga_puts("\nRegister Dump:");
    vga_puts("\nEAX: 0x"); vga_puthex(regs->eax);
    vga_puts(" EBX: 0x"); vga_puthex(regs->ebx);
    vga_puts(" ECX: 0x"); vga_puthex(regs->ecx);
    vga_puts(" EDX: 0x"); vga_puthex(regs->edx);
    
    vga_puts("\nESI: 0x"); vga_puthex(regs->esi);
    vga_puts(" EDI: 0x"); vga_puthex(regs->edi);
    vga_puts(" EBP: 0x"); vga_puthex(regs->ebp);
    vga_puts(" ESP: 0x"); vga_puthex(regs->esp);
    
    vga_puts("\nEIP: 0x"); vga_puthex(regs->eip);
    vga_puts(" EFLAGS: 0x"); vga_puthex(regs->eflags);
    
    vga_puts("\nCS: 0x"); vga_puthex(regs->cs);
    vga_puts(" DS: 0x"); vga_puthex(regs->ds);
    vga_puts(" ES: 0x"); vga_puthex(regs->es);
    vga_puts("\nFS: 0x"); vga_puthex(regs->fs);
    vga_puts(" GS: 0x"); vga_puthex(regs->gs);
    vga_puts(" SS: 0x"); vga_puthex(regs->ss);
}

// Stack trace implementation
static void stack_trace(uint32_t max_frames) {
    struct StackFrame* frame;
    __asm__ volatile ("mov %%ebp, %0" : "=r"(frame));
    
    vga_set_color(VGA_COLOR_YELLOW, VGA_COLOR_RED);
    vga_puts("\n\nStack Trace:");
    
    for(uint32_t i = 0; frame && i < max_frames; i++) {
        vga_puts("\n#"); vga_putdec(i, 0);
        vga_puts(" 0x"); vga_puthex(frame->return_addr);
        frame = frame->next;
    }
}

// Panic implementation with system state capture
__attribute__((noreturn)) void panic_impl(const char *file, int line, const char *message) {
    __asm__ volatile ("cli"); // Disable interrupts immediately

    // Save current color state
    uint8_t original_color = vga_get_color();
    
    // Switch to panic colors
    vga_set_color(VGA_COLOR_WHITE, VGA_COLOR_BLUE);
    vga_clear();

    // Display panic header
    vga_puts("\n!!! KERNEL PANIC !!!\n");
    vga_puts("Timestamp: ");
    
    // Get RTC timestamp
    struct rtc_date time;
    rtc_read_full(&time);
    vga_putdec(time.hour, 2); vga_puts(":");
    vga_putdec(time.minute, 2); vga_puts(":");
    vga_putdec(time.second, 2); vga_puts(" ");
    vga_putdec(time.day, 2); vga_puts("/");
    vga_putdec(time.month, 2); vga_puts("/");
    vga_putdec(time.year, 4);

    // Display panic information
    vga_puts("\nFile: "); vga_puts(file);
    vga_puts("\nLine: "); vga_putdec(line, 0);
    vga_puts("\nReason: "); vga_puts(message);

    // Capture register state
    struct Registers regs;
    __asm__ volatile (
        "mov %%eax, %0\n\t"
        "mov %%ebx, %1\n\t"
        "mov %%ecx, %2\n\t"
        "mov %%edx, %3\n\t"
        "mov %%esi, %4\n\t"
        "mov %%edi, %5\n\t"
        "mov %%ebp, %6\n\t"
        "mov %%esp, %7\n\t"
        : "=m"(regs.eax), "=m"(regs.ebx), "=m"(regs.ecx),
          "=m"(regs.edx), "=m"(regs.esi), "=m"(regs.edi),
          "=m"(regs.ebp), "=m"(regs.esp)
    );

    __asm__ volatile (
        "mov %%cs, %0\n\t"
        "mov %%ds, %1\n\t"
        "mov %%es, %2\n\t"
        "mov %%fs, %3\n\t"
        "mov %%gs, %4\n\t"
        "mov %%ss, %5\n\t"
        : "=r"(regs.cs), "=r"(regs.ds), "=r"(regs.es),
          "=r"(regs.fs), "=r"(regs.gs), "=r"(regs.ss)
    );

    __asm__ volatile ("pushfl; pop %0" : "=r"(regs.eflags));
    regs.eip = (uint32_t)__builtin_return_address(0);

    // Dump system state
    dump_registers(&regs);
    stack_trace(10); // Show last 10 stack frames

    // Final message
    vga_set_color(VGA_COLOR_WHITE, VGA_COLOR_BLUE);
    vga_puts("\n\nSystem Halted! You must restart your computer.\n");
    vga_puts("Please report this issue if it persists!");
    
    // Restore original color scheme
    vga_set_color(VGA_COLOR_WHITE, VGA_COLOR_BLUE);

    // Permanent halt
    for(;;) __asm__ volatile ("hlt");
}
