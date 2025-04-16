#include "../../include/shell/shell.h"
#include "../../include/video/vga.h"
#include "../../include/keyboard/kb.h"
#include "../../include/lib/string.h"
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

int last_exit_status = 0;

// Shell prompt that exactly matches Bash's default appearance
void print_shell_prompt(void) {
    // Username in green (matches Bash's default)
    vga_set_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK);
    vga_puts("root");
    
    // @ symbol in default color
    vga_set_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    vga_puts("@");
    
    // Hostname in green (first part only, before any dots)
    vga_set_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK);
    vga_puts("Bunix");
    
    // Colon and path in blue
    vga_set_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    vga_puts(":");
    vga_set_color(VGA_COLOR_LIGHT_BLUE, VGA_COLOR_BLACK);
    
    // Current directory (replace with actual path logic)
    char* cwd = "/";  // In a real implementation, get current working directory
    if (strcmp(cwd, "/") == 0) {
        vga_puts(cwd);
    } else {
        // For non-root paths, you might want to implement Bash's path shortening
        vga_puts(cwd);
    }
    
    // Dollar sign in white (normal user) or red (root)
    vga_set_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK); // Red for root (like Bash)
    vga_puts("# ");  // Bash uses '#' for root, '$' for normal users
    
    // Reset to default text color
    vga_set_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
}

// Bash-style command list with proper alignment
Command commands[] = {
    {"help",       help_command,      "Display information about builtin commands"},
    {"clear",      clear_command,     "Clear the terminal screen"},
    {"echo",       echo_command,      "Display a line of text"},
    {"cpuinfo",    cpuinfo_command,   "Display CPU information"},
    {"reboot",     reboot_command,    "Stop and restart the system"},
    {"shutdown",   shutdown_command,  "Bring the system down"},
    {"time",       time_command,      "Display or set the system time"},
    {"date",       date_command,      "Display or set the system date"},
    {"uptime",     uptime_command,    "Show how long the system has been running"},
    {"whoami",     whoami_command,    "Print the current user name"},
    {"meminfo",    meminfo_command,   "Display memory usage information"},
    {"cowsay",     cowsay_command,    "Configurable talking cow (requires ASCII art)"},
    {"uname",      uname_command,     "Print system information"},
    {"yes",        yes_command,       "Repeatedly print a string"},
    {"true",       true_main,         "Return success status"},
    {"false",      false_main,        "Return failure status"},
    {"fetch",      fetch_command,     "Displaying OS information"},
    {"sleep",      sleep_command,     "Pause execution for a duration"},
    {"hexdump",    hexdump_command,   "Display binary data in hex"},
    {"expr",       expr_command,      "Calculate entered input"},
    {"grep",       grep_command,      "Search for patterns in input lines"},
    {"factor",     factor_command,    "Factor numbers"},
    {"rand",       rand_command,      "Generate a random number"},
    {"tty",        tty_command,       "Show terminal device name"},
    {"watch",      watch_command,     "Repeat a command every ... seconds"},
    {NULL, NULL, NULL} // End marker
};

// Command history
static char history[MAX_HISTORY_SIZE][256];
static int history_index = 0;

// Add a command to history
void add_to_history(const char *input) {
    strncpy(history[history_index], input, sizeof(history[history_index]) - 1);
    history_index = (history_index + 1) % MAX_HISTORY_SIZE;
}

// Initialize the shell
int shell_init(void) {
    print_shell_prompt();
    uptime_init();  // Initialize uptime
    return 0;
}

// Run the shell
void shell_run(void) {
    char input[256];
    int index = 0;
    
    while (1) {
        // Clear any partial input if we're starting fresh
        if (index == 0) {
            kb_flush();
        }
        
        char c = kb_getchar();
        
        // Handle backspace
        if (c == '\b') {
            if (index > 0) {
                index--;
                vga_putchar('\b');
            }
        }
        // Handle enter
        else if (c == '\n') {
            input[index] = '\0';
            vga_putchar('\n');
            
            if (index > 0) {
                add_to_history(input);
                
                // Parse command
                char *command_name = strtok(input, " ");
                char *args = strtok(NULL, "\0");  // Get remaining string
                
                bool command_found = false;
		for (const Command *cmd = commands; cmd->name != NULL; cmd++) {
	    if (strcmp(command_name, cmd->name) == 0) {
	        // Handle true/false specially
	        if (strcmp(command_name, "true") == 0) {
            last_exit_status = 0;
        } 
        else if (strcmp(command_name, "false") == 0) {
            last_exit_status = 1;
        }
        cmd->func(args);
        command_found = true;
        break;
    }
}

                
                if (!command_found) {
                    vga_set_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
                    vga_puts("sh: ");
                    vga_puts(command_name);
                    vga_puts(": command not found");
                    vga_putchar('\n');
                    vga_set_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
                }
            }
            
            index = 0;
            print_shell_prompt();
        }
        // Handle regular characters
        else if (index < sizeof(input) - 1) {
            input[index++] = c;
            vga_putchar(c);
        }
    }
}

int get_last_exit_status(void) {
    return last_exit_status;
}
