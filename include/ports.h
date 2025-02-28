#pragma once
#include <types.h>
#include <stdint.h>

// Port I/O functions
void outb(uint16_t port, uint8_t value);      // Write a byte to a port
uint8_t inb(uint16_t port);                   // Read a byte from a port
void outw(uint16_t port, uint16_t value);     // Write a word (2 bytes) to a port
uint16_t inw(uint16_t port);                  // Read a word (2 bytes) from a port
void outl(uint16_t port, uint32_t value);     // Write a long (4 bytes) to a port
uint32_t inl(uint16_t port);                  // Read a long (4 bytes) from a port

