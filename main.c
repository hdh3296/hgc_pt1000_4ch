
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
	unsigned	heater_led_onoff	: 1;
	unsigned	error_led_onoff		: 1;
	unsigned	set_led_onoff		: 1;

	unsigned	b_now_power_on_time	: 1;
	
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


bit is_error(unsigned int ch, unsigned int now_temp_mv)
{

    pt1000[ch].error_led_onoff = OFF_LED;

    if (now_temp_mv >= 4900)
    {
        pt1000[ch].error_led_onoff = ON_LED;
		
		return TRUE;
    }
	

    if (now_temp_mv <= 100)
    {
        pt1000[ch].error_led_onoff = ON_LED;

		return TRUE;
    }

	return FALSE;

}

volatile unsigned int xxxxxx;
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
	xxxxxx = nSetNumber;
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


bit onoff_heater_as_temp(unsigned int ch,
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



bit is_onoff_heater_by_settemp_or_error(unsigned int ch, unsigned int now_temp_mv)
{
    unsigned int n_bcd;
	static bit bError;
	tag_TempValueDef	lowtemp_for_heater_on, hightemp_for_heater_off;	
	

    bError = is_error(ch, now_temp_mv);
	if (bError)
	{
		return OFF_RELAY;
	}


	n_bcd = get_bcd(ch);	
	set_low_and_high_temp(n_bcd, &lowtemp_for_heater_on, &hightemp_for_heater_off);	
	
			
	if (pt1000[ch].b_now_power_on_time)  
	{
		pt1000[ch].b_now_power_on_time = FALSE;		

		return onoff_heater_when_now_power_on_time(now_temp_mv, hightemp_for_heater_off);
	}
	else
	{
		return onoff_heater_as_temp(ch, now_temp_mv, lowtemp_for_heater_on, hightemp_for_heater_off);	
	}
}


bool onoff_led_by_heater(unsigned int ch)
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


void onoff_heater_relay_all()
{
	PIN_HEATER_0_OUT = pt1000[0].heater_onoff;
	PIN_HEATER_1_OUT = pt1000[1].heater_onoff;
	PIN_HEATER_2_OUT = pt1000[2].heater_onoff;
	PIN_HEATER_3_OUT = pt1000[3].heater_onoff;
}


void onoff_set_led_all()
{
	PIN_TEMP_SET_LED_0	= pt1000[0].set_led_onoff;
	PIN_TEMP_SET_LED_1	= pt1000[1].set_led_onoff;
	PIN_TEMP_SET_LED_2	= pt1000[2].set_led_onoff;
	PIN_TEMP_SET_LED_3	= pt1000[3].set_led_onoff;
}

void set_heater_led_to_onoff()
{
	PIN_HEATER_LED_0 = pt1000[0].heater_led_onoff;
	PIN_HEATER_LED_1 = pt1000[1].heater_led_onoff;
	PIN_HEATER_LED_2 = pt1000[2].heater_led_onoff;
	PIN_HEATER_LED_3 = pt1000[3].heater_led_onoff;
}


void set_error_led_to_ofoff()
{
	PIN_ERR_ALARM_LED_0 = pt1000[0].error_led_onoff;
	PIN_ERR_ALARM_LED_1 = pt1000[1].error_led_onoff;
	PIN_ERR_ALARM_LED_2 = pt1000[2].error_led_onoff;
	PIN_ERR_ALARM_LED_3 = pt1000[3].error_led_onoff;
}


void get_bcd_input()
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

void onoff_heater_as_channel(unsigned int ch)
{
	
	if (AD_updated_buffer[ch])
	{		
		AD_updated_buffer[ch] = FALSE;
	
		pt1000[ch].set_led_onoff = onoff_setled(AD_IN_mV_buffer[ch]);
	
		pt1000[ch].heater_onoff = is_onoff_heater_by_settemp_or_error(ch, AD_IN_mV_buffer[ch]);
	}	

	pt1000[ch].heater_led_onoff = onoff_led_by_heater(ch);

	onoff_heater_relay_all();	
	onoff_set_led_all();
	set_heater_led_to_onoff();
	set_error_led_to_ofoff();
	get_bcd_input();
}


void onoff_heater_when_adupdated()
{
	unsigned int i;

	for (i=0; i<4; i++)
	{
		onoff_heater_as_channel(i);
	}

}

void main(void)
{
	unsigned int ch;

	di();
	CPU_Initial();
	PortInit();
	Timer0Init();
	InitAD();
    ei();

	DONE = 1;	
	

	for (ch=0; ch<MAX_CH; ch++)
	{
		pt1000[ch].b_now_power_on_time = TRUE;
	}

	
    while (1)
    {
		CLRWDT();

		process_AD();

		
		// todo !!!
		onoff_heater_when_adupdated();

				
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
