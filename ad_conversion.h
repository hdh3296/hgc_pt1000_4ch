
#ifndef	__AD_CONVERSION_H__
#define	__AD_CONVERSION_H__

typedef	unsigned int	bool;
typedef	unsigned int	uint;
typedef	unsigned char	uchar;

#define	TRUE	1
#define	FALSE	0

#define AD_do		DONE
#define CH_MAX	4 

extern unsigned int AD_IN_mV_buffer[CH_MAX];
extern unsigned char AD_updated_buffer[CH_MAX];
extern unsigned    int   	AD_channel;

extern void process_AD(void);
extern void	InitAD(void);
extern void set_input_ad(unsigned int ad);

#endif

