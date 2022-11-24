/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sspina <sspina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 12:01:45 by sspina            #+#    #+#             */
/*   Updated: 2022/11/24 13:18:32 by sspina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	putstring(char *str)
{
	int	i;

	i = 0;
	if (str)
		while (str[i])
			i += write(1, &str[i], 1);
	else
		i += putstring("(null)");
	return (i);
}

static int	putnumber(long l)
{
	int	nb;
	int	c;

	nb = 0;
	if (l < 0)
	{
		nb += write(1, "-", 1);
		l *= -1;
	}
	if (l > 9)
		nb += putnumber(l / 10);
	c = l % 10 + '0';
	write(1, &c, 1);
	return (++nb);
}

static int	puthexa(unsigned long ul, char c, int n)
{
	char	*set;
	int		nb;

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
	write(1, &set[ul % 16], 1);
	return (++nb);
}

static int	dispatcher(const char *str, int i, va_list vlist)
{
	char	c;

	if (str[i] == 'c')
	{
		c = va_arg(vlist, int);
		return (write(1, &c, 1));
	}
	else if (str[i] == 's')
		return (putstring(va_arg(vlist, char *)));
	else if (str[i] == 'd' || str[i] == 'i')
		return (putnumber(va_arg(vlist, int)));
	else if (str[i] == 'u')
		return (putnumber(va_arg(vlist, unsigned int)));
	else if (str[i] == 'x' || str[i] == 'X' || str[i] == 'p')
		return (puthexa(va_arg(vlist, unsigned long), str[i], 1));
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
