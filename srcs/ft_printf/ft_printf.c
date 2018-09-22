#include "ft_printf.h"

int	ft_countchar(int value)
{
	if (value < 128)
		return (1);
	else if (value < 2048) 
		return (2);
	else if (value < 65536) 
		return (3);
	else if (value <= 1114111) 
		return (4);
	else
		return (0);
}

int ft_countchar_unicode_str(wchar_t *unicode_str)
{	
	int i = 0;
	while (*unicode_str)
	{
		i += ft_countchar(*unicode_str);
		unicode_str++;
	}
	return (i);
}


size_t	ft_unicode_str_len(wchar_t *unicode_str)
{
	size_t i = 0;

	while (*unicode_str)
	{
		i += 4;
		unicode_str++;
	}
	//printf("i = %zi\n", i);
	return (i);
}

int ft_find_replace_unicode(char const *s, wchar_t unicode_char)
{
	int i;

	i = 0;
	if (!s)
		return (i);
	while (*s)
	{
		if((*s == 2) && (unicode_char) && MB_CUR_MAX > 1)
			i += ft_putchar(unicode_char);
		else if ((*s == 2) && (unicode_char))
			i += write(1, &unicode_char, 1);
		else
			write(1, s, 1);
		s++;
	}
	return (i);
}

wchar_t  *ft_unicode_precision(wchar_t *unicode_str, t_flags *specs)
{
	wchar_t	*new_str;
	int i;
	int j = specs->precision;
	int k = 0;

	i = 0;
	new_str = ft_memalloc(sizeof(wchar_t) * (specs->precision + 1));
	while(j > 0)
	{
		k = ft_countchar(*unicode_str);
		if(j >= k)
		{
			new_str[i] = unicode_str[i];
			i++;
		}
		j -= k;
	}
	return (new_str);
}

int 	ft_print_unicode_str(wchar_t *unicode_str)
{
	int i;

	i = 0;
	if (!unicode_str)
		return (i);
	while (*unicode_str)
	{
		i += ft_putchar(*unicode_str);
		unicode_str++;
	}
	return (i);
}

void ft_unicode_conversion(wchar_t *unicode_str, t_flags *specs, ssize_t *bytes_counter)
{
	size_t i = 0;
	wchar_t *new_str = NULL;

	i = ft_countchar_unicode_str(unicode_str);

	if (((specs->precision > 0) || (specs->prec_zero)) &&  (size_t)specs->precision < i)
	{
		new_str = ft_unicode_precision(unicode_str, specs);
		ft_memdel((void**)(&unicode_str));
	}
	else
		new_str = unicode_str;

	i = ft_countchar_unicode_str(new_str);

	if (specs->width > i)
	{
		if (specs->minus)
			*bytes_counter += ft_print_unicode_str(new_str);
		while (specs->width-- > i)
			*bytes_counter += write(1, " ", 1);
		if (!specs->minus)
			*bytes_counter += ft_print_unicode_str(new_str);
	}
	else 
		*bytes_counter += ft_print_unicode_str(new_str);
	ft_memdel((void**)(&new_str));
}

int	ft_find_replace_null_decimal(char const *s)
{
	int i;

	i = 0;
	if (!s)
		return (i);
	while (*s)
	{
		if(*s != 2)
			i += write(1, s, 1);
		s++;
	}
	return (i);
}

int	ft_find_replace_null_char(char const *s)
{
	int i;

	i = 0;
	if (!s)
		return (i);
	while (*s)
	{
		if(*s == 2)
			i += write(1, "\0", 1);
		else
			i += write(1, s, 1);		
		s++;
	}
	return (i);
}

char *ft_str_to_upper(char *str)
{
	char *tmp;
	int i = 0;
	tmp = ft_strnew(ft_strlen(str));

	while (*str)
	{
		tmp[i] = ft_toupper(*str);
		i++;
		str++;
	}
	return (tmp);//////////////////////leak
}

int ft_printf(const char *format, ...)
{
    va_list arg_list;
    t_flags *specs;
    char *str;
    int j;
  	ssize_t bytes_counter = 0;
  	ssize_t init_str_len = 0;
  	size_t universal_var;
  	wchar_t unicode_char;
  	wchar_t *unicode_str;
  	char *tmp;
  	wchar_t *tmp2;
  	//size_t usl;

    va_start(arg_list, format);
    str = NULL;
    unicode_str = NULL;
    while ((j = ft_parser(format, &specs, &bytes_counter)))
    {
    	if ((specs->specs == 'd') || (specs->specs == 'i') || (specs->specs == 'D'))
    	{
			universal_var = va_arg(arg_list, size_t);
			if (specs->specs == 'D')
			{
				specs->length = 'l';
				specs->specs = 'd';
				
			}
			ft_length_signed_conversion(&str, specs, 10, universal_var);
    	}
    	if ((specs->specs == 's') || (specs->specs == 'S'))
    	{
    		if ((specs->specs == 's') && (specs->length != 'l'))
    		{
    			str = va_arg(arg_list, char*);
				if (!str)
					str = ft_strdup("(null)");
				else 
					str = ft_strdup(str);
			}
			if (((specs->specs == 's') && (specs->length == 'l')) || (specs->specs == 'S'))
    		{
    			unicode_str = va_arg(arg_list, wchar_t*);
    			if (!unicode_str)
					{
						specs->unicode = 0;
						specs->specs = 's';
						str = ft_strdup("(null)");
					}
				else
				{
	    			tmp2 = ft_memalloc(sizeof(wchar_t) * (ft_unicode_str_len(unicode_str) + 1));
	    			unicode_str = ft_memcpy(tmp2, unicode_str, ft_unicode_str_len(unicode_str));

	    			//specs->specs = 'S';
	    			specs->unicode = '2';
				}
    		}
		}
    	if ((specs->specs == 'c') || (specs->specs == 'C'))
    	{
    		str = ft_strnew(1);
    		if ((specs->specs == 'c') && (specs->length != 'l'))
    		{
    			str[0] = va_arg(arg_list, int);
				if (!str[0])
				{
					specs->charzero = '1';
					str[0] = 2;
				}
			}
			else if ((specs->length == 'l') || specs->specs == 'C')
			{
				specs->specs = 'c';
	    		unicode_char = va_arg(arg_list, wint_t);
				specs->unicode = '1';
				str[0] = 2;
				if (!unicode_char)
				{
					specs->unicode = 0;
					specs->charzero = '1';
					specs->specs = 'c';
				}
			}
    	}
    	if (specs->specs == 'p')
    	{
			str = ft_itoa_base(va_arg(arg_list, ssize_t), 16);
			tmp = str;
			str = ft_strjoin("0x", str);
			ft_strdel(&tmp);
    	}
	    if (specs->specs == 'o')
		{	
			universal_var = va_arg(arg_list, size_t);
			ft_length_unsigned_conversion(&str, specs, 8, universal_var);
		}
	    if (specs->specs == 'u')
		{			    		
			universal_var = va_arg(arg_list, size_t);
			ft_length_unsigned_conversion(&str, specs, 10, universal_var);
		}
	    if (specs->specs == 'x')
		{			    		
			universal_var = va_arg(arg_list, size_t);
			ft_length_unsigned_conversion(&str, specs, 16, universal_var);
		}
	    if (specs->specs == 'X')
	    {			    		
	    	universal_var = va_arg(arg_list, size_t);
			ft_length_unsigned_conversion(&str, specs, 16, universal_var);
			tmp = str;
			str = ft_str_to_upper(str);
			ft_strdel(&tmp);
		}
		if (specs->specs == 'U')
			str = ft_itoa_base(va_arg(arg_list, unsigned long int), 10);
		if (specs->specs == 'O')
	    	str = ft_itoa_base(va_arg(arg_list, unsigned long int), 8);
	    if (specs->antispecs) 
	    {
	    	str = ft_strnew(1);
	    	str[0] = specs->antispecs;
	    	specs->specs = 'c';
	    }		
	    if ((!str) && (!unicode_str))
	    {
	    	ft_strdel(&str);
	    	free (specs);
	    	return (bytes_counter);///////////////////////////doesn't work
	    }
	// 	printf("str = %s\n", str);
	    init_str_len = ft_strlen(str);
    	
	    if (specs->unicode != '2')
		{   	
			if(str[0] == '-')
	    		specs->negative = '1';
	    	if(str[0] == '0')
	    		specs->zero_octal_hex = '1';
	    	ft_precision_conversion(&str, specs, init_str_len);
	    //	printf("str2 = %s\n", str);
	    	ft_flag_conversion(&str, specs);
	    //	printf("str3 = %s\n", str);
	    	ft_width_conversion(&str, specs);
	    //	printf("str4 = %s\n", str);
    	}
    	if (specs->unicode == '2')
			ft_unicode_conversion(unicode_str, specs, &bytes_counter);
    	else if (specs->unicode == '1')
    		bytes_counter += ft_find_replace_unicode(str, unicode_char);
    	else if ((specs->prec_zero == '1') && (!specs->charzero))
    		bytes_counter += ft_find_replace_null_decimal(str); 
    	else if (specs->charzero == '1')
    		bytes_counter += ft_find_replace_null_char(str); 
    	else
    		bytes_counter += ft_putstr(str);
    	ft_strdel(&str);
    	//ft_memdel((void**)(&unicode_str));
	    free (specs);
	    format += j;
    }
    va_end(arg_list);
    ft_strdel(&str);
    // write(1, "\n================================\n", 34);
   	// system("leaks a.out ");
   	// write(1, "\n================================\n", 34);
   	free (specs);
    return (bytes_counter);
}
