#include "tty_handler.h"

extern unsigned int current_tty;
extern char *vidptr;
extern int current_loc;

static ttys	tty_array[3] = {
	[0].ptr = (char *)VGA_ADDRESS,
	[0].vga_buff = {0},
	[0].xy = 0,
	[1].ptr = (char *)VGA_ADDRESS,
	[1].vga_buff = {0},
	[1].xy = 0,
	[2].ptr = (char *)VGA_ADDRESS,
	[2].vga_buff = {0},
	[2].xy = 0,
};

int		check_tty_nbr(int keycode)
{
	if (keycode == 0x3b)
		return 0;
	else if (keycode == 0x3c)
		return 1;
	else if (keycode == 0x3d)
		return 2;
}

void		change_tty(int keycode)
{
	int new_tty;

	new_tty = check_tty_nbr(keycode);
	if (current_tty != new_tty)
	{
		memcpy(tty_array[current_tty].vga_buff, (char *)VGA_ADDRESS, (MAX_COLS * MAX_ROWS) * 2);
		vidptr = tty_array[new_tty].ptr;
		tty_array[current_tty].xy = current_loc;
		memcpy((char *)VGA_ADDRESS, tty_array[new_tty].vga_buff, (MAX_COLS * MAX_ROWS) * 2);
		current_loc = tty_array[new_tty].xy;
		current_tty = new_tty;
	}
}
