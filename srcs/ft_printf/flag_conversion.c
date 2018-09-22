
#include "ft_printf.h"

void ft_flag_conversion(char **str, t_flags *specs)
{
	ssize_t i = 0;
	char *tmp;
	
	if (specs->hash == '1')
	{
		if (!specs->zero_octal_hex)
		{
			if (specs->specs == 'x')
			{
				tmp = *str;
				*str = ft_strjoin("0x", *str);
				ft_strdel(&tmp);
			}
			if (specs->specs == 'X')
			{
				tmp = *str;
				*str = ft_strjoin("0X", *str);
				ft_strdel(&tmp);
			}
		}
		if ((specs->specs == 'o') || (specs->specs == 'O'))
		{
			if (*str[0] != '0')
			{
				tmp = *str;
				*str = ft_strjoin("0", *str);
				ft_strdel(&tmp);
			}
		}
	}
	if ((specs->zero == '1') && (specs->minus != '1') && (specs->precision == 0))
	{
		i = specs->width - ft_strlen(*str);
		if (specs->negative)
		{
			tmp = *str;
			*str = ft_strsub(*str, 1, ft_strlen(*str) - 1);
			ft_strdel(&tmp);
			//i++;
		}
		//	printf("i = %zu\n", i);
					// printf("s1 = %s\n", *str);
		if ((specs->hash) && ((specs->specs == 'o') || (specs->specs == 'O') || (specs->specs == 'x') ||(specs->specs == 'X')))
		{
			tmp = *str;
			*str = ft_strsub(*str, 2, ft_strlen(*str) - 2);
			ft_strdel(&tmp);
			//i += 2;
		}
		if (specs->space == '1')
			i--;
			//printf("s2 = %s\n", *str);
		while (i-- > 0)
		{
			tmp = *str;
			*str = ft_strjoin("0", *str);
			ft_strdel(&tmp);
		}
		if ((specs->hash) && ((specs->specs == 'o') || (specs->specs == 'O') || (specs->specs == 'x') ||(specs->specs == 'X')))
		{
			if ((specs->specs == 'o') || (specs->specs == 'O'))
			{
				tmp = *str;
				*str = ft_strjoin("0", *str);
				ft_strdel(&tmp);
			}
			if (specs->specs == 'x')
			{
				tmp = *str;
				*str = ft_strjoin("0x", *str);
				ft_strdel(&tmp);
			}
			if (specs->specs == 'X')
			{
				tmp = *str;
				*str = ft_strjoin("0X", *str);
				ft_strdel(&tmp);
			}
		}
		if (specs->negative)
		{
			tmp = *str;
			*str = ft_strjoin("-", *str);
			ft_strdel(&tmp);
		}
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
		{
			tmp = *str;
			*str = ft_strjoin("+", *str);
			ft_strdel(&tmp);
		}
	}
	if (specs->minus == '1')
	{
		i = specs->width - ft_strlen(*str);
		//printf("i = %zu\n", i);
		while (i-- > 0)
		{
			tmp = *str;
			*str = ft_strjoin(*str, " ");
			ft_strdel(&tmp);
		}
	}
	if ((specs->space == '1') && (specs->plus != '1') && ((specs->specs == 'd' || specs->specs == 'D' || specs->specs == 'i')))
	{  
		if (!specs->negative)
		{
			tmp = *str;
			*str = ft_strjoin(" ", *str);/////////////////////////works with str, but mustn't
			ft_strdel(&tmp);
		}
	}
}
































