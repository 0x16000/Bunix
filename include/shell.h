#ifndef SHELL_H
#define SHELL_H

#include "types.h"

// Function to initialize the shell
void initShell();

// Function to display a prompt and read user input
void readInput(char *inputBuffer);

// Function to execute the user command
void executeCommand(char *inputBuffer);

// Function to print the shell prompt
void printPrompt();

#endif // SHELL_H

