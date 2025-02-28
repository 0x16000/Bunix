#include "ports.h"

// Write a byte to the specified port
void outb(uint16_t port, uint8_t value) {
    __asm__ volatile("outb %0, %1" : : "a"(value), "d"(port));
}

// Read a byte from the specified port
uint8_t inb(uint16_t port) {
    uint8_t result;
    __asm__ volatile("inb %1, %0" : "=a"(result) : "d"(port));
    return result;
}

// Write a word (2 bytes) to the specified port
void outw(uint16_t port, uint16_t value) {
    __asm__ volatile("outw %0, %1" : : "a"(value), "d"(port));
}

// Read a word (2 bytes) from the specified port
uint16_t inw(uint16_t port) {
    uint16_t result;
    __asm__ volatile("inw %1, %0" : "=a"(result) : "d"(port));
    return result;
}

// Write a long (4 bytes) to the specified port
void outl(uint16_t port, uint32_t value) {
    __asm__ volatile("outl %0, %1" : : "a"(value), "d"(port));
}

// Read a long (4 bytes) from the specified port
uint32_t inl(uint16_t port) {
    uint32_t result;
    __asm__ volatile("inl %1, %0" : "=a"(result) : "d"(port));
    return result;
}

