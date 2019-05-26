#include "kernel.h"
#include "keyboard.h"

int i = 0;
int j = 0;
char *vidptr = (char *)VGA_ADDRESS;
unsigned int current_loc = 0;

void	move_y()
{
	while (i / 2 % 80)
		i = i + 2;
}

void kb_init(void)
{
	/* 0xFD is 11111101 - enables only IRQ1 (keyboard)*/
	write_port(0x21 , 0xFD);
}

void keyboard_handler_main(void) {
	unsigned char status;
	char keycode;
	/* write EOI */
	write_port(0x20, 0x20);

	status = read_port(KEYBOARD_STATUS_PORT);
	/* Lowest bit of status will be set if buffer is not empty */
	if (status & 0x01) {
		keycode = read_port(KEYBOARD_DATA_PORT);
		if(keycode < 0)
			return;
		vidptr[current_loc++] = keyboard_map[keycode];
		vidptr[current_loc++] = 0x07;
	}
}

void kmain(void)
{
	char *str = "my first kernel\n";
	
	/* this loops clears the screen
	* there are 25 lines each of 80 columns; each element takes 2 bytes */
	black_screen();
	j = 0;

	/* this loop writes the string to video memory */
	print(str);
	print("dans le kmain\n");
	kb_init();
	while (1)

	return;
}
