#include "ft_printf_bonus.h"

int x_length(unsigned int n)
{
	int len;

	len = 0;
	if (!n)
		return 1;
	while (n > 0)
	{
		n /= 16;
		len++;
	}
	return (len);
}

int p_length(unsigned long n)
{
	int len;

	len = 0;
	if (n / 16 > 0)
		len += p_length(n / 16);
	len++;
	return (len);
}

int num_length(long n)
{
	int len;

	len = 0;
	if (!n)
		return 1;
	if (n < 0)
	{
		n = -n;
		len++;
	}
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return len;
}

void put_prefix(int type, int *flag)
{
	int i;

	i = 0;
	if (type == 1)
		while (i++ < (*flag))
			write(1, " ", 1);
	else if (type == 2)
		(*flag) = write(1, "+", 1);
	else if (type == 3)
		(*flag) = write(1, " ", 1);
}

void flag_magic(int type, int *flag, long n)
{
	if (type == 1 && n < 0)
		(*flag) += 1;
	if (type == 2 && (*flag) < 0)
		(*flag) = 0;
	return ;
}