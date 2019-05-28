#include "kernel.h"

extern int current_loc;
extern int j;
extern char *vidptr;
extern unsigned int cursor_x;
extern unsigned int cursor_y;

void	putchar(char c)
{
	vidptr[current_loc] = c;
}

void	putcolor(int color)
{
	vidptr[current_loc + 1] = color;
}

void	putstr(char *str)
{
	j = 0;

	while(str[j] != '\0') 
	{
		/* the character's ascii */
		if (str[j] == '\n')
			new_line();
		else
		{
			putchar(str[j]);
			putcolor(GREEN);
			current_loc += 2;
		//	cursor_x++;
		//	move_cursor();
		}
		j++;
	}
}

void	putstr_color(char *str, int color)
{
	j = 0;

	while(str[j] != '\0') 
	{
		/* the character's ascii */
		if (str[j] == '\n')
			new_line();
		else
		{
			putchar(str[j]);
			putcolor(color);
			current_loc += 2;
		//	cursor_x += 2;
		}
		j++;
	}
}

void	print(char *str)
{
	putstr(str);
}

void	print_color(char *str, int color)
{
	putstr_color(str, color);
}

void	putnbr(int nb)
{
	if (nb < 0)
	{
		putchar('-');
		nb = -nb;
	}
	if (nb < 10)
		putchar(nb + '0');
	else
	{
		putnbr(nb / 10);
		putchar((nb % 10) + '0');
	}
}

void	move_cursor()
{
   // The screen is 80 characters wide...
   uint16 cursorLocation = cursor_y * MAX_COLS + cursor_x;
   write_port(0x3D4, 14);                  // Tell the VGA board we are setting the high cursor byte.
   write_port(0x3D5, cursorLocation >> 8); // Send the high cursor byte.
   write_port(0x3D4, 15);                  // Tell the VGA board we are setting the low cursor byte.
   write_port(0x3D5, cursorLocation);      // Send the low cursor byte.
}

void	black_screen(void)
{
	while(j < MAX_COLS * MAX_ROWS * 2) 
	{
		vidptr[j] = ' ';
		vidptr[j + 1] = BLACK; 		
		j = j + 2;
	}
	cursor_y = 0;
	cursor_x = 0;
//	move_cursor();
}

int	get_screen_offset(int col, int row) 
{
    return (((row * MAX_COLS) + col) * 2);
}

void	memory_copy(char* source , char* dest , int  no_bytes) 
{
	int i;
	
	for ( i = 0; i < no_bytes; i++) 
		*(dest + i) = *( source + i);
}

int	handle_scrolling(int  cursor_offset) 
{
	if (cursor_offset  < MAX_ROWS * MAX_COLS * 2) 
		return  cursor_offset;
	int i;
	for (i = 1; i < MAX_ROWS; i++) 
		memory_copy((char *)get_screen_offset(0, i) + VGA_ADDRESS , \
		(char *)get_screen_offset(0, i - 1) + VGA_ADDRESS , MAX_COLS * 2);
	char *last_line = (char *)get_screen_offset(0, MAX_ROWS - 1) + VGA_ADDRESS;
	for (i = 0; i < MAX_COLS * 2; i++) 
		last_line[i] = 0;
	// Move  the  offset  back  one row , such  that it is now on the  last// row , rather  than  off the  edge of the  screen.
	cursor_offset -= 2 * MAX_COLS;//  Return  the  updated  cursor  position.
	return  cursor_offset;
}
