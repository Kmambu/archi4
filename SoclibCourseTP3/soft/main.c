#include "stdio.h"

#define VCI_GCD_OPA	0x95000000
#define VCI_GCD_OPB	0x95000004
#define VCI_GCD_START	0x95000008
#define VCI_GCD_STATUS	0x9500000c

__attribute__((constructor)) void  main()
{
	char c;
	unsigned int opa = 0, opb = 0, status = 0, res = 0, cycle = 0, iter = 0;

	while(1) 
	{
		opa = (int) rand() + 1;
		gcd_set_opa(opa);

		opb = (int) rand() + 1;
		gcd_set_opb(opb);

		gcd_start();

		gcd_get_status(&status);
		while (status != 0) {
			gcd_get_status(&status);
		}

		gcd_get_result(&res);

		cycle = proctime();
		tty_printf("**** main **** iter=%d, cycle = %d\n", iter, cycle);
		tty_printf("opa = %d\n", opa);
		tty_printf("opb = %d\n", opb);
		tty_printf("res = %d\n\n", res);
		iter++;

		tty_getc(&c);
	}

} // end main
