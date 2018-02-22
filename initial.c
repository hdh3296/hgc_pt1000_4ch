
#include <pic18.h>

#include "initial.h"


void	PortInit(void)
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


	TRIS_PIN_TEMP_SET_LED	= 0;
	PIN_TEMP_SET_LED 		= 1; 	// if 1 = led off

	TRIS_PIN_ERR_ALARM_LED	= 0;		
	PIN_ERR_ALARM_LED 		= 1;	// LED_E0

	TRIS_PIN_HEATER_LED		= 0;
	PIN_HEATER_LED			= 1;
		

	TRIS_PIN_HEATER_OUT	 	= 0;		
	PIN_HEATER_OUT			= 0; 	// if 0 = heater off 

	TRIS_PIN_SW_BCD_1 		= 1;	 
	PIN_SW_BCD_1			= 0;
	TRIS_PIN_SW_BCD_2 		= 1;	 
	PIN_SW_BCD_2			= 0;
	TRIS_PIN_SW_BCD_3 		= 1;	 
	PIN_SW_BCD_3			= 0;
	TRIS_PIN_SW_BCD_4 		= 1;	 
	PIN_SW_BCD_4			= 0;	
	 	
	
}


void	Timer0Init(void)
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



