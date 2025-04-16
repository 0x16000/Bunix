# Compiler and linker settings
CC = gcc
AS = nasm
LD = ld
CFLAGS = -m32 -ffreestanding -fno-stack-protector -Iinclude
ASFLAGS = -f elf32
LDFLAGS = -m elf_i386 -T linker.ld
ISO_TOOL = grub-mkrescue
QEMU = qemu-system-x86_64

# Directories
SRC_DIR = .
OBJ_DIR = obj
ISO_DIR = isodir
BOOT_DIR = $(ISO_DIR)/boot
BIN_DIR = bin
INCLUDE_DIR = include
USR_BIN_DIR = usr.bin

# Source files
SRCS = \
    init/main.c \
    drivers/video/vga.c \
    drivers/keyboard/kb.c \
    drivers/shell/shell.c \
    lib/libc/string/string.c \
    sys/syscall/syscall.c \
    sys/rtc/rtc.c \
	sys/panic/panic.c \
	sys/panic/boot.c \
	sys/arch/x86/cpu.c \
	sys/panic/debug.c \
    mm/vmm.c

# Bin folder source files
BIN_SRCS = \
    $(BIN_DIR)/clear.c \
    $(BIN_DIR)/echo.c \
    $(BIN_DIR)/cpuinfo.c \
    $(BIN_DIR)/reboot.c \
    $(BIN_DIR)/shutdown.c \
    $(BIN_DIR)/time.c \
    $(BIN_DIR)/date.c \
    $(BIN_DIR)/uptime.c \
    $(BIN_DIR)/help.c \
    $(BIN_DIR)/whoami.c \
    $(BIN_DIR)/meminfo.c \
    $(BIN_DIR)/cowsay.c \
	$(BIN_DIR)/yes.c \
	$(BIN_DIR)/uname.c \
	$(BIN_DIR)/fetch.c \
	$(BIN_DIR)/sleep.c \
	$(BIN_DIR)/hexdump.c \
	$(BIN_DIR)/expr.c \
	$(BIN_DIR)/grep.c \
	$(BIN_DIR)/factor.c \
	$(BIN_DIR)/rand.c \
	$(BIN_DIR)/tty.c \
	$(BIN_DIR)/watch.c \
	$(USR_BIN_DIR)/true.c \
	$(USR_BIN_DIR)/false.c

# Object files
OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRCS))
BIN_OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(BIN_SRCS))
BOOT_OBJ = $(OBJ_DIR)/boot.o

# Output files
KERNEL_ELF = kernel.elf
ISO_IMAGE = bunix.iso

# Default target
all: $(ISO_IMAGE)

# Rule to compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Rule to compile bin folder source files into object files
$(OBJ_DIR)/$(BIN_DIR)/%.o: $(BIN_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Rule to assemble boot.s into an object file
$(BOOT_OBJ): init/boot.s
	@mkdir -p $(OBJ_DIR)
	$(AS) $(ASFLAGS) $< -o $@

# Rule to link object files into the kernel ELF
$(KERNEL_ELF): $(BOOT_OBJ) $(OBJS) $(BIN_OBJS)
	$(LD) $(LDFLAGS) -o $@ $^
	@mkdir -p $(BOOT_DIR)
	cp $(KERNEL_ELF) $(BOOT_DIR)/$(KERNEL_ELF)

# Rule to create the ISO image
$(ISO_IMAGE): $(KERNEL_ELF)
	$(ISO_TOOL) -o $@ $(ISO_DIR)

# Rule to run the ISO in QEMU
run: $(ISO_IMAGE)
	$(QEMU) -enable-kvm -cdrom $(ISO_IMAGE) -m 1024

# Clean up build artifacts
clean:
	rm -rf $(OBJ_DIR) $(KERNEL_ELF) $(ISO_IMAGE) $(BOOT_DIR)/$(KERNEL_ELF)

.PHONY: all clean run
