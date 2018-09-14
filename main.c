#include "../libftprintf.h"
#include <stdio.h>

int	main(void)
{
	int		n = -42;
	char	*str = NULL;
	char	c = 'r';

	ft_printf("Test de cliffre avec l : %ld, et %ld\n", 32147483647, -32147483647);
	printf("\n");
	printf("Test de cliffre avec l : %ld, et %ld\n", 32147483647, -32147483647);
	printf("\n");

	return (0);
}
