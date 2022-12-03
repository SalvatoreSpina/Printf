/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sspina <sspina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 11:05:19 by sspina            #+#    #+#             */
/*   Updated: 2022/12/03 11:05:21 by sspina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	put_s(char *str)
{
	int	i;

	i = 0;
	if (str)
		while (str[i])
			i += write(1, &str[i], 1);
	else
		i += put_s("(null)");
	return (i);
}

static int	put_diu(long l)
{
	int	printed;
	int	c;

	printed = 0;
	if (l < 0)
		l *= -write(1, "-", 1) + printed++ ;
	if (l > 9)
		printed += put_diu(l / 10);
	c = l % 10 + '0';
	write(1, &c, 1);
	return (++printed);
}

static int	put_xp(unsigned long ul, char c, bool prefix)
{
	char	*base;
	int		printed;

	printed = 0;
	if (c == 'X')
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	if (c == 'p')
	{
		if (prefix)
			printed += put_s("0x");
		if (ul / 16 > 0)
			printed += put_xp(ul / 16, c, 0);
	}
	else if ((unsigned int)ul / 16 > 0)
		printed += put_xp((unsigned int)ul / 16, c, 0);
	write(1, &base[ul % 16], 1);
	return (++printed);
}

static int	dispatcher(const char *str, int i, va_list vlist)
{
	char	c;

	if (str[i] == 'c')
		return (c = va_arg(vlist, int), write(1, &c, 1));
	else if (str[i] == 's')
		return (put_s(va_arg(vlist, char *)));
	else if (str[i] == 'd' || str[i] == 'i')
		return (put_diu(va_arg(vlist, int)));
	else if (str[i] == 'u')
		return (put_diu(va_arg(vlist, unsigned int)));
	else if (str[i] == 'x' || str[i] == 'X' || str[i] == 'p')
		return (put_xp(va_arg(vlist, unsigned long), str[i], 1));
	else if (str[i] == '%')
		return (write(1, "%", 1));
	return (!"SASSO");
}

int	ft_printf(const char *str, ...)
{
	va_list	vlist;
	int		printed;
	int		i;

	i = 0;
	printed = 0;
	va_start(vlist, str);
	while (str[i])
	{
		if (str[i] == '%' && str[i++])
			printed += dispatcher(str, i++, vlist);
		else
			printed += write(1, &str[i++], 1);
	}
	va_end(vlist);
	return (printed);
}
