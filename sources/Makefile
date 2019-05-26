ASM_SRC = kernel.asm
C_SRC = kernel.c
LD_SRC = link.ld
K_NAME = kernel

CC = gcc
CASM = nasm

all:
	$(CASM) -f elf32 $(ASM_SRC) -o kasm.o
	$(CC) -m32 -c $(C_SRC) -o kc.o
	ld -m elf_i386 -T $(LD_SRC) -o $(K_NAME) kasm.o kc.o

run:
	qemu-system-i386 -kernel $(K_NAME)

clean:
	rm -rf kasm.o kc.o

fclean: clean
	rm -rf $(K_NAME)

re: fclean
	$(MAKE) all
