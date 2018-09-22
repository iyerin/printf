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
	while ((tmp /= base) != 0)
		i++;
	nbr = (char*)malloc(sizeof(char) * (i + neg + 1));
	nbr[i+neg]= '\0';
	while (i--)
	{
		nbr[i+neg] = bchr[value % base];
		value = value/base;
	}
	return (nbr);
}