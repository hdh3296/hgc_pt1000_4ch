
#include <pic18.h>

#include	"main.h"
#include 	"mcu_pic18f65k80.h"
#include 	"initial.h"
#include	"ad_conversion.h"


#define MAX_CH	4


typedef struct
{
	unsigned	bcd_1				: 1; 
	unsigned	bcd_2				: 1;
	unsigned	bcd_3				: 1;
	unsigned	bcd_4				: 1;
	
	unsigned	heater_onoff		: 1;
	unsigned	heaterled_onoff	: 1;
	unsigned	errorled_onoff		: 1;
	unsigned	setled_onoff		: 1;

	unsigned	b_turned_on_power	: 1;
	
}	HgcPt1000;

HgcPt1000	pt1000[MAX_CH];


bool onoff_setled(unsigned int Temp_mV)
{

    if (Temp_mV < T32)
    {
        return OFF_LED;
    }
    else
    {
        return ON_LED;
    }
}



bool is_error(unsigned int now_temp_mv)
{
	return (now_temp_mv >= 4900) || (now_temp_mv <= 100);
}


unsigned int get_bcd(unsigned int ch)
{
    unsigned int nSetNumber = 0;
    unsigned char bit0 = 0, bit1 = 0, bit2 = 0, bit3 = 0;

    bit0 = (~pt1000[ch].bcd_1) & 0x01;
    bit1 = (~pt1000[ch].bcd_2) & 0x01;
    bit2 = (~pt1000[ch].bcd_3) & 0x01;
    bit3 = (~pt1000[ch].bcd_4) & 0x01;

    bit0 = (bit0 << 0);
    bit1 = (bit1 << 1);
    bit2 = (bit2 << 2);
    bit3 = (bit3 << 3);

    nSetNumber = (bit3 | bit2 | bit1 | bit0);

    return nSetNumber;
}


bool set_low_and_high_temp(unsigned int nBCD, 
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


bool onoff_heater_when_now_power_on_time(unsigned int now_temp_mv, tag_TempValueDef hightemp_for_heater_off)
{

	if (now_temp_mv < (hightemp_for_heater_off - 20)) 
	{
		return ON_RELAY;
	}

	return OFF_RELAY;	
	
}


bool onoff_heater_as_temp(unsigned int ch,
				unsigned int now_temp_mv, 
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

	return pt1000[ch].heater_onoff;  
}



bool onoff_heater_by_settemp_or_error(unsigned int ch, unsigned int now_temp_mv)
{
	tag_TempValueDef	lowtemp_for_heater_on, hightemp_for_heater_off;		

	if (is_error(now_temp_mv))
	{
		pt1000[ch].errorled_onoff = ON_LED;
		return OFF_RELAY;
	}
	pt1000[ch].errorled_onoff = OFF_LED;

	
	set_low_and_high_temp(get_bcd(ch), &lowtemp_for_heater_on, &hightemp_for_heater_off);		

	
	if (pt1000[ch].b_turned_on_power)  
	{
		pt1000[ch].b_turned_on_power = FALSE;		
		return onoff_heater_when_now_power_on_time(now_temp_mv, hightemp_for_heater_off);
	}
	
	
	return onoff_heater_as_temp(ch, now_temp_mv, lowtemp_for_heater_on, hightemp_for_heater_off);	
	
}




bool onoff_heaterled_by_heater(unsigned int ch)
{
	if (pt1000[ch].heater_onoff == ON_RELAY)
	{
		return ON_LED;	
	}
	else
	{
		return OFF_LED;	
	}
}


void set_all_heater_pin()
{
	PIN_HEATER_0_OUT = pt1000[0].heater_onoff;
	PIN_HEATER_1_OUT = pt1000[1].heater_onoff;
	PIN_HEATER_2_OUT = pt1000[2].heater_onoff;
	PIN_HEATER_3_OUT = pt1000[3].heater_onoff;
}


void set_all_setled_pin()
{
	PIN_TEMP_SET_LED_0	= pt1000[0].setled_onoff;
	PIN_TEMP_SET_LED_1	= pt1000[1].setled_onoff;
	PIN_TEMP_SET_LED_2	= pt1000[2].setled_onoff;
	PIN_TEMP_SET_LED_3	= pt1000[3].setled_onoff;
}

void set_all_heaterled_pin()
{
	PIN_HEATER_LED_0 = pt1000[0].heaterled_onoff;
	PIN_HEATER_LED_1 = pt1000[1].heaterled_onoff;
	PIN_HEATER_LED_2 = pt1000[2].heaterled_onoff;
	PIN_HEATER_LED_3 = pt1000[3].heaterled_onoff;
}


void set_all_errorled_pin()
{
	PIN_ERR_ALARM_LED_0 = pt1000[0].errorled_onoff;
	PIN_ERR_ALARM_LED_1 = pt1000[1].errorled_onoff;
	PIN_ERR_ALARM_LED_2 = pt1000[2].errorled_onoff;
	PIN_ERR_ALARM_LED_3 = pt1000[3].errorled_onoff;
}


void set_all_bcd_by_input_pin()
{
	pt1000[0].bcd_1 = PIN_SW_BCD_1_A;
	pt1000[0].bcd_2 = PIN_SW_BCD_2_A;
	pt1000[0].bcd_3 = PIN_SW_BCD_3_A;
	pt1000[0].bcd_4 = PIN_SW_BCD_4_A;

	pt1000[1].bcd_1 = PIN_SW_BCD_1_B;
	pt1000[1].bcd_2 = PIN_SW_BCD_2_B;
	pt1000[1].bcd_3 = PIN_SW_BCD_3_B;
	pt1000[1].bcd_4 = PIN_SW_BCD_4_B;

	pt1000[2].bcd_1 = PIN_SW_BCD_1_C;
	pt1000[2].bcd_2 = PIN_SW_BCD_2_C;
	pt1000[2].bcd_3 = PIN_SW_BCD_3_C;
	pt1000[2].bcd_4 = PIN_SW_BCD_4_C;

	pt1000[3].bcd_1 = PIN_SW_BCD_1_D;
	pt1000[3].bcd_2 = PIN_SW_BCD_2_D;
	pt1000[3].bcd_3 = PIN_SW_BCD_3_D;
	pt1000[3].bcd_4 = PIN_SW_BCD_4_D;	
}



void onoff_setled_heater_as_channel(unsigned int ch)
{
	
	if (b_updated_ad[ch])
	{		
		b_updated_ad[ch] = FALSE;

		pt1000[ch].setled_onoff = onoff_setled(ad_updated_mv[ch]);	

		pt1000[ch].heater_onoff = onoff_heater_by_settemp_or_error(ch, ad_updated_mv[ch]);
	}	
}


void init_pt1000()
{
	unsigned int ch;

	for (ch=0; ch<MAX_CH; ch++)
	{
		pt1000[ch].b_turned_on_power = TRUE;

		pt1000[ch].bcd_1	= 1;
		pt1000[ch].bcd_2	= 1;
		pt1000[ch].bcd_3	= 1;
		pt1000[ch].bcd_4	= 1;

		pt1000[ch].heater_onoff		=	OFF_RELAY;
		pt1000[ch].heaterled_onoff	=	OFF_LED;
		pt1000[ch].errorled_onoff	=	OFF_LED;
		pt1000[ch].setled_onoff		=	OFF_LED;

		
	}
}


void main(void)
{
	

	di();
	init_mcu();
	init_port();
	init_timer0();
	init_ad();
    ei();

	b_conversion_ad = 1;	
	
	init_pt1000();

	
    while (1)
    {
		unsigned int i;
	
		CLRWDT();

		process_ad();

		
		// todo !!!
		for (i=0; i<4; i++)
		{
			onoff_setled_heater_as_channel(i);

			pt1000[i].heaterled_onoff = onoff_heaterled_by_heater(i);
		}				

		set_all_heater_pin();	
		set_all_heaterled_pin();
		set_all_setled_pin();			
		set_all_errorled_pin();
		set_all_bcd_by_input_pin();		
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
			PIN_RUN_LED = ~PIN_RUN_LED;
		}

    }

    if (ADIF)
    {
        unsigned int ad;
        ad = ADRES;

		set_input_ad(ad);
		
        ADIF = 0;
        b_conversion_ad = 0;
    }	
}
