#include "../include/shell/shell.h"
#include "../include/video/vga.h"
#include "../include/lib/string.h"
#include "../include/keyboard/kb.h"
#include <stdbool.h>

// Improved delay with ESC check that maintains command repetition
static int delay_with_escape(unsigned int seconds) {
    volatile unsigned int i, j;
    for (i = 0; i < seconds; i++) {
        for (j = 0; j < 1000000; j++) {
            if (kb_check_escape() || (kb_ctrl_pressed() && kb_getchar() == 'c')) {
                return 1;
            }
        }
    }
    return 0;
}

void watch_command(const char *args) {
    const char *command = NULL;
    int interval = 2;
    int parsing = 1;

    // Parse arguments
    while (parsing && args && *args) {
        while (*args == ' ') args++;
        
        if (strncmp(args, "-n ", 3) == 0) {
            args += 3;
            interval = 0;
            while (*args >= '0' && *args <= '9') {
                interval = interval * 10 + (*args - '0');
                args++;
            }
            if (interval <= 0) {
                vga_puts("watch: invalid interval\n");
                return;
            }
        } else {
            command = args;
            parsing = 0;
        }
    }

    if (!command || !*command) {
        vga_puts("Usage: watch [-n sec] <command>\n");
        return;
    }

    // Store the full command for repetition
    char full_command[256];
    strncpy(full_command, command, sizeof(full_command)-1);
    full_command[sizeof(full_command)-1] = '\0';

    // Extract just the command name (first word)
    char cmd_name[32] = {0};
    const char *space = strchr(full_command, ' ');
    if (space) {
        strncpy(cmd_name, full_command, space - full_command);
    } else {
        strncpy(cmd_name, full_command, sizeof(cmd_name)-1);
    }

    vga_puts("Every ");
    if (interval >= 10) vga_putchar('0' + interval/10);
    vga_putchar('0' + interval%10);
    vga_puts("s: ");
    vga_puts(full_command);
    vga_puts("\n(Press ESC or Ctrl+C to stop)\n\n");

    while (1) {
        // Re-parse arguments each iteration in case they change
        const char *cmd_args = NULL;
        if (space) {
            cmd_args = space + 1;
            while (cmd_args && *cmd_args == ' ') cmd_args++;
        }

        // Execute command
        bool found = false;
        for (const Command *cmd = commands; cmd->name != NULL; cmd++) {
            if (strcmp(cmd_name, cmd->name) == 0) {
                cmd->func(cmd_args);
                found = true;
                break;
            }
        }
        
        if (!found) {
            vga_puts("watch: command not found: ");
            vga_puts(cmd_name);
            vga_putchar('\n');
            return;
        }

        // Check for interrupt during execution
        if (kb_check_escape() || (kb_ctrl_pressed() && kb_getchar() == 'c')) {
            vga_puts("\n[watch interrupted]\n");
            kb_flush();
            return;
        }

        // Delay with escape check
        if (delay_with_escape(interval)) {
            vga_puts("\n[watch interrupted]\n");
            kb_flush();
            return;
        }

        vga_puts("\n---\n");
    }
}
