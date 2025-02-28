#ifndef VGA_H
#define VGA_H

#include "types.h"

// Function prototypes
void initVGA();
void updateCursor();
void drawCursor();

// Cursor position variables
extern uint32_t cursorX, cursorY;
extern uint8_t cursorVisible;

#endif // VGA_H
