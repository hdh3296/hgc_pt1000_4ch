
#include <pic18.h>

#include "mcu_pic18f65k80.h"
#include "initial.h"

void main(void)
{
	di();
	CPU_Initial();
	PortInit();
	Timer0Init();
    ei();

    while (1)
    {
		CLRWDT();	

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
}
