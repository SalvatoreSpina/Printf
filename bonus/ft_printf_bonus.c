#include "ft_printf_bonus.h"

void	init_flag(const char *str, int *i, t_flag *flags, va_list args)
{
	flags->dot = 0;
	flags->precision = 0;
	flags->width = 0;
	while (!is_conversion(str[*i]) && is_flag(str[*i]))
	{
		flags->minus = (str[*i] == '-');
		flags->zero = (str[*i] == '0');
		flags->hash = (str[*i] == '#');
		flags->plus = (str[*i] == '+');
		flags->space = (str[*i] == ' ' && !flags->plus);
		if (str[*i] == '.')
			flags->precision = atoi_asterisk(str, i, args) + flags->dot++;
		else if (str[*i] == '*' || (str[*i] >= '1' && str[*i] <= '9'))
			flags->width = atoi_asterisk(str, i, args);
		if (flags->precision < 0 || flags->width < 0)
			negative_asterisk(flags);
		(*i)++;
	}
}

int	dispatcher(const char *str, int *i, va_list vlist)
{
	t_flag	flags;
	int		printed;

	(*i)++;
	init_flag(str, i, &flags, vlist);
	if (str[*i] == 'c')
		printed = put_c(va_arg(vlist, int), flags);
	else if (str[*i] == 's')
		printed = put_s(va_arg(vlist, char *), flags);
	else if (str[*i] == 'p')
		printed = put_p(va_arg(vlist, unsigned long), flags);
	else if (str[*i] == 'd' || str[*i] == 'i')
		printed = put_diu(va_arg(vlist, int), flags);
	else if (str[*i] == 'u')
		printed = put_diu(va_arg(vlist, unsigned int), flags);
	else if (str[*i] == 'x' || str[*i] == 'X')
		printed = put_x(va_arg(vlist, unsigned int), flags, str[*i]);
	else
		printed = put_other(str[*i], flags);
	if (str[*i])
		(*i)++;
	return (printed);
}

int	ft_printf(const char *str, ...)
{
	va_list	vlist;
	int		i;
	int		printed;

	i = 0;
	printed = 0;
	va_start(vlist, str);
	while (str[i])
	{
		if (str[i] == '%')
			printed += dispatcher(str, &i, vlist);
		else
			printed += write(1, &str[i++], 1);
	}
	va_end(vlist);
	return (printed);
}
