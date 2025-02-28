#include "../include/types.h"

#define HEAP_SIZE 4096  // Define the size of the heap (4KB for this example)

// The heap is a static array of memory
static uint8_t heap[HEAP_SIZE];

// Block header structure to track the size of each allocated block
typedef struct block_header {
    uint32_t size;        // Size of the block (including the header)
    struct block_header* next;  // Pointer to the next block in the list
} block_header_t;

// The free list head points to the first free block
static block_header_t* free_list = NULL;

// Function to initialize the memory manager
void init_memory() {
    free_list = (block_header_t*)heap;  // The first block is the start of the heap
    free_list->size = HEAP_SIZE - sizeof(block_header_t);  // The first block takes the whole heap
    free_list->next = NULL;  // No next block
}

// Malloc implementation using a first-fit strategy
void* malloc(size_t size) {
    // Round the size to the nearest multiple of 4 (for alignment)
    size = (size + 3) & ~3;

    block_header_t* prev = NULL;
    block_header_t* curr = free_list;

    // Traverse the free list to find a block large enough
    while (curr) {
        if (curr->size >= size + sizeof(block_header_t)) {
            // Split the block if it's large enough to fit the request
            if (curr->size > size + sizeof(block_header_t) + sizeof(block_header_t)) {
                block_header_t* next_block = (block_header_t*)((uint8_t*)curr + sizeof(block_header_t) + size);
                next_block->size = curr->size - size - sizeof(block_header_t);
                next_block->next = curr->next;

                curr->size = size;
                curr->next = next_block;
            }

            // Remove the block from the free list
            if (prev) {
                prev->next = curr->next;
            } else {
                free_list = curr->next;
            }

            // Return a pointer to the memory after the block header
            return (void*)((uint8_t*)curr + sizeof(block_header_t));
        }

        prev = curr;
        curr = curr->next;
    }

    return NULL;  // Out of memory
}

// Free implementation that returns a block to the free list
void free(void* ptr) {
    if (!ptr) {
        return;  // No-op if the pointer is NULL
    }

    // Get the block header from the pointer (before the actual data)
    block_header_t* block = (block_header_t*)((uint8_t*)ptr - sizeof(block_header_t));

    // Add the block to the free list
    block->next = free_list;
    free_list = block;
}

