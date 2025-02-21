CC = gcc
CFLAGS = -m64 -ffreestanding -Wall -Wextra -Iinclude
LDFLAGS = -m elf_x86_64 -Ttext 0x100000

# Directories
SRC_DIR = src
OBJ_DIR = obj
BUNIX_DIR = /home/damien/Bunix
ISO_DIR = $(BUNIX_DIR)/iso
BOOT_DIR = $(ISO_DIR)/boot

# Output files
KERNEL = $(BOOT_DIR)/kernel.elf
ISO = $(BUNIX_DIR)/bunix.iso

# Source and object files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

.PHONY: all clean run

all: $(ISO)

# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
    @mkdir -p $(OBJ_DIR)
    $(CC) $(CFLAGS) -c $< -o $@

# Link object files into the kernel executable
$(KERNEL): $(OBJS)
    @mkdir -p $(BOOT_DIR)
    $(LD) $(LDFLAGS) -o $@ $^

# Create the ISO image
$(ISO): $(KERNEL)
    @mkdir -p $(BOOT_DIR)
    cp limine/limine.sys $(BOOT_DIR)/
    cp limine.cfg $(BOOT_DIR)/
    xorriso -as mkisofs -b boot/limine.sys -no-emul-boot -boot-load-size 4 -boot-info-table -o $@ $(ISO_DIR)/
    limine/limine-install $@

# Clean up build artifacts
clean:
    rm -rf $(OBJ_DIR) $(ISO_DIR) $(ISO)

# Run the ISO in QEMU
run: $(ISO)
    qemu-system-x86_64 -cdrom $(ISO)