#include "stdio.h"

__attribute__((constructor)) void main()
{
	int		opa;
	int		opb;
	unsigned int    res;
	int		iter=0;

	         char	        c;
	         unsigned int	s;

	while(1) 
        {
	    iter++;
	    // g�n�ration op�randes
	    opa = rand();
	    opb = rand();

	    // �criture op�randes
	    gcd_set_opa(opa);
	    gcd_set_opb(opb);

	    // d�marrage
	    gcd_start();

	    // test status
	    s = 1;
	    while( s!=0 ) { gcd_get_status(&s); }

	    // lecture r�sultat
	    gcd_get_result(&res);

	    //affichage
	    tty_printf("############### iter = %d ###############\n",iter);
	    tty_printf("   - cycle = %d\n",proctime());
	    tty_printf("   - opa   = %d\n",opa);
	    tty_printf("   - opb   = %d\n",opb);
	    tty_printf("   - pgcd  = %d\n",res);

	    // next computation
	    tty_getc_irq((char*)&c);

        }

} // end main
