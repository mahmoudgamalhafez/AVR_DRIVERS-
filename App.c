/*
 * App.c
 *
 *  Created on: Aug 23, 2019
 *      Author: elProf
 */
//#define F_CPU 80000000ul
#include "STD_Types.h"
#include "macros.h"
#include "MCAL/DIO.h"
#include "HAL/LCD.h"
#include "util/delay.h"
#include "HAL/Keypad.h"
#include "HAL/BUZZER.h"
//#include "Calculator.h"
//#include <stdlib.h>
//#include <avr/io.h>
//#include <avr/interrupt.h>




/*	Calculator  */
int main()
{
/*	u16 i;
	DIO_vidSetPortDir(PORTD,0xFF);
	for(i=0;i<512;i++){
		DIO_vidSetPortValue(PORTD,0x01);
		_delay_ms(5);
		DIO_vidSetPortValue(PORTD,0x02);
		_delay_ms(5);
		DIO_vidSetPortValue(PORTD,0x04);
		_delay_ms(5);
		DIO_vidSetPortValue(PORTD,0x08);
		_delay_ms(5);
	}
*/
	/*set INT0 falling Edge  */
//	set_bit(MCUCR,ISC01);
	/* Enable INT0*/
//	set_bit(GICR,INT0);
	/*Enable Global Int */
//	set_bit(SREG,SREG_T);
	BUZZER_vidInit();

	while(1)
	{
		BUZZER_vidON();
		_delay_ms(1);
		BUZZER_vidOFF();
		_delay_ms(1);
	}
}
/*
ISR(INT0_vect)
{
	PORTA=0x01;
}*/
