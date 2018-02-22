
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


#define PIN_TEMP_SET_LED	 	RD4	// LED_S0 (set led)
#define TRIS_PIN_TEMP_SET_LED	TRISD4 

#define PIN_HEATER_OUT			RC0 	// SSR_0
#define TRIS_PIN_HEATER_OUT	 	TRISC0 

#define PIN_ERR_ALARM_LED 		RD0		// LED_E0
#define TRIS_PIN_ERR_ALARM_LED 	TRISD0

#define PIN_HEATER_LED			RC4 // ?àÌÑ∞ ?ÅÌÉú LED 
#define TRIS_PIN_HEATER_LED		TRISC4



#define PIN_SW_BCD_1			RB0x // SW BCD 1
#define TRIS_PIN_SW_BCD_1 		TRISB0 

#define PIN_SW_BCD_2	 		RB1x	// SW BCD 2
#define TRIS_PIN_SW_BCD_2	 	TRISB1 	

#define PIN_SW_BCD_3			RB2	// SW BCD 3 
#define TRIS_PIN_SW_BCD_3 		TRISB2 	 

#define PIN_SW_BCD_4			RB3	// SW BCD 4
#define TRIS_PIN_SW_BCD_4 		TRISB3 


extern void PortInit(void);
extern void	Timer0Init(void);

#endif

