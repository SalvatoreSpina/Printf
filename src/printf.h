#ifndef PRINTF_H
# define PRINTF_H

# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdarg.h>

typedef struct s_flags
{
	bool	minus;
	bool	zero;
	bool	dot;
	bool	hash;
	bool	space;
	bool	plus;
	int		precision;	
	int		width;
}	t_flag;

int		ft_printf(const char *str, ...);

int		put_c(int c, t_flag flags);
int		put_s(char *str, t_flag flags);
int		put_p(unsigned long p, t_flag flags);
int		put_x(unsigned int x, t_flag flags, char c);
int		put_diu(long n, t_flag flags);
int		put_other(char c, t_flag flags);
void	put_prefix(int type, int *flag);

bool	is_conversion(char c);
bool	is_flag(char c);
int		atoi_asterisk(const char *str, int *i, va_list args);
void	flag_magic(int type, int *flag, long n);

int		num_length(long n);
int		x_length(unsigned int x);
int		p_length(unsigned long p);

#endif