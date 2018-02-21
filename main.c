
#include <pic18.h>

#include 	"mcu_pic18f65k80.h"
#include 	"initial.h"
#include	"ad_conversion.h"

void main(void)
{
	di();
	CPU_Initial();
	PortInit();
	Timer0Init();
	InitAD();
    ei();

	DONE = 1;	

    while (1)
    {
		CLRWDT();

		process_AD();
    }
}


void interrupt isr(void)
{
	static unsigned int timer_msec = 0;

    if (TMR0IF)
    {
        TMR0IF = 0 ;
        TMR0L = MSEC_L;
        TMR0H = MSEC_H;

		timer_msec++;
		if (timer_msec > 500)
		{
			timer_msec = 0;
			LATD0 = ~LATD0;
		}
    }

    if (ADIF)
    {
        unsigned int ad;
        ad = ADRES;

		set_input_ad(ad);
		
        ADIF = 0;
        DONE = 0;
    }	
}
