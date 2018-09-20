#include "ft_printf.h"

int		ft_specifier_is_true (char format)
{
		if (format == 's' ||  format == 'S' || format == 'p' || format == 'd' 
		|| format == 'D' || format == 'i' || format == 'o' || format == 'O' 
		|| format == 'u' || format == 'U' || format == 'x' || format == 'X' 
		|| format == 'c' || format == 'C')
			return 1;
		return 0;
}

int   ft_parser(const char *format, t_flags **specs, ssize_t *bytes_counter)
{
	char tmp[1024];
	int i = 0;
 	const char *tmp2;
 	
 	tmp2 = format;

	*specs = malloc(sizeof(t_flags));

	(*specs)->hash = (*specs)->zero = (*specs)->minus = (*specs)->plus = (*specs)->space = (*specs)->width
	 = (*specs)->precision = (*specs)->length = (*specs)->specs = (*specs)->negative = (*specs)->antispecs
	  = (*specs)->charzero = (*specs)->zero_octal_hex = (*specs)->prec_zero = (*specs)->unicode = 0;

	while (*format != '%' && *format)
		{
			*bytes_counter += write(1, format, 1);
			format++;
		}
	if (!*format)
		return (0);
	format++;

	while (*format == '#' || *format == '0' || *format == '-' || *format == '+'|| *format == ' ')
	{
		if(*format == '#')
			(*specs)->hash = '1';
		if(*format == '0')
			(*specs)->zero = '1';
		if(*format == '-')
			(*specs)->minus = '1';
		if(*format == '+')
			(*specs)->plus = '1';
		if(*format == ' ')
			(*specs)->space = '1';
		format++;
	}
	while ((*format >= '0') && (*format <= '9'))
			tmp[i++] = *format++;
		tmp[i] = 0;
		(*specs)->width = ft_atoi(tmp);
		ft_bzero(tmp, 1024);
		i = 0;
	if (*format == '.')
	{
		format++;
		while (*format >= '0' && *format <= '9')
				tmp[i++] = *format++;
		(*specs)->precision = ft_atoi(tmp);
		if((*specs)->precision == 0)
			(*specs)->prec_zero = '1';
	}	
	if (*format == 'h' || *format == 'l' || *format == 'j' || *format == 'z')
	{
		if (*format == 'h')
		{
			if (*(format + 1) == 'h')
			{
				(*specs)->length = 'H';
				format++;
			}
			else 
				(*specs)->length = 'h';
		}
		else if (*format == 'l')
		{
			if (*(format + 1) == 'l')
			{
				(*specs)->length = 'L';
				format++;
			}
			else 
				(*specs)->length = 'l';
		}	
		else
			(*specs)->length = *format;
		format++;
	}
	if (ft_specifier_is_true(*format))
		(*specs)->specs = *format;
	else
		(*specs)->antispecs = *format;
	format++;
	// printf(" plus %c\n", (*specs)->plus);
	// printf("minus %c\n", (*specs)->minus);
	// printf(" hash %c\n", (*specs)->hash);
	// printf(" zero %c\n", (*specs)->zero);
	// printf("space %c\n\n", (*specs)->space);
	// printf("Width = %zu\n", (*specs)->width);
	// printf("Precision = %d\n", (*specs)->precision);
	// printf("Length = %c\n", (*specs)->length);
	// printf("Spec = %c\n", (*specs)->specs);
	
	//free (specs);
	return (format - tmp2);
}