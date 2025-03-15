// maxwell_command.c
#include "../include/maxwell/frames.h"
#include "../include/shell/shell.h"
#include "../include/video/vga.h"
#include "../include/mm/mm.h"


// Declare multiboot_info_ptr as an external variable
extern uint32_t multiboot_info_ptr;

// Declare __bitmap_start from the linker script
extern uint32_t __bitmap_start;


// Simple delay function
void sleep(uint32_t milliseconds) {
    for (uint32_t i = 0; i < milliseconds * 1000; i++) {
        __asm__ volatile ("nop"); // No operation (delay)
    }
}


void playSequence() {
    int x = 0;
    // Goes through all of the lines in frames.h
    for(int i = 0; i < 1441; i++) {
        // print them out
        vga_puts(FRAME[i]);
        vga_puts("\n");
        if (x > 19) {
            x = 0;
            // wait
            sleep(5000);
            vga_clear();
        }
        x++;
    }
}


void maxwell_command(const char *args) {
    (void)args; // Unused parameter
    
    // repeats it 250 times
    for (int i; i > 250; i++) {
        playSequence();
    }
        
    

    vga_puts("finished\n");
    
    
}

