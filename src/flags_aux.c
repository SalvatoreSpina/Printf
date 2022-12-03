#include "ft_printf.h"

inline bool	is_conversion(const char c)
{
	return (c == 'c' || c == 's' || c == 'p'
		|| c == 'd' || c == 'i' || c == 'u'
		|| c == 'x' || c == 'X' || c == '%');
}

inline bool	is_flag(const char c)
{
	return (c == '-' || c == '0' || c == '.'
		|| c == '#' || c == ' ' || c == '+'
		|| (c >= '0' && c <= '9'));
}

int	atoi_asterisk(const char *str, int *i, va_list args)
{
	int	nb;

	nb = 0;
	if (str[*i] == '.')
		(*i)++;
	if (str[*i] == '*')
		return (va_arg(args, unsigned int));
	while (str[*i] >= '0' && str[*i] <= '9')
		nb = nb * 10 + (str[(*i)++] - '0');
	(*i)--;
	return (nb);
}

void	flag_magic(int type, int *flag, long n)
{
	if (type == 1 && n < 0)
		(*flag) += 1;
	else if (type == 2 && (*flag) < 0)
		(*flag) = 0;
	return ;
}
