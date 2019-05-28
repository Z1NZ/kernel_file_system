#include "kernel.h"
#include "keyboard.h"
#include "tty_handler.h"

unsigned int j = 0;
unsigned int current_tty = 0;
unsigned int cursor_x;
unsigned int cursor_y;

char *vidptr = (char *)VGA_ADDRESS;
unsigned int current_loc = 0;

unsigned int	new_line()
{
	if (current_loc / 2 % MAX_COLS == 0)
		current_loc += 2;
	while (current_loc / 2 % MAX_COLS)
		current_loc += 2;
	cursor_y++;
//	move_cursor();
	return (current_loc);
}

void kb_init(void)
{
	print("kb_init\n");
	/* 0xFD is 11111101 - enables only IRQ1 (keyboard)*/
	write_port(0x21 , 0xFD);
}

int	is_tty_sym(int keycode)
{
	if (keycode == 0x3b || keycode == 0x3c || keycode == 0x3d)
		return 1;
	return 0;
}

void	keyboard_handler_main(void) {
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
				return;
			if (is_tty_sym(keycode))
			{
				//print("change tty detect\n");
				change_tty(keycode);
				return;
			}
			if (keyboard_map[keycode] == '\n')
				current_loc = new_line();
			else if (keyboard_map[keycode] == '\b')
			{
				if ((current_loc / 2) % MAX_COLS)
				{
					current_loc -= 2;
					vidptr[current_loc] = 0;
//					cursor_x--;
				}
			}
			else
			{
				vidptr[current_loc++] = keyboard_map[keycode];
				vidptr[current_loc++] = GREEN;
			}
			current_loc = handle_scrolling(current_loc);
			set_cursor(current_loc - 1);
		}
}

void kmain(void)
{
	char *str = "my first kernel\n";
	
	black_screen();
	j = 0;

	print(str);
	print_color("we can write in red also \n", RED);
	print_color("even in blue if we wish\n", BLUE);
	//kb_init();
	while(1)
		keyboard_handler();	

	return;
}
