#include "kernel.h"

extern int i;
extern int j;
extern char *vidptr;

void	kputchar(char c)
{
	vidptr[i] = c;
}

void	putcolor(int color)
{
	vidptr[i + 1] = color;
}

void	putstr(char *str)
{
	j = 0;

	while(str[j] != '\0') 
	{
		/* the character's ascii */
		if (str[j] == '\n')
			move_y();
		else
		{
			kputchar(str[j]);
			putcolor(GREEN);
			i = i + 2;
		}
		j++;
	}
}

void	print(char *str)
{
	putstr(str);
}

void	black_screen()
{
	while(j < 80 * 25 * 2) 
	{
		vidptr[j] = ' ';
		vidptr[j+1] = BLACK; 		
		j = j + 2;
	}
}

