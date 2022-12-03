#include "ft_printf.h"

static int	put_basic_p(unsigned long n, int start)
{
	char	*base;
	int		i;
	int		printed;

	printed = 0;
	if (start)
		printed += write(1, "0x", 2);
	base = "0123456789abcdef";
	if (n / 16 > 0)
		printed += put_basic_p(n / 16, 0);
	i = n % 16;
	printed += write(1, &base[i], 1);
	return (printed);
}

static int	put_p_width(unsigned long n, t_flag flags)
{
	int	padding;
	int	printed;

	printed = 0;
	padding = flags.width - 2;
	if (flags.dot)
		padding = flags.precision;
	padding -= p_length(n);
	while (!flags.minus && padding-- > 0)
		printed += write(1, " ", 1);
	printed += put_basic_p(n, 1);
	while (flags.minus && padding-- > 0)
		printed += write(1, " ", 1);
	return (printed);
}

static int	put_p_precision(unsigned long n, t_flag flags)
{
	char	*base;
	int		printed;
	int		var_len;

	base = "0123456789abcdef";
	printed = write(1, "0x", 2);
	var_len = flags.width - printed;
	if (flags.dot)
		var_len = flags.precision;
	var_len -= p_length(n);
	while (var_len-- > 0)
		printed += write(1, "0", 1);
	if (n / 16 > 0)
		printed += put_basic_p(n / 16, 0);
	printed += write(1, &base, 1);
	return (printed);
}

static int	put_p_precision_width(unsigned long n, t_flag flags)
{
	int	printed;
	int	padding;
	int	var_len;

	var_len = flags.precision - p_length(n);
	if (var_len <= 0)
		var_len = 0;
	padding = flags.width - var_len - p_length(n) - 2;
	if (padding <= 0)
		padding = 0;
	printed = 2 + padding + var_len;
	while (!flags.minus && padding-- > 0)
		write(1, " ", 1);
	write(1, "0x", 2);
	while (var_len-- > 0)
		write(1, "0", 1);
	printed += put_basic_p(n, 0);
	while (flags.minus && padding-- > 0)
		write(1, " ", 1);
	return (printed);
}

int	put_p(unsigned long n, t_flag flags)
{
	int	i;

	i = 0;
	if (flags.dot && !flags.precision && !n)
	{
		while (!flags.minus && i++ < flags.width - 2)
			write(1, " ", 1);
		write(1, "0x", 2);
		while (flags.minus && i++ < flags.width - 2)
			write(1, " ", 1);
		return (++i);
	}
	if (flags.width > 0 && flags.dot)
		return (put_p_precision_width(n, flags));
	else if (flags.width > 0)
		return (put_p_width(n, flags));
	else if (flags.dot)
		return (put_p_precision(n, flags));
	else
		return (put_basic_p(n, 1));
}
