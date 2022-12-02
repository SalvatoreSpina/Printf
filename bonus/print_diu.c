#include "ft_printf_bonus.h"

int	put_basic_diu(long n)
{
	int	num;
	int	c;

	num = 0;
	if (n < 0)
	{
		num += write(1, "-", 1);
		n *= -1;
	}
	if (n > 9)
		num += put_basic_diu(n / 10);
	c = n % 10 + '0';
	num += write(1, &c, 1);
	return (num);
}

int	put_diu_precision_width(long n, t_flag flags)
{
	int	printed;
	int	var_len;
	int	padding;

	printed = 0;
	var_len = flags.precision - num_length(n);
	flag_magic(1, &var_len, n);
	flag_magic(2, &var_len, n);
	padding = flags.width - num_length(n) - var_len;
	flag_magic(2, &padding, n);
	printed += padding + var_len + num_length(n);
	while (flags.minus == 0 && padding-- > 0)
		write(1, " ", 1);
	if (n < 0)
		n *= (-1 * write(1, "-", 1));
	while (var_len-- > 0)
		write(1, "0", 1);
	put_basic_diu(n);
	while (flags.minus && padding-- > 0)
		write(1, " ", 1);
	return (printed);
}

int	put_diu_width(long n, t_flag flags)
{
	int	printed;
	int	padding;

	printed = 0;
	padding = flags.width - num_length(n);
	while (flags.minus == 0 && padding-- > 0)
		printed += write(1, " ", 1);
	printed += put_basic_diu(n);
	while (flags.minus == 1 && padding-- > 0)
		printed += write(1, " ", 1);
	return (printed);
}

int	put_diu_precision(long n, t_flag flags)
{
	int	printed;
	int	var_len;

	printed = 0;
	var_len = flags.width - num_length(n);
	if (flags.dot)
		var_len = flags.precision - num_length(n);
	if (n < 0 && flags.dot)
		var_len++;
	if (n < 0)
	{
		printed += write(1, "-", 1);
		n = -n;
	}
	while (var_len-- > 0)
		printed += write(1, "0", 1);
	printed += put_basic_diu(n);
	return (printed);
}

int	put_diu(long n, t_flag flags)
{
	int	idx;

	idx = 0;
	if (n >= 0 && flags.plus)
		put_prefix(2, &idx);
	if (n >= 0 && flags.space && !flags.plus)
		put_prefix(3, &idx);
	if (flags.dot && !flags.precision && !n)
		return (put_prefix(1, &flags.width), flags.width);
	else if (flags.width > 0 && flags.dot)
		return (put_diu_precision_width(n, flags) + idx);
	else if (flags.width > 0 && !flags.zero)
		return (put_diu_width(n, flags) + idx);
	else if (flags.width > 0 && flags.zero && flags.minus)
		return (put_diu_width(n, flags) + idx);
	else if (flags.dot || (flags.width > 0 && flags.zero))
		return (put_diu_precision(n, flags) + idx);
	else
		return (put_basic_diu(n) + idx);
}
