#include "../include/vga.h"
#include "../include/printf.h"
#include "../include/keyboard.h"
#include "../include/idt.h"
#include "../include/malloc.h"

void kernel_main() {
    // Initialize IDT (Interrupt Descriptor Table)
    initIDT();

    // Initialize Keyboard (or any other drivers)
    initKb();

    // Initialize memory management (malloc/free)
    init_memory();

    // Print a message to confirm that the kernel is running
    printf("Bunix 0.1\n");

    // Enable interrupts globally (important for handling interrupts like keyboard)
    __asm__ __volatile__ ("sti");

    // Allocate some memory using malloc (just as an example)
    void* ptr1 = malloc(100);  // Allocate 100 bytes
    printf("Allocated memory at: %p\n", ptr1);

    // Optionally, allocate more memory and demonstrate usage
    void* ptr2 = malloc(200);  // Allocate 200 bytes
    printf("Allocated more memory at: %p\n", ptr2);

    // Start the shell loop or any other logic
    while (1) {
        // For example, process keyboard input
        char key = getKey();
        if (key) {
            printf("Key pressed: %c\n", key);
        }

        // Optionally, you can free memory after use (if needed)
        // free(ptr1);
        // free(ptr2);
    }
}
