SRC_PATH = ./sources/
OBJ_PATH = ./obj/

ASM_SRC = kernel.asm
C_SRC = kernel.c display.c utils.c tty_handler.c
LD_SRC = link.ld
K_NAME = kfs1

INC = ./include/

OBJ_NAME = $(C_SRC:.c=.o)

SRC_C = $(addprefix $(SRC_PATH), $(C_SRC))
SRC_ASM = $(addprefix $(SRC_PATH), $(ASM_SRC))
SRC_LD = $(addprefix $(SRC_PATH), $(LD_SRC))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))

CC = gcc
CASM = nasm
FLAGS = -m32 -fno-builtin -fno-exceptions -fno-stack-protector -nostdlib -nodefaultlibs

all:
	$(CASM) -f elf32 $(SRC_ASM) -o kasm.o
	$(CC) -I $(INC) $(FLAGS) $(SRC_C) -c
	ld -m elf_i386 -T $(SRC_LD) -o $(K_NAME) *.o

run:
	qemu-system-i386 -kernel $(K_NAME)

clean:
	rm -rf *.o

fclean: clean
	rm -rf $(K_NAME)
	rm -rf $(OBJ_PATH)

re: fclean
	$(MAKE) all
