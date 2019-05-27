#include "kernel.h"

extern int current_loc;
extern int j;
extern char *vidptr;

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
		}
		j++;
	}
}

int 	strlen(char *str)
{
	unsigned int index = 0; 
	while (str && str[index])
		index++;
	return index;
}

void	print(char *str)
{
	putstr(str);
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

void	black_screen(void)
{
	while(j < 80 * 25 * 2) 
	{
		vidptr[j] = ' ';
		vidptr[j + 1] = BLACK; 		
		j = j + 2;
	}
}

