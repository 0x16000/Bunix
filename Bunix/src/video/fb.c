#include <fb.h>
#include <stddef.h>
#include <stdint.h>

void framebuffer_initialize(struct framebuffer* fb) {
    // Limine provides the framebuffer information, so no initialization is needed here.
    // The framebuffer struct is populated by the Limine bootloader.
}

void framebuffer_putpixel(struct framebuffer* fb, size_t x, size_t y, uint32_t color) {
    if (x >= fb->width || y >= fb->height) {
        return; // Out of bounds
    }

    uint32_t* pixel = (uint32_t*)((uintptr_t)fb->base_address + (y * fb->pixels_per_scanline + x) * 4);
    *pixel = color;
}

void framebuffer_clear(struct framebuffer* fb, uint32_t color) {
    for (size_t y = 0; y < fb->height; y++) {
        for (size_t x = 0; x < fb->width; x++) {
            framebuffer_putpixel(fb, x, y, color);
        }
    }
}

void framebuffer_draw_text(struct framebuffer* fb, const char* str, size_t x, size_t y, uint32_t color) {
    // Simple font rendering (8x8 font)
    for (size_t i = 0; str[i] != '\0'; i++) {
        char c = str[i];
        for (size_t dy = 0; dy < 8; dy++) {
            for (size_t dx = 0; dx < 8; dx++) {
                if ((c & (1 << dx))) {
                    framebuffer_putpixel(fb, x + i * 8 + dx, y + dy, color);
                }
            }
        }
    }
}