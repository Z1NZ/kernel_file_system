#ifndef TTY_HANDLER_H
#define TTY_HANDLER_H

#include "../include/kernel.h"
#include "../include/utils.h"

void	change_tty(int keycode);

typedef struct	ttys
{
	char		*ptr;
	char		vga_buff[(MAX_COLS * MAX_ROWS) * 2];
	int		cursor_loc;
}		ttys;

#endif
