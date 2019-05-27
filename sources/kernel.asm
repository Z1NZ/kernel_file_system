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
global keyboard_handler
global read_port
global write_port

extern kmain	        ;kmain is defined in the c file
extern keyboard_handler_main

keyboard_handler:                 
	call    keyboard_handler_main
	ret

read_port:
	mov edx, [esp + 4]
	in al, dx	
	ret

write_port:
	mov   edx, [esp + 4]    
	mov   al, [esp + 4 + 4]  
	out   dx, al  
	ret

start:
	cli 			;block interrupts
	mov esp, stack_space	;set stack pointer
	call kmain
	hlt		 	;halt the CPU

section .bss
resb 8192		;8KB for stack
stack_space:
