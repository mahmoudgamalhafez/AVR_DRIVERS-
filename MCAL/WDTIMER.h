/*
 * WDTIMER.h
 *
 *  Created on: Sep 13, 2019
 *      Author: mahmo
 */

#ifndef MCAL_WDTIMER_H_
#define MCAL_WDTIMER_H_

#define WDP_16K		0
#define WDP_32K		1
#define WDP_64K		2
#define WDP_128K	3
#define WDP_256K	4
#define WDP_512K	5
#define WDP_1024K	6
#define WDP_2048K	7

void WDT_vidInit(u8 u8Precscaler);
void WDT_vidDisable();

#define wdt_reset()	asm("WDR")




#endif /* MCAL_WDTIMER_H_ */
