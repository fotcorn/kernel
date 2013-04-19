# compiler
CC=gcc
LD=ld
CFLAGS=-c -m32 -nostdlib -fno-builtin -nostartfiles -nodefaultlibs -I src -I src/klibc
NASMLFAGS=-f elf

LDFLAGS=-melf_i386 -T src/linker.ld

# files
C_SOURCES=$(wildcard src/*.c) $(wildcard src/klibc/*.c)
C_HEADERS=$(wildcard src/*.h)
C_OBJECTS=$(patsubst src/%.c, build/%.o, $(C_SOURCES))

ASM_SOURCES=src/kernel_asm.asm src/loader.asm 
ASM_OBJECTS=build/kernel_asm.o build/loader.o

KERNEL_BIN=build/kernel.bin
ISO=cd.iso

all: $(ISO)

$(ISO): $(KERNEL_BIN)
	cp $(KERNEL_BIN) iso
	grub-mkrescue -o $(ISO) iso

$(KERNEL_BIN): $(ASM_OBJECTS) $(C_OBJECTS)
	$(LD) $(LDFLAGS) -o $(KERNEL_BIN) $(ASM_OBJECTS) $(C_OBJECTS)
	
build/%.o: src/%.c $(C_HEADERS) build_dir
	$(CC) $(CFLAGS) -o $@ $<

build/%.o: src/%.asm build_dir
	nasm $(NASMLFAGS) -o $@ $<

build_dir:
	mkdir -p build
	mkdir -p build/klibc

clean:
	rm -rf build
	rm -f cd.iso
	
