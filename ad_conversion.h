
#ifndef	__AD_CONVERSION_H__
#define	__AD_CONVERSION_H__

typedef	unsigned int	bool;
typedef	unsigned int	uint;
typedef	unsigned char	uchar;

#define	TRUE	1
#define	FALSE	0

#define b_conversion_ad		DONE
#define CH_MAX	4 

extern unsigned int ad_updated_mv[CH_MAX];
extern unsigned char b_updated_ad[CH_MAX];
extern unsigned    int   	AD_channel;

extern void process_ad(void);
extern void	init_ad(void);
extern void set_input_ad(unsigned int ad);

#endif

