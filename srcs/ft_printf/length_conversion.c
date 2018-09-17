
#include "ft_printf.h"

void ft_length_signed_conversion(char **str, t_flags *specs, size_t base, size_t universal_var)
{
	ssize_t signed_var;
	size_t unsigned_var = 0;

	if (specs->length == 'H')
    	signed_var = (signed char)universal_var;
	else if (specs->length == 'h')
		signed_var = (short int)universal_var;
	else if (specs->length == 'l')
		signed_var = (long int)universal_var;
	else if (specs->length == 'L')
		signed_var = (long long int)universal_var;
	else if (specs->length == 'j')
		signed_var = (intmax_t)universal_var;
	else if (specs->length == 'z')
	 	signed_var = (ssize_t)universal_var;
	else
		signed_var = (int)universal_var;
//	printf("SV = %zi\n", signed_var);
	if (signed_var < 0)
	{
		unsigned_var = signed_var * -1;//////////////////////////
		*str = ft_itoa_base(unsigned_var, base);
		*str = ft_strjoin("-", *str);
	
	}
	else
	{
		*str = ft_itoa_base(signed_var, base);
	}
//		printf("str = %s\n", *str);
}

void ft_length_unsigned_conversion(char **str, t_flags *specs, size_t base, size_t universal_var)
{
	size_t unsigned_var;

	if (specs->length == 'H')
    	unsigned_var = (unsigned char)universal_var;
	else if (specs->length == 'h')
		unsigned_var = (unsigned short int)universal_var;
	else if (specs->length == 'l')
		unsigned_var = (unsigned long int)universal_var;
	else if (specs->length == 'L')
		unsigned_var = (unsigned long long int)universal_var;
	else if (specs->length == 'j')
		unsigned_var = (uintmax_t)universal_var;
	else if (specs->length == 'z')
		unsigned_var = (size_t)universal_var;
	else
		unsigned_var = (unsigned int)universal_var;
	*str = ft_itoa_base(unsigned_var, base);
}