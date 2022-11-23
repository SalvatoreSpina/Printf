#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int		putch(char c);
int		putstring(char *str);
int		putnumber(long l);
int		puthexa(unsigned long ul, char c, int n);
int		dispatcher(const char *str, int i, va_list vlist);
int		ft_printf(const char *str, ...);

#endif