#include <vga.h>
#include <fb.h>
#include <kb.h>
#include <shell.h>
#include <limine.h>

// Limine requests
static volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0
};

void kernel_main(void) {
    // Initialize VGA text mode
    vga_initialize();
    vga_puts("Bunix 0.1\n");

    // Check if Limine provided a framebuffer
    if (framebuffer_request.response == NULL || framebuffer_request.response->framebuffer_count < 1) {
        vga_puts("No framebuffer available. Falling back to VGA text mode.\n");
    } else {
        // Get the first framebuffer
        struct limine_framebuffer* framebuffer = framebuffer_request.response->framebuffers[0];

        // Initialize the framebuffer
        struct framebuffer fb = {
            .base_address = framebuffer->address,
            .width = framebuffer->width,
            .height = framebuffer->height,
            .pixels_per_scanline = framebuffer->pitch / 4, // Assuming 32-bit pixels
            .format = framebuffer->bpp
        };

        // Clear the screen with a dark blue color
        framebuffer_clear(&fb, 0x000033);

        // Draw "Bunix 0.1" in white
        framebuffer_draw_text(&fb, "Bunix 0.1 (Framebuffer Mode)", 100, 100, 0xFFFFFF);

        vga_puts("Framebuffer initialized successfully.\n");
    }

    // Initialize the keyboard
    kb_initialize();

    // Start the interactive shell
    shell_run();

    // Hang forever
    for (;;) __asm__("hlt");
}