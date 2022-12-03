/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_c.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sspina <sspina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 11:44:40 by sspina            #+#    #+#             */
/*   Updated: 2022/12/03 11:44:41 by sspina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static int	put_minus_padding(char c, int width)
{
	int	padding;

	padding = 0;
	write(1, &c, 1);
	while (padding++ < width - 1)
		write(1, " ", 1);
	return (width);
}

static int	put_padded_char(char c, int width, char type)
{
	int	padding;

	padding = 0;
	while (padding++ < width - 1)
		write(1, &type, 1);
	write(1, &c, 1);
	return (width);
}

static int	put_char(char c)
{
	return (write(1, &c, 1));
}

int	put_c(int c, t_flag flags)
{
	if (flags.width > 0 && flags.minus)
		return (put_minus_padding(c, flags.width));
	else if (flags.width > 0 && flags.zero)
		return (put_padded_char(c, flags.width, '0'));
	else if (flags.width > 0)
		return (put_padded_char(c, flags.width, ' '));
	else
		return (put_char(c));
}
