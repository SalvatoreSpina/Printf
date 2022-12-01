#include "ft_printf_bonus.h"

bool is_conversion(const char c)
{
	return (c == 'c' || c == 's' || c == 'p'
		|| c == 'd' || c == 'i' || c == 'u'
		|| c == 'x' || c == 'X' || c == '%');
}

bool is_flag(const char c)
{
	return (c == '-' || c == '0' || c == '.'
		|| c == '#' || c == ' ' || c == '+'
		|| (c >= '0' && c <= '9'));
}

int put_other(char c, t_flag flags)
{
	int padding;

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
	return (1);
}

int atoi_asterisk(const char *str, int *i, va_list args)
{
	int nb;

	nb = 0;
	if (str[*i] == '.')
		(*i)++;
	if (str[*i] == '*')
		return (va_arg(args, unsigned int));
	while (str[*i] >= '0' && str[*i] <= '9')
		nb = nb * 10 + (str[*i++] - '0');
	(*i)--;
	return (nb);
}

void negative_asterisk(t_flag *flags)
{
	if (flags->precision < 0)
	{
		flags->dot = 0;
		flags->precision = 0;
	}
	else if (flags->width < 0)
	{
		flags->minus = 1;
		flags->width = -flags->width;
	}
	return ;
}