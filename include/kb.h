#ifndef KB_H
#define KB_H

#include "types.h"

// Keyboard initialization
void initKb();

// Interrupt handler for keyboard input
void kbHandler();

// Function to get the next key pressed
char getKey();

#endif // KB_H
