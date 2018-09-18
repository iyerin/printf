#include "ft_printf.h"

// int	ft_putstr_zero(char const *s)
// {
// 	int i;

// 	i = 0;
// 	if (!s)
// 		return (i);
// 	while (*s)
// 	{
// 		i += write(1, s, 1);
// 		s++;
// 	}
// 	write(1, "\0", 1);
// 	return (i);
// }

int	ft_find_replace_null_decimal(char const *s)
{
	int i;
	//printf("HUUUUUI\n");
	i = 0;
	if (!s)
		return (i);
	while (*s)
	{
		if(*s != 2)
			i += write(1, s, 1);
		s++;
	}
	//printf("i = %i\n", i);
	//write(1, "\0", 1);
	return (i);
}

int	ft_find_replace_null_char(char const *s)
{
	int i;
	//printf("TYYYYYYT\n");
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
	//printf("i = %i\n", i);
	//write(1, "\0", 1);
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
  //	char c;

  //	str = malloc(1024);
    va_start(arg_list, format);
    str = NULL;
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
    	if (specs->specs == 's')
    	{
			str = va_arg(arg_list, char*);
			if (!str)
			{
				str = ft_strnew(6);
				str = "(null)";
			}
		}
    	if (specs->specs == 'c')
    	{
    		str = ft_strnew(1);
    		str[0] = va_arg(arg_list, int);
			if (!str[0])
			{
			//	printf("HUYARA\n");
				str = ft_strnew(1);
				specs->charzero = '1';
				str[0] = 2;
			}
    	}
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

	    if (!str)
	    {
	    	//printf("SSSSSSSS\n");
	    	return (bytes_counter);
	    }

	    // S
	 //    if (specs->specs == 'C')
	 //    {			    		
	 //    	universal_var = va_arg(arg_list, size_t);
		// 	ft_length_unsigned_conversion(&str, specs, 16, universal_var);
		// 	str = ft_str_to_upper(str);
		// }

	// 	printf("str = %s\n", str);
	    init_str_len = ft_strlen(str);
    	
    	//printf("TYT\n");
    	if(str[0] == '-')
    		specs->negative = '1';
    	if(str[0] == '0')
    		specs->zero_octal_hex = '1';
    	//printf("TYT2\n");
    	
    	ft_precision_conversion(&str, specs, init_str_len);
    //	printf("str2 = %s\n", str);
    	
    	ft_flag_conversion(&str, specs);
    //	printf("str3 = %s\n", str);

    	ft_width_conversion(&str, specs);
    //	printf("str4 = %s\n", str);

    	if ((specs->prec_zero == '1') && (!specs->charzero))
    		bytes_counter += ft_find_replace_null_decimal(str); 
    	else if (specs->charzero == '1')
    	{
    		//printf("%s\n", );
    		bytes_counter += ft_find_replace_null_char(str); 
    	}
    	else
    		bytes_counter += ft_putstr(str);
	    //free (specs);
	    format += j;
    }

    va_end(arg_list);
    return (bytes_counter);
}
