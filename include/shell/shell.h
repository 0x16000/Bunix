#ifndef SHELL_H
#define SHELL_H

#include <stdint.h>

#define SHELL_PROMPT "root@Bunix:/# "

// Constants
#define MAX_HISTORY_SIZE 10  // Define the size of the command history buffer

// Command structure
typedef struct {
    const char *name;
    void (*func)(const char *);
    const char *description;
} Command;

extern int last_exit_status;

char kb_getchar(void);  // Reads one character from input
                        
extern Command commands[];  // expose the commands to array struct

// Command function prototypes
void print_shell_prompt(void);
void help_command(const char *args);
void clear_command(const char *args);
void echo_command(const char *args);
void cpuinfo_command(const char *args);
void reboot_command(const char *args);
void shutdown_command(const char *args);
void time_command(const char *args);
void date_command(const char *args);
void uptime_command(const char *args);
void whoami_command(const char *args);
void meminfo_command(const char *args);
void cowsay_command(const char *args);
void uname_command(const char *args);
void yes_command(const char *args);
void true_main(const char *args);
void false_main(const char *args);
void fetch_command(const char *args);
void sleep_command(const char *args);
void hexdump_command(const char *args);
void expr_command(const char *args);
void grep_command(const char *args);
void factor_command(const char *args);
void rand_command(const char *args);
void tty_command(const char *args);
void watch_command(const char *args);
int get_last_exit_status(void);

// Shell functions
int shell_init(void);
void shell_run(void);
void uptime_init(void);
void print_shell_prompt(void);

#endif // SHELL_H
