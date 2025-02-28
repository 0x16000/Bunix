#include "vga.h"

// The BIOS/UEFI GOP provided framebuffer...
static volatile struct limine_framebuffer_request limineFBreq = {
    .id = LIMINE_FRAMEBUFFER_REQUEST, .revision = 0};

// Declare framebuffer variables
uint8_t *framebuffer;
uint32_t framebufferWidth, framebufferHeight, framebufferPitch;

// Cursor position and visibility
uint32_t cursorX = 0, cursorY = 0;
uint8_t cursorVisible = 1; // 1 for visible, 0 for hidden

void initVGA() {
    // Get the framebuffer from the Limine request
    struct limine_framebuffer *framebufferRes =
        limineFBreq.response->framebuffers[0];

    // Setup framebuffer properties
    framebuffer = (uint8_t *)framebufferRes->address;
    framebufferHeight = framebufferRes->height;
    framebufferWidth = framebufferRes->width;
    framebufferPitch = framebufferRes->pitch;
}

void updateCursor() {
    if (cursorVisible) {
        drawCursor();  // Draw the cursor if it should be visible
    } else {
        // Optionally clear the cursor by drawing the background (if needed)
        drawCursor();  // Overwrite the cursor position with background (or empty)
    }
}

void drawCursor() {
    // Assuming a 16x16 cursor (simple block or vertical line)
    uint32_t offset = cursorY * framebufferPitch + cursorX * 4;

    // Example of drawing a simple cursor as a vertical line (16px high)
    if (cursorVisible) {
        for (int i = 0; i < 16; ++i) {
            framebuffer[offset + i * framebufferPitch] = 0xFF;       // Blue channel
            framebuffer[offset + 1 + i * framebufferPitch] = 0x00;   // Green channel
            framebuffer[offset + 2 + i * framebufferPitch] = 0x00;   // Red channel (red cursor)
            framebuffer[offset + 3 + i * framebufferPitch] = 0xFF;   // Alpha channel
        }
    }
}

// Call this periodically to toggle cursor visibility
void toggleCursor() {
    cursorVisible = !cursorVisible;
}
