
#include "ft_printf.h"

void ft_flag_conversion(char **str, t_flags *specs)
{
	ssize_t i = 0;

	
	if (specs->hash == '1')
	{
		if (!specs->zero_octal_hex)
		{
			if (specs->specs == 'x')
				*str = ft_strjoin("0x", *str);
			if (specs->specs == 'X')
				*str = ft_strjoin("0X", *str);
			
		}
		
		if ((specs->specs == 'o') || (specs->specs == 'O'))
			if (*str[0] != '0')
				*str = ft_strjoin("0", *str);
	}
	if ((specs->zero == '1') && (specs->minus != '1') && (specs->precision == 0))
	{
		i = specs->width - ft_strlen(*str);
		if (specs->negative)
		{
			*str = ft_strsub(*str, 1, ft_strlen(*str) - 1);
			//i++;
		}
		//	printf("i = %zu\n", i);
					// printf("s1 = %s\n", *str);
		if ((specs->hash) && ((specs->specs == 'o') || (specs->specs == 'O') || (specs->specs == 'x') ||(specs->specs == 'X')))
		{
			*str = ft_strsub(*str, 2, ft_strlen(*str) - 2);
			//i += 2;
		}
		if (specs->space == '1')
			i--;
			//printf("s2 = %s\n", *str);
		while (i-- > 0)
			*str = ft_strjoin("0", *str);
		if ((specs->hash) && ((specs->specs == 'o') || (specs->specs == 'O') || (specs->specs == 'x') ||(specs->specs == 'X')))
		{
			if ((specs->specs == 'o') || (specs->specs == 'O'))
				*str = ft_strjoin("0", *str); 
			if (specs->specs == 'x')
				*str = ft_strjoin("0x", *str);
			if (specs->specs == 'X')
				*str = ft_strjoin("0X", *str);
		}
		if (specs->negative)
				*str = ft_strjoin("-", *str);
	}
	if ((specs->plus == '1') && ((specs->specs == 'd' || specs->specs == 'D' || specs->specs == 'i')))
	{
		//printf("str = %s\n", *str);
		if ((*str[0] != '-') && (ft_strlen(*str) == specs->width))
		{
		//	printf("HUI\n");
			*str[0] = '+';
		}
		else if (*str[0] != '-')
			*str = ft_strjoin("+", *str);
	}
	if (specs->minus == '1')
	{
		i = specs->width - ft_strlen(*str);
		//printf("i = %zu\n", i);
		while (i-- > 0)
			*str = ft_strjoin(*str, " ");
	}
	if ((specs->space == '1') && (specs->plus != '1') && ((specs->specs == 'd' || specs->specs == 'D' || specs->specs == 'i')))  
		if (!specs->negative)//(*str[0] != '-')
				*str = ft_strjoin(" ", *str);/////////////////////////works with str, but mustn't
}