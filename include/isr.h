#ifndef ISR_H
#define ISR_H

#include "types.h"

// Declare the default ISR handler
void isr_default();

// Declare IRQ1 handler (keyboard)
void irq1_handler();

#endif // ISR_H

