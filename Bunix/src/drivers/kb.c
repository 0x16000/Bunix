#include <kb.h>
#include <stdbool.h>
#include <stddef.h>

#define KB_DATA_PORT 0x60
#define KB_STATUS_PORT 0x64

static bool shift_pressed = false;

// Scancode to ASCII mapping (for US QWERTY keyboard)
static const char scancode_to_ascii[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\',
    'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '-', 0, 0, 0, '+', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

void kb_initialize(void) {
    // No initialization needed for PS/2 keyboard in this simple example
}

char kb_read_char(void) {
    char c = 0;
    while (1) {
        // Wait for a key to be pressed
        if (inb(KB_STATUS_PORT) & 0x01) {
            uint8_t scancode = inb(KB_DATA_PORT);

            // Handle key release (ignore for now)
            if (scancode & 0x80) {
                if (scancode == 0xAA || scancode == 0xB6) {
                    shift_pressed = false;
                }
                continue;
            }

            // Handle shift key
            if (scancode == 0x2A || scancode == 0x36) {
                shift_pressed = true;
                continue;
            }

            // Convert scancode to ASCII
            c = scancode_to_ascii[scancode];
            if (shift_pressed && c >= 'a' && c <= 'z') {
                c -= 32; // Convert to uppercase
            }

            break;
        }
    }
    return c;
}