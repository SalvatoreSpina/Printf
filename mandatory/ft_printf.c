#include "ft_printf.h"

int dispatcher(const char *str, int i, va_list vlist)
{
	if (str[i] == 'c')
		return (putch(va_arg(vlist, int)));
	else if (str[i] == 's')
		return (putstring(va_arg(vlist, char *)));
	else if (str[i] == 'd' || str[i] == 'i')
		return (putnumber(va_arg(vlist, int)));
	else if (str[i] == 'u')
		return (putnumber(va_arg(vlist, unsigned int)));
	else if (str[i] == 'x' || str[i] == 'X' || str[i] == 'p')
		return (puthexa(va_arg(vlist, unsigned long), str[i], 1));
	else if (str[i] == '%')
		return (putch('%'));
	return (0);
}

int ft_printf(const char *str, ...)
{
	va_list vlist;
	int printed;
	int i;

	i = 0;
	printed = 0;
	va_start(vlist, str);
	while (str[i])
	{
		if (str[i] == '%' && str[i++]) {
			printed += dispatcher(str, i++, vlist);
		}
		else
			printed += putch(str[i++]);
	}
	va_end(vlist);
	return (printed);
}