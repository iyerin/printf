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

    j = ft_printf("my = %5.d %5.0d", 0, 0);
    printf("\n");
    k =    printf("st = %5.d %5.0d", 0, 0);

    printf("\nmy = %i\nst = %i\n", j, k);
///////////prec??
    return (0);
}

/*
  48. FAIL ft_printf("@moulitest: %5.x %5.0x", 0, 0);    -> "@moulitest:            "
  94. FAIL ft_printf("@moulitest: %5.o %5.0o", 0, 0);    -> "@moulitest:            "
  95. FAIL ft_printf("@moulitest: %#.o %#.0o", 0, 0);    -> "@moulitest: 0 0"
 172. FAIL ft_printf("%03.2d", -1);                      -> "-01"
 176. FAIL ft_printf("@moulitest: %5.d %5.0d", 0, 0);    -> "@moulitest:            "
*/
