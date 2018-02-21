
#ifndef	__INITIAL_H__
#define	__INITIAL_H__


#define  MANUAL_LAMP	LATG1		//user lamp1
#define  AUTO_LAMP		LATG0		//user lamp2
#define  USER_LAMP3 	LATG2
#define  USER_LAMP4 	LATG3

#define  MSEC_H	0xfc
#define  MSEC_L  0x18





extern void PortInit(void);
extern void	Timer0Init(void);

#endif

