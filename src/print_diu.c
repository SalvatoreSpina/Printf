/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_diu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sspina <sspina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 11:44:02 by sspina            #+#    #+#             */
/*   Updated: 2022/12/03 15:54:26 by sspina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	put_basic_diu(long n)
{
	int	num;
	int	c;

	num = 0;
	if (n < 0)
		n *= -1 * write(1, "-", 1) + num++;
	if (n > 9)
		num += put_basic_diu(n / 10);
	c = n % 10 + '0';
	num += write(1, &c, 1);
	return (num);
}

static int	put_diu_precision_width(long n, t_flag flags)
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
	while (!flags.minus && padding-- > 0)
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

static int	put_diu_width(long n, t_flag flags)
{
	int	printed;
	int	padding;

	printed = 0;
	padding = flags.width - num_length(n);
	while (!flags.minus && padding-- > 0)
		printed += write(1, " ", 1);
	printed += put_basic_diu(n);
	while (flags.minus && padding-- > 0)
		printed += write(1, " ", 1);
	return (printed);
}

static int	put_diu_precision(long n, t_flag flags)
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
		n = n * -write(1, "-", 1) + printed++;
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
		return (idx + put_diu_precision_width(n, flags));
	else if (flags.width > 0 && !flags.zero)
		return (idx + put_diu_width(n, flags));
	else if (flags.width > 0 && flags.zero && flags.minus)
		return (idx + put_diu_width(n, flags));
	else if (flags.dot || (flags.width > 0 && flags.zero))
		return (idx + put_diu_precision(n, flags));
	else
		return (idx + put_basic_diu(n));
}
