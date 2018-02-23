
#include <pic18.h>

#include "initial.h"


void	init_port(void)
{
	TRISA=1;
	TRISB=1;
	TRISC=1;
	TRISD=1;
	TRISE=1;
	TRISF=1;
	TRISG=1;

	TRISE=0x0f;
	TRISB=0xff;

  	LATA=0xff;	
  	LATB=0xff;	
  	LATC=0xff;	
  	LATD=0xff;	
  	LATE=0xff;	
  	LATF=0xff;	
  	LATG=0xff;	

	MANUAL_LAMP=0;
	AUTO_LAMP=0;
	USER_LAMP3=0;
	USER_LAMP4=0;


	TRIS_PIN_TEMP_SET_LED_0	= 0;
	PIN_TEMP_SET_LED_0 		= 1; 	// if 1 = led off
	TRIS_PIN_TEMP_SET_LED_1	= 0;
	PIN_TEMP_SET_LED_1 		= 1; 	// if 1 = led off
	TRIS_PIN_TEMP_SET_LED_2	= 0;
	PIN_TEMP_SET_LED_2 		= 1; 	// if 1 = led off
	TRIS_PIN_TEMP_SET_LED_3	= 0;
	PIN_TEMP_SET_LED_3 		= 1; 	// if 1 = led off	

	TRIS_PIN_ERR_ALARM_LED_0	= 0;		
	PIN_ERR_ALARM_LED_0 		= 1;	// LED_E0
	TRIS_PIN_ERR_ALARM_LED_1	= 0;		
	PIN_ERR_ALARM_LED_1 		= 1;	// LED_E0
	TRIS_PIN_ERR_ALARM_LED_2	= 0;		
	PIN_ERR_ALARM_LED_2 		= 1;	// LED_E0
	TRIS_PIN_ERR_ALARM_LED_3	= 0;		
	PIN_ERR_ALARM_LED_3 		= 1;	// LED_E0
	


	TRIS_PIN_HEATER_LED_0		= 0;
	PIN_HEATER_LED_0			= 1;
	TRIS_PIN_HEATER_LED_1		= 0;
	PIN_HEATER_LED_1			= 1;
	TRIS_PIN_HEATER_LED_2		= 0;
	PIN_HEATER_LED_2			= 1;
	TRIS_PIN_HEATER_LED_3		= 0;
	PIN_HEATER_LED_3			= 1;

	TRIS_PIN_HEATER_0_OUT	 	= 0;		
	PIN_HEATER_0_OUT			= 0; 	// if 0 = heater off 
	TRIS_PIN_HEATER_1_OUT	 	= 0;		
	PIN_HEATER_1_OUT			= 0;
	TRIS_PIN_HEATER_2_OUT	 	= 0;		
	PIN_HEATER_2_OUT			= 0;
	TRIS_PIN_HEATER_3_OUT	 	= 0;		
	PIN_HEATER_3_OUT			= 0;

	TRIS_PIN_SW_BCD_1_A 		= 1;	 
	PIN_SW_BCD_1_A				= 0;
	TRIS_PIN_SW_BCD_2_A 		= 1;	 
	PIN_SW_BCD_2_A				= 0;
	TRIS_PIN_SW_BCD_3_A 		= 1;	 
	PIN_SW_BCD_3_A				= 0;
	TRIS_PIN_SW_BCD_4_A 		= 1;	 
	PIN_SW_BCD_4_A				= 0;	

	TRIS_PIN_SW_BCD_1_B 		= 1;	 
	PIN_SW_BCD_1_B				= 0;
	TRIS_PIN_SW_BCD_2_B 		= 1;	 
	PIN_SW_BCD_2_B				= 0;
	TRIS_PIN_SW_BCD_3_B 		= 1;	 
	PIN_SW_BCD_3_B				= 0;
	TRIS_PIN_SW_BCD_4_B 		= 1;	 
	PIN_SW_BCD_4_B				= 0;	

	TRIS_PIN_SW_BCD_1_C 		= 1;	 
	PIN_SW_BCD_1_C				= 0;
	TRIS_PIN_SW_BCD_2_C 		= 1;	 
	PIN_SW_BCD_2_C				= 0;
	TRIS_PIN_SW_BCD_3_C 		= 1;	 
	PIN_SW_BCD_3_C				= 0;
	TRIS_PIN_SW_BCD_4_C 		= 1;	 
	PIN_SW_BCD_4_C				= 0;

	TRIS_PIN_SW_BCD_1_D 		= 1;	 
	PIN_SW_BCD_1_D				= 0;
	TRIS_PIN_SW_BCD_2_D 		= 1;	 
	PIN_SW_BCD_2_D				= 0;
	TRIS_PIN_SW_BCD_3_D 		= 1;	 
	PIN_SW_BCD_3_D				= 0;
	TRIS_PIN_SW_BCD_4_D 		= 1;	 
	PIN_SW_BCD_4_D				= 0;

	TRIS_PIN_RUN_LED	= 0;
	PIN_RUN_LED			= 1;
}


void	init_timer0(void)
{
  TMR0IE=1;
  TMR0IF=0;

  TMR0ON=1;	    // TMR0 on/off
  T08BIT=0;	    // 8/16 bit select    ..(16bit)
  T0CS=0;	    // TMR0 Source Select ..(internal clock)
  T0SE=0;	    // TMR0 Source Edge Select
  PSA=0;	    // Prescaler Assignment ..(enable)
  T0PS2=0;	    // Prescaler..............(1:2)
  T0PS1=1;
  T0PS0=0;
 
  TMR0L=MSEC_L;
  TMR0H=MSEC_H;
} 



