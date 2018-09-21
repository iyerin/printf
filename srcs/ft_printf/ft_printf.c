#include "ft_printf.h"

int	ft_countchar(int value)
{
	if (value < 128)
		return (1);
	else if (value < 2048) 
	{
		return (2);
	}
	else if (value < 65536) 
	{
		return (3);
	}
	else if (value <= 1114111) 
	{
		return (4);
	}
	else
		return (0);
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
	//size_t i = 0;
	wchar_t	*new_str;
	int j = specs->precision;
	int k = 0;
	wchar_t *tmp;

	new_str = ft_memalloc(sizeof(wchar_t) * (specs->precision + 1));
	tmp = new_str;
	while(j > 0)
	{
	//	printf("T\n");
		k = ft_countchar(*unicode_str);
	//	printf("k = %i\n", k);
	//	printf("j = %i\n", j);
		if(j >= k)
		{
		//	printf("old = %C\n", *unicode_str);
			*new_str = *unicode_str;
		//	printf("new = %C\n", *new_str);
			new_str++;
			unicode_str++;
		}
		j -= k;
	}
	//printf("HHH\n");
	return (tmp);
}



int 	ft_print_unicode_str(wchar_t *unicode_str)
{
	int i;
//printf("HUI\n");
	i = 0;
	if (!unicode_str)
		return (i);
	//ft_putchar(*unicode_str);
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
//	size_t free_space = 0;
	wchar_t	*tmp;
	wchar_t *tmp2;
	wchar_t *new_str;

	tmp = unicode_str;
	// if (!unicode_str)
	// 	return (i);
	//ft_putchar(*unicode_str);
	while (*unicode_str)
	{
		i += ft_countchar(*unicode_str);
		unicode_str++;
	}
	unicode_str = tmp;
//	printf("\ni = %zi\n", i);
//	printf("str1 = %S\n", unicode_str);
	if (((specs->precision > 0) || (specs->prec_zero)) &&  (size_t)specs->precision < i)
		new_str = ft_unicode_precision(unicode_str, specs);
	else
		new_str = unicode_str;
//	printf("NEWSTR = %ls\n", new_str);
	tmp2 = new_str;
	i = 0;
	while (*new_str)
	{
		i += ft_countchar(*new_str);
		new_str++;
	}
	new_str = tmp2;
//	printf("\ni = %zi\n", i);
//	printf("str2 = %S\n", new_str);
	if (specs->width > i)
	{
		if (specs->minus)
		{
			*bytes_counter += ft_print_unicode_str(new_str);
			while (specs->width > i)
			{
				*bytes_counter += write(1, " ", 1);
				specs->width --;
			}
		}
		else
		{
			while (specs->width > i)
			{
				*bytes_counter += write(1, " ", 1);
				specs->width --;
			}
			*bytes_counter += ft_print_unicode_str(new_str);
		}
	}
	else 
		*bytes_counter += ft_print_unicode_str(new_str);
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
	return (tmp);
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

  	//printf("==%C==", va_arg(arg_list, wchar_t));
  //	unicode_str = malloc(sizeof(wchar_t) * 1024);


    va_start(arg_list, format);
    str = NULL;
    unicode_str = NULL;
    while ((j = ft_parser(format, &specs, &bytes_counter)))
    {
    	//printf("i = %zu\n", bytes_counter);
    //	printf("Spec = %c\n", specs->specs);
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
				{
					str = ft_strnew(6);
					str = "(null)";
				}
			}
			if (((specs->specs == 's') && (specs->length == 'l')) || (specs->specs == 'S'))
    		{
    			unicode_str = va_arg(arg_list, wchar_t*);
    			//specs->specs = 'S';
    			specs->unicode = '2';
    			if (!unicode_str)
					{
						specs->unicode = 0;
						specs->specs = 's';
						str = ft_strnew(6);
						str = "(null)";

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


   //  	if ((specs->specs == 'c') || (specs->specs == 'C'))
   //  	{
   //  		str = ft_strnew(1);
   //  		if ((specs->specs == 'c') && (specs->length != 'l'))
   //  		{
   //  			str[0] = va_arg(arg_list, int);
			// 	if (!str[0])
			// 	{
			// 		specs->charzero = '1';
			// 		str[0] = 2;
			// 	}
			// }
			// else if ((specs->length == 'l') || specs->specs == 'C')
			// {
			// 	specs->specs = 'C';
	  //   		unicode_char = va_arg(arg_list, wint_t);
			// 	specs->unicode = '1';
			// 	str[0] = 2;
			// }
   //  	}
    	if (specs->specs == 'p')
			str = ft_strjoin("0x", ft_itoa_base(va_arg(arg_list, ssize_t), 16));
	    // if (specs->specs == 'D')
	    // 	str = ft_itoa_base(va_arg(arg_list, long int), 10);
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
			str = ft_str_to_upper(str);
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

	 //    if (specs->specs == 'C')
	 //    {
	 //    //printf("%s\n", "HHHHHHHHHHHH");			    		
  //   		str = ft_strnew(1);
  //   		unicode_char = va_arg(arg_list, int);
		// 	specs->unicode = '1';
		// 	str[0] = 2;
		// }
		//write(1, "HUI", 3);
		

		
	    if ((!str) && (!unicode_str))
	    {
	    	//printf("YO\n");
	    	return (bytes_counter);
	    }
	// 	printf("str = %s\n", str);
	    init_str_len = ft_strlen(str);
    	
	    if (specs->unicode != '2')
		{ 
			//printf("RRR\n");   	
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
    	{
    		//printf("AAA\n");
    		bytes_counter += ft_find_replace_unicode(str, unicode_char);
    	}
    	// else if (specs->unicode == '2')
    	// {
    	// 	bytes_counter += ft_print_unicode_str(unicode_str);
    	// }
    	else if ((specs->prec_zero == '1') && (!specs->charzero))
    		bytes_counter += ft_find_replace_null_decimal(str); 
    	else if (specs->charzero == '1')
    		bytes_counter += ft_find_replace_null_char(str); 
    	else
    		bytes_counter += ft_putstr(str);
	    //free (specs);
	    format += j;
    }

    va_end(arg_list);
    return (bytes_counter);
}
