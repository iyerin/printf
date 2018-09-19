#ifndef FT_PRINTF_H
#define FT_PRINTF_H

#include <stdio.h>
#include "./libft.h" /////// way
#include <stdarg.h>
#include <stdlib.h>
#include <wchar.h>

int ft_printf(const char *format, ...);

typedef struct	s_flags
{
    char    *text;
    char	minus;
    char	plus;
    char	hash;
    char	zero;
    char	space;
    size_t		width;
    int		precision;
    char    length;
    char    specs;
    char    negative;
    char    antispecs;
    char    charzero;
    char    zero_octal_hex;
    char    prec_zero;
    char    unicode;
}				t_flags;

// typedef struct	s_var
// {
// 	char		*str;
// 	//pointer
// 	int			i;
// 	long int	li;
// 	unsigned int	ui;
// 	unsigned long int	uli;
// 	char 				c;

// }				t_var;

char	*ft_itoa_base(size_t value, size_t base);
int     ft_specifier_is_true (char format);
int   ft_parser(const char *format, t_flags **specs, ssize_t *bytes_counter);
void ft_flag_conversion(char **str, t_flags *specs);
void ft_length_signed_conversion(char **str, t_flags *specs, size_t base, size_t universal_var);
void ft_length_unsigned_conversion(char **str, t_flags *specs, size_t base, size_t universal_var);
int ft_arg_is_numeric(char format);
void ft_width_conversion(char **str, t_flags *specs);
void ft_precision_conversion(char **str, t_flags *specs, ssize_t init_str_len);

#endif

/*			switch (*format) 
			{
				case '#':
				  specs.hash = 1;
				  break;
				case '-':
				  specs.minus = 1;
				  break;
				case '+':
				  specs.plus = 1;
				  break;
				 case ' ':
				  specs.space = 1;
				  break;
				 case '0':
				  specs.zero = 1;
				  break;
				default:
				  break;
			}*/



	// while (format)
	// {
	//     if (*format == '%')
	//     {
	//     	format++;
	// 	    i = parsing(format, t_specs);
	// 	    format += i;

	// 	    get_type_data(); // va_arg(arg_list, TYPE);

	// 	   	work_with_data();

	// 	   	write_data_to_buffer();

	// 	   	output_buffer();
	// 	}
	// 	else
	// 		write_to_buffer();
	// 	format++;
	// }


    // char *str = "test";
    // int i = 123;
   // printf("osapon is %c%copa\n", 122, 104);
  //  ft_printf("MY  = numbers is %-+#20.400hd %s \n", i, str);




    		// if (specs->length == 'H')
    		// {
    		// //	printf("HUI\n");
    		// 	signed_var = (signed char)(va_arg(arg_list, int));
    		// 	//str = ft_itoa_base(signed_var, 10);    		
    		// }
    		// else if (specs->length == 'h')
    		// {
    		// 	signed_var = (short int)(va_arg(arg_list, int));
    		// 	//str = ft_itoa_base(signed_var, 10);    		
    		// }
    		// else if (specs->length == 'l')
    		// {
    		// 	signed_var = (long int)(va_arg(arg_list, long int));
    		// 	//str = ft_itoa_base(signed_var, 10);    		
    		// }
    		// else if (specs->length == 'L')
    		// {
    		// 	signed_var = (ssize_t)(va_arg(arg_list, ssize_t));
    		// 	//printf("SV = %zu\n", signed_var);
    		// 	//str = ft_itoa_base(signed_var, 10);
    		// 	//printf("SV2 = %s\n", str);   		
    		// }
    		// else if (specs->length == 'j')
    		// {
    		// 	signed_var = (intmax_t)(va_arg(arg_list, intmax_t));
    		// 	//str = ft_itoa_base(signed_var, 10);    		
    		// }
    		// else if (specs->length == 'z')
    		// {
    		// 	signed_var = (ssize_t)(va_arg(arg_list, ssize_t));
    		// 	//str = ft_itoa_base(unsigned_var, 10);    		
    		// }
    		// else
    		// 	signed_var = (va_arg(arg_list, int));
    		// 	//str = ft_itoa_base(va_arg(arg_list, int), 10);
    		// if (signed_var >= 0)
    		// 	str = ft_itoa_base(signed_var, 10);
    		// else
    		// {
    		// 	unsigned_var = -signed_var;
    		// 	str = ft_strjoin("-", ft_itoa_base(unsigned_var, 10));
    		// }





			// if (specs->length == 'H')
		 //    	unsigned_var = (unsigned char)(va_arg(arg_list, int));
			// else if (specs->length == 'h')
			// 	unsigned_var = (unsigned short int)(va_arg(arg_list, int));
			// else if (specs->length == 'l')
			// 	unsigned_var = (unsigned long int)(va_arg(arg_list, unsigned long int));
			// else if (specs->length == 'L')
			// 	unsigned_var = (unsigned long long int)(va_arg(arg_list, unsigned long long int));
			// else if (specs->length == 'j')
			// 	unsigned_var = (uintmax_t)(va_arg(arg_list, uintmax_t));
			// else if (specs->length == 'z')
			// 	unsigned_var = (size_t)(va_arg(arg_list, size_t));
			// else
			// 	unsigned_var = (va_arg(arg_list, unsigned int));
			// str = ft_itoa_base(unsigned_var, 8);

