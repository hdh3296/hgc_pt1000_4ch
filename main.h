
#ifndef __MAIN_H__
#define __MAIN_H__

#define __TEMP_1000		1

#define	TRUE	1
#define	FALSE	0


#define ON_LED		0
#define OFF_LED		1

#define	ON_RELAY	1
#define OFF_RELAY	0

// pt1000용 온도표
typedef enum
{
	T11 = 2269, T12 = 2304, T13 = 2339, T14 = 2374, T15 = 2409,
	T16 = 2444, T17 = 2479, T18 = 2514, T19 = 2549, T20 = 2584,
	T21 = 2619, T22 = 2654, T23 = 2689, T24 = 2723, T25 = 2758,
	T26 = 2793, T27 = 2827, T28 = 2862, T29 = 2897, T30 = 2931,
	T31 = 2966, T32 = 3000, T33 = 3035, T34 = 3069, T35 = 3104,
	T36 = 3138, T37 = 3173, T38 = 3207, T39 = 3241, T40 = 3276,
	T41 = 3310, T42 = 3344, T43 = 3378, T44 = 3413, T45 = 3447,
	T46 = 3481, T47 = 3515, T48 = 3549, T49 = 3583, T50 = 3617
} tag_TempValueDef;




#endif

