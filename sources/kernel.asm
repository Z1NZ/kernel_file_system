;;kernel.asm

;nasm directive - 32 bit
bits 32
MAGIC equ 0x1BADB002
FLAGS equ 0x00
CHECKSUM equ - (MAGIC + FLAGS)

section .text
        ;multiboot spec
        align 4
        dd MAGIC
        dd FLAGS
        dd CHECKSUM ;checksum. m+f+c should be zero

global start
extern kmain	        ;kmain is defined in the c file

start:
  cli 			;block interrupts
  mov esp, stack_space	;set stack pointer
  call kmain
  hlt		 	;halt the CPU

section .bss
resb 8192		;8KB for stack
stack_space:
