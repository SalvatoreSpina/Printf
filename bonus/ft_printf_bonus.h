#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdarg.h>

typedef struct	s_flags
{
	int	minus;			// -		-> left align
	int	zero;			// 0		-> zero-padded number (ignored if - or precision)
	int	dot;			// .		-> precision

	int	hash;			// #		-> prefix 0x or 0X for x or X conversion
	int	space;			// ' '		-> prefix a space if no sign is going to be written
	int	plus;			// +		-> prefix a + for positive numbers

	int	precision;		// .number		
	int	width;			// 0-9
} t_flag;

int put_c(int c, t_flag flags);
int put_s(char *str, t_flag flags);
int put_p(unsigned long p, t_flag flags);
int put_x(unsigned int x, t_flag flags, char c);
int put_diu(long n, t_flag flags);
int put_other(char c, t_flag flags);

bool is_conversion(char c);
bool is_flag(char c);
int atoi_asterisk(const char *str, int *i, va_list args);
void negative_asterisk(t_flag *flags);

void put_prefix(int type, int *flag);
void flag_magic(int type, int *flag, long n);

int num_length(long n);
int x_length(unsigned int x);
int p_length(unsigned long p);

#endif