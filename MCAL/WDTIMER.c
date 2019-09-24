/*
 * WDTIMER.c
 *
 *  Created on: Sep 13, 2019
 *      Author: mahmo
 */
#include "../STD_Types.h"
#include "../macros.h"
#include "WDTIMER.h"

#define WDTCR_REG	*((volatile u8*) 0x41)

#define WDP0 	0
#define WDP1 	1
#define WDP2 	2
#define WDE 	3
#define WDTOE 	4


void WDT_vidInit(u8 u8Precscaler)
{
	/*enable WatchDog Timer */
	set_bit(WDTCR_REG,WDE);
	/*switch for time period */
	switch(u8Precscaler)
	{
		/* 16k cycles  */
		case WDP_16K :
			clr_bit(WDTCR_REG,WDP0);
			clr_bit(WDTCR_REG,WDP1);
			clr_bit(WDTCR_REG,WDP2);
			break;
		/* 32k cycles  */
		case WDP_32K :
			set_bit(WDTCR_REG,WDP0);
			clr_bit(WDTCR_REG,WDP1);
			clr_bit(WDTCR_REG,WDP2);
			break;
		/* 64k cycles  */
		case WDP_64K :
			clr_bit(WDTCR_REG,WDP0);
			set_bit(WDTCR_REG,WDP1);
			clr_bit(WDTCR_REG,WDP2);
			break;
		/* 128k cycles  */
		case WDP_128K :
			set_bit(WDTCR_REG,WDP0);
			set_bit(WDTCR_REG,WDP1);
			clr_bit(WDTCR_REG,WDP2);
			break;
		/* 256k cycles  */
		case WDP_256K :
			clr_bit(WDTCR_REG,WDP0);
			clr_bit(WDTCR_REG,WDP1);
			set_bit(WDTCR_REG,WDP2);
			break;
		/* 512k cycles  */
		case WDP_512K :
			set_bit(WDTCR_REG,WDP0);
			clr_bit(WDTCR_REG,WDP1);
			set_bit(WDTCR_REG,WDP2);
			break;
		/* 1024k cycles  */
		case WDP_1024K :
			clr_bit(WDTCR_REG,WDP0);
			set_bit(WDTCR_REG,WDP1);
			set_bit(WDTCR_REG,WDP2);
			break;
		/* 2048k cycles  */
		case WDP_2048K :
			set_bit(WDTCR_REG,WDP0);
			set_bit(WDTCR_REG,WDP1);
			set_bit(WDTCR_REG,WDP2);
			break;

	}
}


void WDT_vidDisable()
{
	/* Write logical one to WDTOE & WDE*/
	WDTCR_REG=(1<<WDTOE)| (1<<WDE);
	/*Turn off WDT */
	WDTCR_REG=0x00;

}
