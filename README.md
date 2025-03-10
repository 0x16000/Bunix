# Compile the source files in 32-bit mode
gcc -m32 -ffreestanding -fno-stack-protector -c init/main.c -o init/main.o
gcc -m32 -ffreestanding -fno-stack-protector -c drivers/video/vga.c -o drivers/video/vga.o
gcc -m32 -ffreestanding -fno-stack-protector -c drivers/keyboard/kb.c -o drivers/keyboard/kb.o
gcc -m32 -ffreestanding -fno-stack-protector -c drivers/shell/shell.c -o drivers/shell/shell.o
gcc -m32 -ffreestanding -fno-stack-protector -c lib/libc/string/string.c -o lib/libc/string/string.o
gcc -m32 -ffreestanding -fno-stack-protector -c lib/libc/memmove/memmove.c -o lib/libc/memmove/memmove.o
gcc -m32 -ffreestanding -fno-stack-protector -c sys/syscall/syscall.c -o sys/syscall/syscall.o 

# Link the object files
ld -m elf_i386 -T linker.ld -o kernel.elf \
    init/main.o \
    drivers/video/vga.o \
    drivers/keyboard/kb.o \
    drivers/shell/shell.o \
    lib/libc/string/string.o \
    lib/libc/memmove/memmove.o \
    sys/syscall/syscall.o 

# Optionally, create a raw binary
objcopy -O binary kernel.elf kernel.bin

# Copy kernel over to grub
mkdir -p isodir/boot/grub 
cp kernel.elf isodir/boot/kernel.elf

# Create ISO
grub-mkrescue -o bunix.iso isodir

# Finally run the ISO
qemu-system-x86_64 -cdrom bunix.iso


