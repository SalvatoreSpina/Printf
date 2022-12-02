#include "ft_printf_bonus.h"

void	init_flags(t_flag *flags)
{
	flags->minus = 0;
	flags->zero = 0;
	flags->dot = 0;
	flags->hash = 0;
	flags->space = 0;
	flags->plus = 0;
	flags->precision = 0;
	flags->width = 0;
}

void	set_flags(const char *str, int *i, t_flag *flags, va_list vlist)
{
	init_flags(flags);
	while (!is_conversion(str[*i]) && is_flag(str[*i]))
	{
		if (str[*i] == '-')
			flags->minus = 1;
		else if (str[*i] == '0')
			flags->zero = 1;
		else if (str[*i] == '#')
			flags->hash = 1;
		else if (str[*i] == '+')
			flags->plus = 1;
		else if (str[*i] == ' ' && flags->plus == 0)
			flags->space = 1;
		else if (str[*i] == '.')
			flags->precision = atoi_asterisk(str, i, vlist) + flags->dot++;
		else if (str[*i] == '*' || (str[*i] >= '1' && str[*i] <= '9'))
			flags->width = atoi_asterisk(str, i, vlist);
		if (flags->precision < 0)
			flags->precision = --flags->dot;
		else if (flags->width < 0)
			flags->width *= -1 * flags->minus++;
		(*i)++;
	}
}

int	dispatcher(const char *str, int *i, va_list vlist)
{
	t_flag	flags;
	int		printed;

	(*i)++;
	set_flags(str, i, &flags, vlist);
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
