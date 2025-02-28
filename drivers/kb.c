#include "../include/kb.h"
#include "../include/vga.h"
#include "../include/printf.h"
#include "../include/ports.h"

// Keyboard buffer (to store key presses)
#define KEYBOARD_BUFFER_SIZE 128
char kbBuffer[KEYBOARD_BUFFER_SIZE];
uint32_t bufferIndex = 0;

// ASCII map for key codes (simplified)
const char keyMap[] = {
    0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 
    0, 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '[', ']', '\n', 
    0, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ';', '\'', 0, '\\', 
    'Z', 'X', 'C', 'V', 'B', 'N', 'M', ',', '.', '/', 0, '*', 0, ' ', 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

// Function to initialize the keyboard
void initKb() {
    // Initialize the keyboard controller and enable IRQ1
    outb(0x21, inb(0x21) & ~0x02);  // Mask interrupt 1 (enable keyboard IRQ)
    // Set up IRQ1 handler (you need to do this with your IDT)
    // For now, let's assume that keyboardHandler() is called for IRQ1.
}

// The keyboard interrupt handler
void kbHandler() {
    uint8_t scancode = inb(0x60);  // Read from the keyboard data port

    // Ignore any spurious interrupt (scancode 0xFF is a common spurious code)
    if (scancode == 0xFF) return;

    // Check if the buffer is full (prevent overflow)
    if (bufferIndex < KEYBOARD_BUFFER_SIZE) {
        // Process the key press (using a simple keymap)
        if (scancode < sizeof(keyMap)) {
            keyboardBuffer[bufferIndex++] = keyMap[scancode];
        }
    }

    // Send End Of Interrupt (EOI) to the PIC
    outb(0x20, 0x20);  // EOI to PIC1
}

// Function to retrieve the next key from the buffer
char getKey() {
    if (bufferIndex > 0) {
        // Return the first character in the buffer
        char key = keyboardBuffer[0];
        
        // Shift the rest of the buffer
        for (uint32_t i = 1; i < bufferIndex; i++) {
            keyboardBuffer[i - 1] = keyboardBuffer[i];
        }
        
        bufferIndex--;  // Decrease the buffer index
        return key;
    }
    
    return 0;  // Return null if the buffer is empty
}

