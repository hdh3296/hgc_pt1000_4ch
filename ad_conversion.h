
#ifndef	__AD_CONVERSION_H__
#define	__AD_CONVERSION_H__

typedef	unsigned int	bool;
typedef	unsigned int	uint;
typedef	unsigned char	uchar;

#define	TRUE	1
#define	FALSE	0

#define AD_do		DONE


extern void process_AD(void);
extern void	InitAD(void);
extern void set_input_ad(unsigned int ad);

#endif

