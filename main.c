#include <stdio.h>
#include "includes/ft_printf.h"
#include <locale.h>

int main(void)
{
  setlocale(P_ALL, "");

	int j;
	int k;

	int i = 214647;
	char c = 'C';
	long int ii = 21474836568;
	char *str = "werwerwer";

	//////////RETURN////////////////
  	// j = ft_printf("my = %-10.5d", 4242);
   //  k =    printf("st = %-10.5d", 4242);

	// j = ft_printf("my = %-3.2d\n", 4);
 //    k =    printf("st = %-3.2d\n", 4);

    j = ft_printf("my = %5.3S", L"лала");
    printf("\n");
    k =    printf("st = %5.3ls", L"лала");

    printf("\nmy = %i\nst = %i\n", j, k);


    // j = ft_printf("my = @moulitest: %#.o %#.0o", 0, 0);
    // printf("\n");
    // k =    printf("st = @moulitest: %#.o %#.0o", 0, 0);

   // printf("\nmy = %i\nst = %i\n", j, k);

    return (0);
}

/*
>>>> 07_conv_S.spec.c ------------ [FAIL] ....F [FAIL] nullWideString -> printf("{%S}", NULL)
>>>> 43_length_modif_hh.spec.c --- [FAIL] ......................F [FAIL] test_err_hhs_up_max -> printf("%hhS, %hhS", 0, L"Á±≥Á±≥")
>>>> 50_min_width.spec.c --------- [FAIL] ..........FF [FAIL] wideString -> printf("{%30S}", L"ÊM-M-^QÊM-^XØ‰∏M-ÂM-^O™ÁM-^L´„M-M-^B")
>>>> 52_min_width_flag_zero.spec.c [FAIL] ........FF. [FAIL] wide_str_posMinWidth_zeroFlag -> printf("{%030S}", L"ÊM-M-^QÊM-^XØ‰∏M-ÂM-^O™ÁM-^L´„M-M-^B")
>>>> 62_flag_space.spec.c -------- [FAIL] ............F.. [FAIL] SNullString_spaceFlag -> printf("{% S}", NULL)
>>>> 72_precision_for_sS.spec.c -- [FAIL] .........FFFFF [FAIL] test_precision_S -> printf("%.4S", L"ÊM-M-^QÊM-^XØ‰∏M-ÂM-^O™ÁM-^L´„M-M-^B")
*/