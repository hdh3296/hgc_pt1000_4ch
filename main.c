
#include <pic18.h>

#include	"main.h"
#include 	"mcu_pic18f65k80.h"
#include 	"initial.h"
#include	"ad_conversion.h"


void onoff_setled(unsigned int Temp_mV)
{

    if (Temp_mV < T32)
    {
        PIN_TEMP_SET_LED = OFF_LED;
    }
    else
    {
        PIN_TEMP_SET_LED = ON_LED;
    }

}


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

		
		// todo !!!

        if (AD_updated_buffer[0])
        {
            AD_updated_buffer[0] = FALSE;

			onoff_setled(AD_IN_mV_buffer[0]);

			//PIN_HEATER_OUT = is_onoff_heater_by_settemp_or_error(arADmV[TEMP_CH]);
        }	

		//onoff_led_by_heater();		
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
