
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
	if (j > 0)
		while(j-- > 0)
			*str = ft_strjoin(" ", *str);
}

void ft_precision_conversion(char **str, t_flags *specs, ssize_t init_str_len)
{
	if ((specs->prec_zero == '1') && (specs->zero_octal_hex) && (ft_arg_is_numeric(specs->specs))) 
	{
		//printf("HUI\n");
		*str[0] = 2;
	}

	if (specs->precision > 0)
	{
		//printf("prec = %i\n", specs->precision);
		ssize_t i = specs->precision - init_str_len;
		//printf("init = %zu\n", init_str_len);
		//printf("i === %zu\n", i);
	///////////////// fix prec 0 ////////////////////////////
		if ((specs->specs == 's') && (i < 0))
		{
			*str = ft_strsub(*str, 0, specs->precision);
		}

		if (ft_arg_is_numeric(specs->specs) && (i > 0))/////////////fix only 0
		{
			if (specs->negative)
			{
				*str = ft_strsub(*str, 1, ft_strlen(*str) - 1);
				i++;
			}
			// printf("s1 = %s\n", *str);
			// if ((specs->hash) && ((specs->specs == 'o') || (specs->specs == 'O') || (specs->specs == 'x') ||(specs->specs == 'X')))
			// {
			// 	*str = ft_strsub(*str, 2, ft_strlen(*str) - 2);
			// 	//i += 2;
			// }
			// printf("s2 = %s\n", *str);
			while (i-- > 0)
				*str = ft_strjoin("0", *str);
			if (specs->negative)
				*str = ft_strjoin("-", *str);
			// if ((specs->hash) && ((specs->specs == 'o') || (specs->specs == 'O') || (specs->specs == 'x') ||(specs->specs == 'X')))
			// {
			// 	if ((specs->specs == 'o') || (specs->specs == 'O'))
			// 		*str = ft_strjoin("0", *str);
			// 	if (specs->specs == 'x')
			// 		*str = ft_strjoin("0x", *str);
			// 	if (specs->specs == 'X')
			// 		*str = ft_strjoin("0X", *str);
			// }
		}
	}
	// else if ((specs->precision = 0) && (specs->zero_octal_hex))
	// {
	// 	str[0] = '2';
	// }

}