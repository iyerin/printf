
#include "ft_printf.h"


int ft_arg_is_numeric(char format)
{
		if (format == 'd' || format == 'D' || format == 'i' || format == 'o' || format == 'O' 
		|| format == 'u' || format == 'U' || format == 'x' || format == 'X' )
			return 1;
		return 0;
}

void ft_width_conversion(char **str, t_flags *specs)
{
	ssize_t j;

	j = specs->width - ft_strlen(*str);
	//printf("j = %zi\n", j);
	if (specs->prec_zero == '1')
		j = specs->width;
	if (specs->specs != 'S')
	{
		if (j > 0)
			while(j-- > 0)
				*str = ft_strjoin(" ", *str);
	}
	// else if (specs->specs == 'S')
	// {
	// 	if (j > 0)
	// 		while(j-- > 0)
	// 			*str = ft_strjoin(" ", *char(*unicode_str));
	// }
}

void ft_precision_conversion(char **str, t_flags *specs, ssize_t init_str_len)
{
	ssize_t i = specs->precision - init_str_len;

	if ((specs->prec_zero == '1') && (specs->zero_octal_hex) && (ft_arg_is_numeric(specs->specs))) 
		*str[0] = 2;
	if (((specs->specs == 's') || (specs->specs == 's')) && (i < 0) && ((specs->precision > 0) || (specs->prec_zero)))
			*str = ft_strsub(*str, 0, specs->precision);
	if (specs->precision > 0)
	{
		if (specs->negative)
			i++;
		if (ft_arg_is_numeric(specs->specs) && (i > 0))
		{
			if (specs->negative)
				*str = ft_strsub(*str, 1, ft_strlen(*str) - 1);
			while (i-- > 0)
				*str = ft_strjoin("0", *str);
			if (specs->negative)
				*str = ft_strjoin("-", *str);
		}
	}
}



