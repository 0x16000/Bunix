#include <video/vga.h>
#include <mm/vmm.h>
#include <stdint.h>
#include "../include/version/version.h"
// Declaration for calculate_uptime from uptime.c
extern uint32_t calculate_uptime();

// CPUID implementation
static void cpuid(uint32_t reg, uint32_t *eax, uint32_t *ebx, uint32_t *ecx, uint32_t *edx) {
    asm volatile("cpuid"
        : "=a"(*eax), "=b"(*ebx), "=c"(*ecx), "=d"(*edx)
        : "a"(reg));
}

// Get CPU vendor string
static void get_cpu_vendor(char *vendor) {
    uint32_t eax, ebx, ecx, edx;
    cpuid(0, &eax, &ebx, &ecx, &edx);
    
    *((uint32_t*)vendor) = ebx;
    *((uint32_t*)(vendor + 4)) = edx;
    *((uint32_t*)(vendor + 8)) = ecx;
    vendor[12] = '\0';
}

// Revised memory formatting without buffer
static void format_memory(size_t size) {
    const char *units[] = {"B", "KB", "MB", "GB"};
    size_t unit = 0;
    size_t divisor = 1;
    
    // Find appropriate unit
    while (size >= 1024 * divisor && unit < 3) {
        divisor *= 1024;
        unit++;
    }
    
    // Calculate whole units
    size_t whole = size / divisor;
    size_t remainder = size % divisor;
    
    // Print whole part
    vga_putdec(whole, 0);
    
    // Print remainder if relevant
    if (remainder > 0 && unit > 0) {
        vga_putchar('.');
        vga_putdec((remainder * 10) / divisor, 1); // Single decimal digit
    }
    
    vga_puts(units[unit]);
}

void fetch_command(void) {
    vga_clear();
    vga_set_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    
    // Tiny ASCII art (customize this)
    vga_set_color(VGA_COLOR_LIGHT_CYAN, VGA_COLOR_BLACK);
    vga_puts("  /\\ /\\\n");
    vga_puts(" ( . . )\n");
    vga_puts("  ( v )\n");
    
    // Get system information
    char cpu_vendor[13];
    get_cpu_vendor(cpu_vendor);
    
    size_t total_mem = vmm_get_total_pages() * PAGE_SIZE;
    size_t used_mem = vmm_get_used_pages() * PAGE_SIZE;
    size_t free_mem = vmm_get_free_pages() * PAGE_SIZE;
    
    // Display system info in columns
    int info_x = 15;
    int y = 0;
    
    vga_move_cursor(info_x, y++);
    vga_set_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK);
    vga_puts("OS: ");
    vga_set_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
    vga_puts(BUNIX_NAME);
    
    vga_move_cursor(info_x, y++);
    vga_set_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK);
    vga_puts("Kernel: ");
    vga_set_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
    vga_puts(BUNIX_VERSION);
    
    vga_move_cursor(info_x, y++);
    vga_set_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK);
    vga_puts("CPU: ");
    vga_set_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
    vga_puts(cpu_vendor);
    
    vga_move_cursor(info_x, y++);
    vga_set_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK);
    vga_puts("Memory: ");
    vga_set_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
    format_memory(used_mem);
    vga_puts(" / ");
    format_memory(total_mem);
    
    // Display uptime
    vga_move_cursor(info_x, y++);
    vga_set_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK);
    vga_puts("Uptime: ");
    vga_set_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
    
    uint32_t uptime_seconds = calculate_uptime();
    uint32_t days = uptime_seconds / 86400;
    uptime_seconds %= 86400;
    uint32_t hours = uptime_seconds / 3600;
    uptime_seconds %= 3600;
    uint32_t minutes = uptime_seconds / 60;
    
    vga_putdec(days, 0);
    vga_puts("d ");
    vga_putdec(hours, 0);
    vga_puts("h ");
    vga_putdec(minutes, 0);
    vga_puts("m");
    
    // Add separator line
    vga_move_cursor(0, y+1);
    vga_set_color(VGA_COLOR_DARK_GREY, VGA_COLOR_BLACK);
    vga_puts("------------------------------\n");
}
