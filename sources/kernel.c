#include "kernel.h"
#include "keyboard.h"

unsigned int j = 0;
char *vidptr = (char *)VGA_ADDRESS;
unsigned int current_loc = 0;

unsigned int	new_line()
{
	if (current_loc / 2 % 80 == 0)
		current_loc += 2;
	while (current_loc / 2 % 80)
		current_loc += 2;
	return (current_loc);
}

void kb_init(void)
{
	print("kb_init\n");
	/* 0xFD is 11111101 - enables only IRQ1 (keyboard)*/
	write_port(0x21 , 0xFD);
}

void keyboard_handler_main(void) {
	unsigned char status;
	char keycode;
	/* write EOI */
	
//		write_port(0x20, 0x20);
	//	print("in keyboard handler\n");
		status = read_port(KEYBOARD_STATUS_PORT);
		/* Lowest bit of status will be set if buffer is not empty */
		if (status & 0x01)
		{
			keycode = read_port(KEYBOARD_DATA_PORT);
			if(keycode < 0)
			{	
			//	print("in keyboard_handler keycode < 0 so return is called\n");
				return;
			}
			if (keyboard_map[keycode] == '\n')
				current_loc = new_line();
			else
			{
				vidptr[current_loc++] = keyboard_map[keycode];
				vidptr[current_loc++] = GREEN;
			}
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
	while(1)
		keyboard_handler();	

	return;
}
