
#include    <pic18.h>
#include	"ad_conversion.h"




unsigned    int   	AD_channel;
bit	AD_interrupted = 0;
unsigned 	int	    in_ad_changed 	= 0;
bool b_ad_calc_enable;
unsigned char ad_calc_wait_count;
unsigned	long    SumAD	= 0;
unsigned	int	    SumCnt	= 0;

#define CH_MAX	2 // todo
unsigned int AD_IN_mV_buffer[CH_MAX] = {0,}; // 각 채널에서 읽어드린 AD 값 
unsigned char AD_updated_buffer[CH_MAX] = {0,};

unsigned int ccr_in_current_mV = 0;
bit A_IN_mV_was_updated = FALSE;
unsigned int V_IN_mV = 0;
unsigned    int   	bef_ad_channel	= 0;


void	InitAD(void)
{
    ADCON0 = 0x01;	//ADON = 1;
    ADCON1 = 0x80;  //event= timer1

    ADFM = 1;		// period is an 8 bit value, right justify to get result from ADRESH
    ADCS2 = 1;
    ADCS1 = 1;
    ADCS0 = 0;  	// 1Tad = 2 usec >= 1.6usec
    ACQT2 = 1;
    ACQT1 =  0;
    ACQT0 = 0; 	// acquisition time >= 16~20 usec

    ANCON0 = 0x0f;  // an0-an4
    ANCON1 = 0x0;		// digital

    ADIP = 0;
    ADIF = 0;
    ADIE = 1;

    DONE = 1;

}


bool is_ad_calc_enable()
{
    ad_calc_wait_count++;
    if (ad_calc_wait_count >= 3)
    {
        ad_calc_wait_count = 0;
        return TRUE;
    }

    return FALSE;
}


bool is_update_AD(   )
{
    unsigned long AdVal;
    unsigned char i;
    unsigned char sum_count;

    if (!AD_interrupted) return FALSE;

    // 변경시 쓰레기 값이 저장되는 문제 때문에 추가 하였다.
    if (!b_ad_calc_enable)
    {
        b_ad_calc_enable = is_ad_calc_enable();
    }
    else
    {
        SumAD = SumAD + (unsigned long)in_ad_changed; // 12비트 AD
        SumCnt++;

        sum_count = 100;
        if (SumCnt >= sum_count)
        {
            AdVal =  ((SumAD * 1000) / (0xfff / 5)) / SumCnt ; // 12비트 5000 mV 기준
            AD_IN_mV_buffer[AD_channel] = (unsigned int)AdVal;
            AD_updated_buffer[AD_channel] = TRUE;

            SumAD = 0;
            SumCnt = 0;


            return TRUE;
        }
    }


    AD_interrupted = FALSE;
    DONE = 1;

    return FALSE;
}


void update_A_IN_mA__and__V_IN_mV(void)
{
    unsigned char ch;

    for (ch=0; ch<CH_MAX; ch++)
    {
        if (AD_updated_buffer[ch])
        {
            switch (ch)
            {
                case 0:
                    ccr_in_current_mV = AD_IN_mV_buffer[ch];
                    A_IN_mV_was_updated = TRUE;
                    break;
                case 1:
                    V_IN_mV = AD_IN_mV_buffer[ch];
                    break;
                default:
                    break;
            }

            for (ch=0; ch<CH_MAX; ch++)
            {
                AD_updated_buffer[ch] = FALSE;
            }
            break;
        }
    }
}


uchar get_AD_channel(uchar AdSel)
{


    switch (AdSel)
    {
        case 0: // A_IN
            AdSel = 1;
            break;
        case 1: // V_IN
            AdSel = 0;
            break;
        default:
            AdSel = 0;
            break;
    }
    return AdSel;
}


void set_AD_channel_register(unsigned char AdSel)
{
    switch (AdSel)
    {
        case 0:
            CHS4 = 0;
            CHS3 = 0;
            CHS2 = 0;
            CHS1 = 0;
            CHS0 = 0;
            break;
        case 1:
            CHS4 = 0;
            CHS3 = 0;
            CHS2 = 0;
            CHS1 = 0;
            CHS0 = 1;
            break;
        case 2:
            CHS4 = 0;
            CHS3 = 0;
            CHS2 = 0;
            CHS1 = 1;
            CHS0 = 0;
            break;
        case 3:
            CHS4 = 0;
            CHS3 = 0;
            CHS2 = 0;
            CHS1 = 1;
            CHS0 = 1;
            break;
        case 4:
            CHS4 = 0;
            CHS3 = 0;
            CHS2 = 1;
            CHS1 = 0;
            CHS0 = 0;
            break;
        default:
            CHS4 = 0;
            CHS3 = 0;
            CHS2 = 0;
            CHS1 = 0;
            CHS0 = 0;
            break;
    }
}


void check_changing_of_AD_channel()
{
    // AD 채널이 변경 되었다.
    // 변경시 쓰레기 값이 저장되는 문제 때문에 추가 하였다.
    if (AD_channel != bef_ad_channel)
    {
        b_ad_calc_enable = FALSE;
        ad_calc_wait_count = 0;
        bef_ad_channel = AD_channel;
    }

}


void process_AD(void)
{
    if (!is_update_AD()) return;

    update_A_IN_mA__and__V_IN_mV();

    AD_channel = get_AD_channel(AD_channel); // 채널 변경
    set_AD_channel_register(AD_channel); // 채널 설정

    check_changing_of_AD_channel();

    AD_interrupted = FALSE;

    AD_do = 1;
}


void set_input_ad(unsigned int ad)
{
    if (!AD_interrupted)
    {
        in_ad_changed = ad;
        AD_interrupted = TRUE;
    }
}


