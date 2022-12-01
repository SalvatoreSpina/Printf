#include "ft_printf_bonus.h"

int	string_length(char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

int	put_prec_pad_string(char *str, t_flag flags, int size, int width)
{
	char	c;
	int		i;

	i = 0;
	c = ' ';
	if (flags.zero && !flags.minus)
		c = '0';
	while (flags.minus && i < flags.precision && str[i])
		write(1, &str[i++], 1);
	while (width--)
		write(1, &c, 1);
	while (!flags.minus && i < flags.precision && str[i])
		write(1, &str[i++], 1);
	if (size > flags.width)
		return (size);
	return (flags.width);
}

int	put_padded_string(char *str, t_flag flags)
{
	char	c;
	int		padding;
	int		i;

	i = 0;
	padding = 0;
	c = ' ';
	if (flags.zero && !flags.minus)
		c = '0';
	if (flags.width > string_length(str))
		padding = flags.width - string_length(str);
	while (flags.minus && str[i])
		write(1, &str[i], 1);
	while (padding--)
		write(1, &c, 1);
	i = 0;
	while (!flags.minus && str[i])
		write(1, &str[i], 1);
	if (string_length(str) > flags.width)
		return (string_length(str));
	return (flags.width);
}

int	put_precisioned_string(char *str, int size)
{
	int	i;

	i = 0;
	while (i < size && str[i])
		write(1, &str[i++], 1);
	return (size);
}

int	put_s(char *str, t_flag flags)
{
	int	size;
	int	width;

	size = flags.precision;
	width = 0;
	if (!str)
		str = "(null)";
	if (flags.precision > string_length(str))
		size = string_length(str);
	if (flags.width > size)
		width = flags.width - size;
	if (flags.width && flags.dot)
		return (put_prec_pad_string(str, flags, size, width));
	else if (flags.width)
		return (put_padded_string(str, flags));
	else if (flags.dot)
		return (put_precisioned_string(str, size));
	return (write(1, &str, string_length(str)));
}
