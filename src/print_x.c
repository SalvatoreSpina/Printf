#include "printf.h"

static int	put_x_basic(unsigned int n, bool uppercase)
{
	char	*base;
	int		printed;
	int		i;

	base = "0123456789abcdef";
	if (uppercase)
		base = "0123456789ABCDEF";
	printed = 0;
	if (n / 16 > 0)
		printed += put_x_basic(n / 16, uppercase);
	i = n % 16;
	printed += write(1, &base[i], 1);
	return (printed);
}

static int	put_x_precision(unsigned int n, t_flag flags, bool uppercase)
{
	int	printed;
	int	var_len;

	printed = 0;
	var_len = flags.width;
	if (flags.dot)
		var_len = flags.precision;
	var_len -= x_length(n);
	while (var_len-- > 0)
		printed += write(1, "0", 1);
	printed += put_x_basic(n, uppercase);
	return (printed);
}

static int	put_x_width(unsigned int n, t_flag flags, bool uppercase)
{
	int	printed;
	int	padding;

	printed = 0;
	padding = flags.width - x_length(n);
	while (!flags.minus && padding-- > 0)
		printed += write(1, " ", 1);
	printed += put_x_basic(n, uppercase);
	while (flags.minus && padding-- > 0)
		printed += write(1, " ", 1);
	return (printed);
}

static int	put_x_width_precision(unsigned int n, t_flag flags, bool uppercase)
{
	int	printed;
	int	var_len;
	int	padding;

	printed = 0;
	var_len = flags.precision - x_length(n);
	flag_magic(2, &var_len, n);
	padding = flags.width - x_length(n) - var_len;
	flag_magic(2, &padding, n);
	printed += padding + var_len + x_length(n);
	while (!flags.minus && padding-- > 0)
		write(1, " ", 1);
	while (var_len-- > 0)
		write(1, "0", 1);
	put_x_basic(n, uppercase);
	while (flags.minus && padding-- > 0)
		write(1, " ", 1);
	return (printed);
}

int	put_x(unsigned int n, t_flag flags, char c)
{
	int		idx;
	bool	uppercase;

	idx = 0;
	uppercase = (c == 'X');
	if (n && flags.hash && uppercase)
		idx += write(1, "0X", 2);
	else if (n && flags.hash && !uppercase)
		idx += write(1, "0x", 2);
	if (flags.dot && !flags.precision && !n)
		return (flag_magic(1, &flags.width, n), flags.width);
	else if (flags.width > 0 && flags.dot)
		return (idx + put_x_width_precision(n, flags, uppercase));
	else if (flags.width > 0 && !flags.zero)
		return (idx + put_x_width(n, flags, uppercase));
	else if (flags.width > 0 && flags.zero && flags.minus)
		return (idx + put_x_width(n, flags, uppercase));
	else if (flags.dot || (flags.width > 0 && flags.zero))
		return (idx + put_x_precision(n, flags, uppercase));
	else
		return (idx + put_x_basic(n, uppercase));
}
