
#ifndef	__INITIAL_H__
#define	__INITIAL_H__

extern volatile bit RB0x                @ ((unsigned)&PORTB*8)+0;
extern volatile bit RB1x                @ ((unsigned)&PORTB*8)+1;



#define  MANUAL_LAMP	LATG1		//user lamp1
#define  AUTO_LAMP		LATG0		//user lamp2
#define  USER_LAMP3 	LATG2
#define  USER_LAMP4 	LATG3

#define  MSEC_H	0xfc
#define  MSEC_L  0x18

// 4ch set led
#define PIN_TEMP_SET_LED_0	 	RD4	// LED_S0 (set led)
#define TRIS_PIN_TEMP_SET_LED_0	TRISD4 
#define PIN_TEMP_SET_LED_1	 	RD5	// LED_S0 (set led)
#define TRIS_PIN_TEMP_SET_LED_1	TRISD5 
#define PIN_TEMP_SET_LED_2	 	RD6	// LED_S0 (set led)
#define TRIS_PIN_TEMP_SET_LED_2	TRISD6 
#define PIN_TEMP_SET_LED_3	 	RD7	// LED_S0 (set led)
#define TRIS_PIN_TEMP_SET_LED_3	TRISD7 


// 4ch heater relay out
#define PIN_HEATER_0_OUT			RC0 	// SSR_0
#define TRIS_PIN_HEATER_0_OUT	 	TRISC0 
#define PIN_HEATER_1_OUT			RC1 	// SSR_0
#define TRIS_PIN_HEATER_1_OUT	 	TRISC1 
#define PIN_HEATER_2_OUT			RC2 	// SSR_0
#define TRIS_PIN_HEATER_2_OUT	 	TRISC2 
#define PIN_HEATER_3_OUT			RC3 	// SSR_0
#define TRIS_PIN_HEATER_3_OUT	 	TRISC3 

// 4ch heater led 
#define PIN_HEATER_LED_0			RC4 
#define TRIS_PIN_HEATER_LED_0		TRISC4
#define PIN_HEATER_LED_1			RC5 
#define TRIS_PIN_HEATER_LED_1		TRISC5
#define PIN_HEATER_LED_2			RC6 
#define TRIS_PIN_HEATER_LED_2		TRISC6
#define PIN_HEATER_LED_3			RC7 
#define TRIS_PIN_HEATER_LED_3		TRISC7




// 4ch err led 
#define PIN_ERR_ALARM_LED_0 		RD0		// LED_E0
#define TRIS_PIN_ERR_ALARM_LED_0 	TRISD0
#define PIN_ERR_ALARM_LED_1 		RD1		// LED_E0
#define TRIS_PIN_ERR_ALARM_LED_1 	TRISD1
#define PIN_ERR_ALARM_LED_2 		RD2		// LED_E0
#define TRIS_PIN_ERR_ALARM_LED_2 	TRISD2
#define PIN_ERR_ALARM_LED_3 		RD3		// LED_E0
#define TRIS_PIN_ERR_ALARM_LED_3 	TRISD3




// 4ch bcd 
#define PIN_SW_BCD_1_A			RB0x 
#define TRIS_PIN_SW_BCD_1_A 	TRISB0 
#define PIN_SW_BCD_2_A	 		RB1x
#define TRIS_PIN_SW_BCD_2_A	 	TRISB1 
#define PIN_SW_BCD_3_A			RB2	
#define TRIS_PIN_SW_BCD_3_A 	TRISB2 
#define PIN_SW_BCD_4_A			RB3	
#define TRIS_PIN_SW_BCD_4_A 	TRISB3 

#define PIN_SW_BCD_1_B			RE4 
#define TRIS_PIN_SW_BCD_1_B 	TRISE4 
#define PIN_SW_BCD_2_B	 		RE5
#define TRIS_PIN_SW_BCD_2_B	 	TRISE5 
#define PIN_SW_BCD_3_B			RE6	
#define TRIS_PIN_SW_BCD_3_B 	TRISE6 
#define PIN_SW_BCD_4_B			RE7	
#define TRIS_PIN_SW_BCD_4_B 	TRISE7 

#define PIN_SW_BCD_1_C			RF0 
#define TRIS_PIN_SW_BCD_1_C 	TRISF0 
#define PIN_SW_BCD_2_C	 		RF1
#define TRIS_PIN_SW_BCD_2_C	 	TRISF1 
#define PIN_SW_BCD_3_C			RF2
#define TRIS_PIN_SW_BCD_3_C 	TRISF2 
#define PIN_SW_BCD_4_C			RF3	
#define TRIS_PIN_SW_BCD_4_C 	TRISF3 

#define PIN_SW_BCD_1_D			RF4 
#define TRIS_PIN_SW_BCD_1_D 	TRISF4 
#define PIN_SW_BCD_2_D	 		RF5
#define TRIS_PIN_SW_BCD_2_D	 	TRISF5 
#define PIN_SW_BCD_3_D			RF6	
#define TRIS_PIN_SW_BCD_3_D 	TRISF6 
#define PIN_SW_BCD_4_D			RF7	
#define TRIS_PIN_SW_BCD_4_D 	TRISF7 





extern void PortInit(void);
extern void	Timer0Init(void);

#endif

