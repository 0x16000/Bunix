#include "shell.h"
#include "printf.h"
#include "string.h"  // For string manipulation functions like strcmp

// Simple buffer to store the user's input
#define MAX_INPUT_SIZE 128
char inputBuffer[MAX_INPUT_SIZE];

// Function to initialize the shell
void initShell() {
    // You can initialize any shell-specific structures here if needed
    printPrompt();  // Print the shell prompt when the shell starts
}

// Function to display a prompt (e.g., "Bunix> ")
void printPrompt() {
    printf("Bunix> ");
}

// Function to read user input
void readInput(char *inputBuffer) {
    int i = 0;
    char c;

    // Read characters until Enter is pressed (i.e., '\n')
    while (1) {
        c = getchar();  // This assumes you have a function to get a character from stdin

        if (c == '\n') {
            inputBuffer[i] = '\0';  // Null-terminate the input string
            break;
        }

        if (i < MAX_INPUT_SIZE - 1) {
            inputBuffer[i++] = c;  // Store the character in the buffer
        }
    }
}

// Function to execute the command entered by the user
void executeCommand(char *inputBuffer) {
    if (strcmp(inputBuffer, "exit") == 0) {
        // Exit the shell (this can be improved depending on your OS design)
        printf("Exiting shell...\n");
        // You can implement a system to halt or reboot the OS here
    } else if (strcmp(inputBuffer, "help") == 0) {
        // Show basic help information
        printf("Bunix Shell Help:\n");
        printf("  exit   - Exit the shell\n");
        printf("  help   - Show this help message\n");
        // Add more commands as you add them
    } else {
        // Command not found
        printf("Unknown command: %s\n", inputBuffer);
    }
}

// Main shell loop
void shellLoop() {
    while (1) {
        printPrompt();  // Show the shell prompt
        readInput(inputBuffer);  // Read input from the user
        executeCommand(inputBuffer);  // Execute the command
    }
}

