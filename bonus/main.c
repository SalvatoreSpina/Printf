#include "ft_printf_bonus.h"
#include <stdio.h>

int main()
{
	int r1, r2;

	r1 = ft_printf("%-1c", '0');
	printf("\n");

	r2 =    printf("%-1c", '0');
	printf("\n");

	printf("Return 1: %d", r1);
	printf("\n");

	printf("Return 2: %d", r2);
	printf("\n");

	return 0;
}