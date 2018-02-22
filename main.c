
#include <pic18.h>

#include	"main.h"
#include 	"mcu_pic18f65k80.h"
#include 	"initial.h"
#include	"ad_conversion.h"


bit b_now_power_on_time;


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


bit is_error(unsigned int now_temp_mv)
{

    PIN_ERR_ALARM_LED = OFF_LED;

    if (now_temp_mv >= 4900)
    {
        PIN_ERR_ALARM_LED = ON_LED;
		
		return TRUE;
    }
	

    if (now_temp_mv <= 100)
    {
        PIN_ERR_ALARM_LED = ON_LED;

		return TRUE;
    }

	return FALSE;

}


unsigned int get_bcd(void)
{
    unsigned int nSetNumber = 0;
    unsigned char bit0 = 0, bit1 = 0, bit2 = 0, bit3 = 0;

    bit0 = ~PIN_SW_BCD_1;
    bit1 = ~PIN_SW_BCD_2;
    bit2 = ~PIN_SW_BCD_3;
    bit3 = ~PIN_SW_BCD_4;

    bit0 = (bit0 << 0);
    bit1 = (bit1 << 1);
    bit2 = (bit2 << 2);
    bit3 = (bit3 << 3);

    nSetNumber = (bit0 | bit1 | bit2 | bit3);

    return nSetNumber;
}


bit set_low_and_high_temp(unsigned int nBCD, 
			tag_TempValueDef *OnTemp, 
			tag_TempValueDef *OffTemp)
{
	switch (nBCD)
	{
	case	0:
		*OnTemp	 = T21;
		*OffTemp = T26;
		break;
	case	1:
		*OnTemp	 = T23;
		*OffTemp = T28;
		break;
	case	2:
		*OnTemp	 = T25;
		*OffTemp = T30;
		break;
	case	3:
		*OnTemp	 = T27;
		*OffTemp = T32;
		break;
	case	4:
		*OnTemp	 = T29;
		*OffTemp = T34;
		break;
	case	5:
		*OnTemp	 = T31;
		*OffTemp = T36;
		break;
	case	6:
		*OnTemp	 = T33;
		*OffTemp = T38;
		break;
	case	7:
		*OnTemp	 = T35;
		*OffTemp = T40;
		break;
	case	8:
		*OnTemp	 = T37;
		*OffTemp = T42;
		break;
	case	9:
		*OnTemp	 = T39;
		*OffTemp = T44;
		break;
	default:			
		return	FALSE;
	}
	
	return TRUE;
}


bit onoff_heater_when_now_power_on_time(unsigned int now_temp_mv, tag_TempValueDef hightemp_for_heater_off)
{

	if (now_temp_mv < (hightemp_for_heater_off - 20)) 
	{
		return ON_RELAY;
	}

	return OFF_RELAY;	
	
}


bit onoff_heater_as_temp(unsigned int now_temp_mv, 
				tag_TempValueDef lowtemp_for_heater_on,
				tag_TempValueDef hightemp_for_heater_off)
{
	
	if (now_temp_mv < lowtemp_for_heater_on)
	{
		return ON_RELAY;
	}

	if (now_temp_mv > hightemp_for_heater_off)
	{
		return OFF_RELAY;
	}	

	return PIN_HEATER_OUT;  
}



bit is_onoff_heater_by_settemp_or_error(unsigned int now_temp_mv)
{
    unsigned int n_bcd;
	static bit bError;
	tag_TempValueDef	lowtemp_for_heater_on, hightemp_for_heater_off;	
	

    bError = is_error(now_temp_mv);
	if (bError)
	{
		return OFF_RELAY;
	}


	n_bcd = get_bcd();	
	set_low_and_high_temp(n_bcd, &lowtemp_for_heater_on, &hightemp_for_heater_off);	
	
			
	if (b_now_power_on_time)  
	{
		b_now_power_on_time = FALSE;		

		return onoff_heater_when_now_power_on_time(now_temp_mv, hightemp_for_heater_off);
	}
	else
	{
		return onoff_heater_as_temp(now_temp_mv, lowtemp_for_heater_on, hightemp_for_heater_off);	
	}
	

	return PIN_HEATER_OUT;
}


void onoff_led_by_heater(void)
{
	if (PIN_HEATER_OUT == ON_RELAY)
	{
		PIN_HEATER_LED	= ON_LED;	
	}
	else
	{
		PIN_HEATER_LED	= OFF_LED;	
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


	b_now_power_on_time = TRUE;

    while (1)
    {
		CLRWDT();

		process_AD();

		
		// todo !!!

        if (AD_updated_buffer[0])
        {
            AD_updated_buffer[0] = FALSE;

			onoff_setled(AD_IN_mV_buffer[0]);

			PIN_HEATER_OUT = is_onoff_heater_by_settemp_or_error(AD_IN_mV_buffer[0]);
        }	

		onoff_led_by_heater();		
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
