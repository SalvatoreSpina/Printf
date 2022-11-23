#include "ft_printf.h"

int putch(char c)
{
	return (!!write(1, &c, 1));
}

int putstring(char *str)
{
	int i;
	
	i = 0;
	if (str)
		while (str[i])
			i += putch(str[i]);
	else
		i += putstring("(null)");
	return (i);	
}

int putnumber(long l)
{
	int nb;

	nb = 0;
	if (l < 0)
	{
		nb += putch('-');
		l *= -1;
	}
	if (l > 9)
		nb += putnumber(l / 10);
	putch(l % 10 + 48);
	return (++nb);
}

int puthexa(unsigned long ul, char c, int n)
{
	char *set;
	int nb;

	nb = 0;
	if (c == 'X')
		set = "0123456789ABCDEF";
	else
		set = "0123456789abcdef";
	if (c == 'p')
	{
		if (n == 1)
			nb += putstring("0x");
		if (ul / 16 > 0)
			nb += puthexa(ul / 16, c, 0);
	}
	else if ((unsigned int)ul / 16 > 0)
			nb += puthexa((unsigned int)ul / 16, c, 0);
	putch(set[ul % 16]);
	return (++nb);
}