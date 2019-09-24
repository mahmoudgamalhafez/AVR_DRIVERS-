/*
 * E_INTERRUPT.c
 *
 *  Created on: Sep 3, 2019
 *      Author: mahmo
 */

#include "../STD_Types.h"
#include "../macros.h"
#include "E_INTERRUPT.h"
/*REGISTERS */
#define SREG_REG		*((volatile u8*) 0x5F) //GLOBAL INTRRUPT
#define	MCUSR_REG		*((volatile u8*) 0x55) //INTRRUPT SENCE CONTROL FOR INT0&1 'MCUCR'
#define MCUCSR_REG		*((volatile u8*) 0x54) //INTRRUPT SENCE CONTROL FOR INT2   'MCUCSR'
#define GICR_REG		*((volatile u8*) 0x5B) //INTRRUPT ENABLE REGISTER	'GICR'

/*SREG */
#define G_INT_ENABLE	7
/* GICR */
#define INT1    7
#define INT0    6
#define INT2    5
/* MCUCR */
#define ISC11   3
#define ISC10   2
#define ISC01   1
#define ISC00   0
/* MCUCSR */
#define ISC2    6


/*Interrupt Call back */
void (* ptr_INT0)(void);
void (* ptr_INT1)(void);
void (* ptr_INT2)(void);

/* External Interrupt Request 0 */
#define vect_INT0			1
/* External Interrupt Request 1 */
#define vect_INT1			2
/* External Interrupt Request 2 */
#define vect_INT2			3

void EINTERRUPT_vidGEnable()
{
	set_bit(SREG_REG,G_INT_ENABLE); //Enable Global Interrupt
}

void EINTERRUPT_vidGDisable()
{
	clr_bit(SREG_REG,G_INT_ENABLE); //disable Global Interrupt
}
/*
 * Enable INT0
 * */
void EINTERRUPT_vidENINT0(u8 Triggering)
{
	//sei();turn on Global interrupt bit
	//cli(); turn off Global interrupt bit
	set_bit(GICR_REG,INT0);//set periphiral interrupt
	switch(Triggering){
		case LOW:
			clr_bit(MCUSR_REG,ISC00);
			clr_bit(MCUSR_REG,ISC01);
			break;
		case LOGICAL_CHANGE:
			set_bit(MCUSR_REG,ISC00);
			clr_bit(MCUSR_REG,ISC01);
			break;
		case FALLING_EDGE:
			set_bit(MCUSR_REG,ISC01);
			clr_bit(MCUSR_REG,ISC00);
			break;
		case RISING_EDGE:
			set_bit(MCUSR_REG,ISC01);
			set_bit(MCUSR_REG,ISC00);
			break;

	}
}
/*
 * Enable INT1
 * */
void EINTERRUPT_vidENINT1(u8 Triggering)
{
	set_bit(GICR_REG,INT1);//set periphiral interrupt
	switch(Triggering){
		case LOW:
			clr_bit(MCUSR_REG,ISC10);
			clr_bit(MCUSR_REG,ISC11);
			break;
		case LOGICAL_CHANGE:
			set_bit(MCUSR_REG,ISC10);
			clr_bit(MCUSR_REG,ISC11);
			break;
		case FALLING_EDGE:
			set_bit(MCUSR_REG,ISC10);
			clr_bit(MCUSR_REG,ISC11);
			break;
		case RISING_EDGE:
			set_bit(MCUSR_REG,ISC11);
			set_bit(MCUSR_REG,ISC10);
			break;

	}
}
/*
 * Enable INT2
 * */
void EINTERRUPT_vidENINT2(u8 Triggering)
{
	set_bit(GICR_REG,INT2);//set periphiral interrupt
	switch(Triggering){
	case FALLING_EDGE:
		clr_bit(MCUCSR_REG,ISC2);
		break;
	case RISING_EDGE:
		set_bit(MCUCSR_REG,ISC2);
		break;
	}
}
/* */
void INT0_CallBack(void (*pfn) (void))
{
	ptr_INT0=pfn;
}
void INT1_CallBack(void (*pfn) (void))
{
	ptr_INT1=pfn;
}
void INT2_CallBack(void (*pfn) (void))
{
	ptr_INT2=pfn;
}


ISR(vect_INT0)
{
	ptr_INT0();
}
ISR(vect_INT1)
{
	ptr_INT1();
}
ISR(vect_INT2)
{
	ptr_INT2();
}
