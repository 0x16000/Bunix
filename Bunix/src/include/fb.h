#ifndef FB_H
#define FB_H

#include <stdint.h>
#include <stddef.h>

struct framebuffer {
    void* base_address;
    size_t width;
    size_t height;
    size_t pixels_per_scanline;
    uint32_t format;
};

void framebuffer_initialize(struct framebuffer* fb);
void framebuffer_putpixel(struct framebuffer* fb, size_t x, size_t y, uint32_t color);
void framebuffer_clear(struct framebuffer* fb, uint32_t color);
void framebuffer_draw_text(struct framebuffer* fb, const char* str, size_t x, size_t y, uint32_t color);

#endif // FRAMEBUFFER_H