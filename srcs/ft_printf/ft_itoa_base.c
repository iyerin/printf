#include "ft_printf.h"

char	*ft_itoa_base(size_t value, size_t base)
{
	char *nbr;
	int i;
	int neg;
	size_t tmp = value;
	char *bchr = "0123456789abcdef";

	i = 1;
	neg = 0;
	//printf("value = %zd\n", value);
	// if ((value < 0) && (base == 10))
	// {
	// 	neg = 1;
	// 	value *= -1;
	// }
	while ((tmp /= base) != 0)
		i++;
	//printf("i = %d\n", i);
	//printf("i =%d\n", i);
	nbr = (char*)malloc(sizeof(char) * (i + neg + 1));
	nbr[i+neg]= '\0';
	while (i--)
	{
		// printf("value = %zd\n", value);
		// printf("base = %zi\n", base);
		// printf("||i = %li||\n", value % base);
		nbr[i+neg] = bchr[value % base];
		value = value/base;
	//	printf("||c = %c||\n", nbr[i+neg]);

	}
	// if (neg)
	// 	nbr[0] = '-';
//printf("str = %s\n", nbr);
	return (nbr);
}