#include <shell.h>
#include <keyboard.h>
#include <vga.h>
#include <stddef.h>
#include <stdbool.h>

#define SHELL_PROMPT "$ "

static char input_buffer[256];
static size_t input_index = 0;

void shell_handle_command(const char* command) {
    if (strcmp(command, "help") == 0) {
        vga_puts("Available commands:\n");
        vga_puts("  help - Show this help message\n");
        vga_puts("  clear - Clear the screen\n");
    } else if (strcmp(command, "clear") == 0) {
        vga_clear();
    } else {
        vga_puts("Unknown command: ");
        vga_puts(command);
        vga_puts("\n");
    }
}

void shell_run(void) {
    vga_puts("Bunix 0.1 - Simple Interactive Shell\n");
    vga_puts(SHELL_PROMPT);

    while (1) {
        char c = kb_read_char();

        if (c == '\n') {
            // Execute command
            input_buffer[input_index] = '\0';
            shell_handle_command(input_buffer);

            // Reset input buffer
            input_index = 0;
            vga_puts(SHELL_PROMPT);
        } else if (c == '\b') {
            // Handle backspace
            if (input_index > 0) {
                input_index--;
                vga_putchar('\b');
                vga_putchar(' ');
                vga_putchar('\b');
            }
        } else {
            // Add character to input buffer
            if (input_index < sizeof(input_buffer) {
                input_buffer[input_index++] = c;
                vga_putchar(c);
            }
        }
    }
}