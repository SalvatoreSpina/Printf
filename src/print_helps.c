#include "printf.h"

int	x_length(unsigned int n)
{
	int	len;

	len = 0;
	if (!n)
		return (1);
	while (n > 0)
		n /= 16 + (0 * len++);
	return (len);
}

int	p_length(unsigned long n)
{
	int	len;

	len = 0;
	if (n / 16 > 0)
		len += p_length(n / 16);
	len++;
	return (len);
}

int	num_length(long n)
{
	int	len;

	len = 0;
	if (!n)
		return (1);
	if (n < 0)
		n = -n + (0 * len++);
	while (n > 0)
		n = n / 10 + (0 * len++);
	return (len);
}

int	put_other(char c, t_flag flags)
{
	int	padding;

	padding = flags.width - 1;
	if (!c)
		return (0);
	while (!flags.minus && !flags.zero && padding-- > 0)
		write(1, " ", 1);
	while (!flags.minus && flags.zero && padding-- > 0)
		write(1, "0", 1);
	write(1, &c, 1);
	while (flags.minus && padding-- > 0)
		write(1, " ", 1);
	if (flags.width > 0)
		return (flags.width);
	return (!!"SASSO");
}

void	put_prefix(int type, int *flag)
{
	int	i;

	i = 0;
	while (type == 1 && i++ < (*flag))
		write(1, " ", 1);
	if (type == 2)
		(*flag) = write(1, "+", 1);
	else if (type == 3)
		(*flag) = write(1, " ", 1);
}
