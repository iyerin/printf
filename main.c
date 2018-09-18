#include <stdio.h>
#include "includes/ft_printf.h"

int main(void)
{
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

    j = ft_printf("my = %05.c", 0);
    printf("\n");
    k =    printf("st = %05.c", 0);

    printf("\nmy = %i\nst = %i\n", j, k);


    // j = ft_printf("my = @moulitest: %#.o %#.0o", 0, 0);
    // printf("\n");
    // k =    printf("st = @moulitest: %#.o %#.0o", 0, 0);

   // printf("\nmy = %i\nst = %i\n", j, k);

    return (0);
}

/*
>>>> 07_conv_S.spec.c ------------ [FAIL] FFFFF [FAIL] test_simple -> printf("%S", L"Á±≥")
>>>> 17_conv_C.spec.c ------------ [FAIL] FFFFFFFFF [FAIL] test_simple_char -> printf("%C", 'c')
>>>> 18_mix_all_previous.spec.c -- [FAIL] FF [FAIL] test_simple -> printf("%s %C %d %p %x %% %S", "bonjour ", L'Ë©≤', 42, &free, 42, L"ŸM-^Dÿ≠ŸM-^E ÿÆŸM-^Fÿ...
>>>> 40_length_modif_l.spec.c ---- [FAIL] ..............FF... [FAIL] test_lc_wchar -> printf("%lc, %lc", L'ÊM-^ZM-^V', L'ÿ≠')
>>>> 43_length_modif_hh.spec.c --- [FAIL] .....................FF [FAIL] test_err_hhc_up_max -> printf("%hhC, %hhC", 0, L'Á±≥')





>>>> 50_min_width.spec.c --------- [FAIL] ..........FF [FAIL] wideString -> printf("{%30S}", L"ÊM-M-^QÊM-^XØ‰∏M-ÂM-^O™ÁM-^L´„M-M-^B")
>>>> 52_min_width_flag_zero.spec.c [FAIL] ........FF. [FAIL] wide_str_posMinWidth_zeroFlag -> printf("{%030S}", L"ÊM-M-^QÊM-^XØ‰∏M-ÂM-^O™ÁM-^L´„M-M-^B")


>>>> 61_flag_plus.spec.c --------- [FAIL] .....F....... [FAIL] test_plus_c_up_zero -> printf("%+C", 0)
>>>> 62_flag_space.spec.c -------- [FAIL] ..........FFFFF [FAIL] test_space_C_zero -> printf("{% C}", 0)
>>>> 72_precision_for_sS.spec.c -- [FAIL] .........FFFFF [FAIL] test_precision_S -> printf("%.4S", L"ÊM-M-^QÊM-^XØ‰∏M-ÂM-^O™ÁM-^L´„M-M-^B")
>>>> 73_precision_for_cC.spec.c -- [FAIL] ...FFF [FAIL] cUpperNullChar -> printf("%.C", 0)
     
     >>>> 74_precision_for_p.spec.c --- [FAIL] FF..FF [FAIL] pNullPointer_zeroPrecision -> printf("%.0p, %.p", 0, 0)


     >>>> 79_precision_mixed_with_flags [FAIL] ..FFFFF.FF [FAIL] test_precision_p_zero -> printf("%.p, %.0p", 0, 0)
*/