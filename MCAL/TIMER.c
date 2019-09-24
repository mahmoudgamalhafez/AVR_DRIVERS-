/*
 * TIMER.c
 *
 *  Created on: Sep 7, 2019
 *      Author: mahmo
 */
#include "../STD_Types.h"
#include "../macros.h"
#include "TIMER.h"


/*Timer 0_1_2 Flag REG */
#define REG_TIMSK	*((volatile u8*) 0x59) 		 //Timer/Counter Interrupt mask REG
#define TIFR_REG  	*((volatile u8*) 0x58)	    //Timer Counter Interrupt Flag Reg
/* 				Timer 0				*/
#define REG_TCNT0 	*((volatile u8*) 0x52)    //Timer/Counter0 REG
#define REG_TCCR0 	*((volatile u8*) 0x53)   //Timer/Counter0 Control REG
#define REG_OCR0	*((volatile u8*) 0x5C)  //Timer/Counter0 OUTPUT Compare REG

/*Timer_Counter0  Interrupt Enable*/
#define B0_TOIE0  	0     //Timer/Counter0 Overflow Interrupt Enable
#define B0_OCIE0	1  	 //Timer/Counter0	Output compare match Enable
/*Timer0 Flags */
#define B0_TOV0		0  //Timer0 overflow flag Bit
#define B0_OCF0		1 //Timer0 output compare flag

/*Timer0 Control BITS */
  /* Prescaling */
#define B0_CS00		0
#define B0_CS01		1
#define B0_CS02		2

 /*Timer_Counter0 Modes */
#define B0_WGM00		6
#define B0_WGM01		3

 /* Wave Generator*/
#define B0_FOC0 		7  //Force compare match
#define B0_COM00		4 //Outout compare match
#define B0_COM01		5//Output compare match

/* 				TIMER 1  		*/
#define REG_TCNT1	*((volatile u16*) 0x4C)    //TIMER/COUNTER1 REG
#define REG_TCCR1	*((volatile u16*) 0x4E)   //TIMER/COUNTER1 CONTROL REG
#define REG_OCR1A	*((volatile u16*) 0x4A)  //TIMER/COUNTER1 COMPARE REG CHANNEL A
#define REG_OCR1B	*((volatile u16*) 0x48) //TIMER/COUNTER1 COMPARE REG CHANNEL B
#define REG_ICR1	*((volatile u16*) 0x46)//TIMER/COUNTER1 INPUT CAPTURE REG

/*Timer_Counter1  Interrupt Enable*/
#define B1_TOIE1  	2   	   //Timer/Counter1 Overflow Interrupt Enable
#define B1_OCIE1B	3  		  //Timer/Counter1	Output compare match Enable channel B
#define B1_OCIE1A	4		 //Timer/Counter1	Output compare match Enable channel B
#define B1_TICIE1	5		//Timer/Counter1 Input capture Enable

/*Timer Flags */
#define B1_TOV1		2    //Timer1 overflow flag
#define B1_OCF1B	3   //Timer1 output compare flag B
#define B1_OCF1A	4  //Timer1 output compare flag A
#define B1_ICF1		5 //Input capture flag

/*Timer1 Control BITS */
	/*Prescaling */
#define B1_CS10		0
#define B1_CS11		1
#define B1_CS12		2

 /*Timer_Counter1 Modes */
#define B1_WGM10	8
#define B1_WGM11	9
#define B1_WGM12	3
#define B1_WGM13	4

/* Wave Generator*/
#define B1_FOC1B 	10
#define B1_FOC1A 	11
#define B1_COM1B0	12
#define B1_COM1B1	13
#define B1_COM1A0	14
#define B1_COM1A1	15

/*Input Capture */
#define B1_ICNC1	7
#define B1_ICES1	6


/*Call Back Pointer */
void (*Timer0_OVF)(void);
void (*Timer0_COMP)(void);
void (*Timer1_OVF)(void);
void (*Timer1_COMPA)(void);
void (*Timer1_COMPB)(void);
void (*Timer1_CAPT)(void);

/*Timer/Counter0 Interrupt vector */

#define vect_TimerOVF0		11    // Overflow
#define vect_TimerCOMP0		10 	 //Compare match

/*Timer/Counter0 Interrupt vector */
#define vect_TimerOVF1		9  // Overflow
#define vect_TimerCOMP1B	8 //compare match B channel
#define vect_TimerCOMP1A	7//compare match A channel


/*							TIMER0 FUN 									*/


extern void TIMER0_vidOVEnable(){
	/*Enable Timer/Counter0 Overflow Interrupt  */
		set_bit(REG_TIMSK,B0_TOIE0);
}
extern void TIMER0_vidCMEnable(){
	/*Enable Timer/Counter0 Interrupt Compare match */
		set_bit(REG_TIMSK,B0_OCIE0);
}
/*
 * TIMER0_vidInit(u8 Prescaling,u8 Mode):
 * 			Enable TimerCounter0 and set Mode and prescaling
 *  */
extern void TIMER0_vidInit(u8 u8Mode,u8 u8Prescaling,u8 u8Wave)
{

	/*switch for mode */
	switch(u8Mode){
		/*case Normal mode*/
		case MODE_NORMAL:
			clr_bit(REG_TCCR0,B0_WGM00);
			clr_bit(REG_TCCR0,B0_WGM01);
			break;
		case MODE_CTC:
			clr_bit(REG_TCCR0,B0_WGM00);
			set_bit(REG_TCCR0,B0_WGM01);
			break;
		case MODE_PhaseCorrect:
			set_bit(REG_TCCR0,B0_WGM00);
			clr_bit(REG_TCCR0,B0_WGM01);
			break;
		case MODE_FASTPWM:
			set_bit(REG_TCCR0,B0_WGM00);
			set_bit(REG_TCCR0,B0_WGM01);
			break;
	}
	/* switch For prescaling*/
	switch(u8Prescaling)
	{
		/*case Timer off */
		case Prescaling_NOCLOCK:
			clr_bit(REG_TCCR0,B0_CS00);
			clr_bit(REG_TCCR0,B0_CS01);
			clr_bit(REG_TCCR0,B0_CS02);
			break;
		/*case No Prescaling */
		case Prescaling_NOPRESCALING:
			set_bit(REG_TCCR0,B0_CS00);
			clr_bit(REG_TCCR0,B0_CS01);
			clr_bit(REG_TCCR0,B0_CS02);
			break;
		/*case Prescaling/8 */
		case Prescaling_8:
			clr_bit(REG_TCCR0,B0_CS00);
			set_bit(REG_TCCR0,B0_CS01);
			clr_bit(REG_TCCR0,B0_CS02);
			break;
		/*case Prescaling/64 */
		case Prescaling_64:
			set_bit(REG_TCCR0,B0_CS00);
			set_bit(REG_TCCR0,B0_CS01);
			clr_bit(REG_TCCR0,B0_CS02);
			break;
		/*case Prescaling/256 */
		case Prescaling_256:
			clr_bit(REG_TCCR0,B0_CS00);
			clr_bit(REG_TCCR0,B0_CS01);
			set_bit(REG_TCCR0,B0_CS02);
			break;
		/*case Prescaling/1024 */
		case Prescaling_1024:
			set_bit(REG_TCCR0,B0_CS00);
			clr_bit(REG_TCCR0,B0_CS01);
			set_bit(REG_TCCR0,B0_CS02);
			break;
		/*case Prescaling External Falling Edge */
		case Prescaling_EXTFALLING:
			clr_bit(REG_TCCR0,B0_CS00);
			set_bit(REG_TCCR0,B0_CS01);
			set_bit(REG_TCCR0,B0_CS02);
			break;
		/*case Prescaling External Rising Edge  */
		case Prescaling_EXTRISING:
			set_bit(REG_TCCR0,B0_CS00);
			set_bit(REG_TCCR0,B0_CS01);
			set_bit(REG_TCCR0,B0_CS02);
			break;
	}
	/*if not PWM  in case Normal or CTC */
	if(!get_bit(REG_TCCR0,B0_WGM00)){
		/*Switch for Wave Generaton */
		switch(u8Wave)
		{
			/*in case OC0 disconnected */
			case WAVE_NONE:
				clr_bit(REG_TCCR0,B0_COM00);
				clr_bit(REG_TCCR0,B0_COM01);
				break;
			/*Toggle on compare Match */
			case WAVE0_TOGONCOMP:
				set_bit(REG_TCCR0,B0_COM00);
				clr_bit(REG_TCCR0,B0_COM01);
				break;
			/*set on compare match*/
			case WAVE0_SETONCOMP:
				clr_bit(REG_TCCR0,B0_COM00);
				set_bit(REG_TCCR0,B0_COM01);
				break;
			/* clear on compare match*/
			case WAVE0_CLRONCOMP:
				set_bit(REG_TCCR0,B0_COM00);
				set_bit(REG_TCCR0,B0_COM01);
				break;
		}
	}
	/* in case PWM GENERATION*/
	else if (u8Mode==MODE_FASTPWM|| u8Mode==MODE_PhaseCorrect) {
			switch(u8Wave)
			{
			/*in case OC0 disconnected */
				case WAVE_NONE:
					clr_bit(REG_TCCR0,B0_COM00);
					clr_bit(REG_TCCR0,B0_COM01);
					break;
				case PWM0_Inverted:
					clr_bit(REG_TCCR0,B0_COM00);
					set_bit(REG_TCCR0,B0_COM01);
					break;
				case PWM0_NonInverted:
					set_bit(REG_TCCR0,B0_COM00);
					set_bit(REG_TCCR0,B0_COM01);
			 }
	}
}

/*
 *
 * */

extern void TIMER0_vidOVDisable()
{
	/*Disable Timer/counter0 Overflow interrupt*/
	clr_bit(REG_TIMSK,B0_TOIE0);
}
extern void TIMER0_vidCMDisable()
{
	/*Disable Timer/counter0 compare match interrupt*/
	clr_bit(REG_TIMSK,B0_OCIE0);
}

/*
 * TIMER0_vidSetREG(u8 u8Value):-
 * 			set TCNT0 Value to start count with
 * */
extern void TIMER0_vidSetTCNT0(u8 u8Value)
{
	REG_TCNT0=u8Value;
}

extern u8 TIMER0_u8GetTCNT0()
{
	return REG_TCNT0;
}
/* TIMER0_vidSetOCREG(u8 u8Value):-
 * 			set OCR0 Register for compare match mode
 * */
extern void TIMER0_vidSetOCR0(u8 u8Value)
{
	REG_OCR0=u8Value;
}

/*					TIMER1 FUN								 */

/* Enable Timer/Counter1 Interrupt overflow */
extern void TIMER1_vidOVEnable()
{

	set_bit(REG_TIMSK,B1_TOIE1);
}
/* Enable Timer/Counter Interrupt Compare match channel A */
extern void TIMER1_vidCMEnable()
{
	set_bit(REG_TIMSK,B1_OCIE1A);
}
/*
 * TIMER1_vidInit(u8 Prescaling,u8 Mode):
 * 			Enable TimerCounter1 and set Mode and prescaling
 *  */
extern void TIMER1_vidInit(u8 u8Mode,u8 u8Prescaling,u8 u8Wave)
{
	/* switch For prescaling*/
	switch(u8Prescaling)
	{
		/*case Timer off */
		case Prescaling_NOCLOCK:
			clr_bit(REG_TCCR1,B1_CS10);
			clr_bit(REG_TCCR1,B1_CS11);
			clr_bit(REG_TCCR1,B1_CS12);
			break;
		/*case No Prescaling */
		case Prescaling_NOPRESCALING:
			set_bit(REG_TCCR1,B1_CS10);
			clr_bit(REG_TCCR1,B1_CS11);
			clr_bit(REG_TCCR1,B1_CS12);
			break;
		/*case Prescaling/8 */
		case Prescaling_8:
			clr_bit(REG_TCCR1,B1_CS10);
			set_bit(REG_TCCR1,B1_CS11);
			clr_bit(REG_TCCR1,B1_CS12);
			break;
		/*case Prescaling/64 */
		case Prescaling_64:
			set_bit(REG_TCCR1,B1_CS10);
			set_bit(REG_TCCR1,B1_CS11);
			clr_bit(REG_TCCR1,B1_CS12);
			break;
		/*case Prescaling/256 */
		case Prescaling_256:
			clr_bit(REG_TCCR1,B1_CS10);
			clr_bit(REG_TCCR1,B1_CS11);
			set_bit(REG_TCCR1,B1_CS12);
			break;
		/*case Prescaling/1024 */
		case Prescaling_1024:
			set_bit(REG_TCCR1,B1_CS10);
			clr_bit(REG_TCCR1,B1_CS11);
			set_bit(REG_TCCR1,B1_CS12);
			break;
		/*case Prescaling External Falling Edge */
		case Prescaling_EXTFALLING:
			clr_bit(REG_TCCR1,B1_CS10);
			set_bit(REG_TCCR1,B1_CS11);
			set_bit(REG_TCCR1,B1_CS12);
			break;
		/*case Prescaling External Rising Edge  */
		case Prescaling_EXTRISING:
			set_bit(REG_TCCR1,B1_CS10);
			set_bit(REG_TCCR1,B1_CS11);
			set_bit(REG_TCCR1,B1_CS12);
			break;
	}
	/* switch For Modes*/
	switch(u8Mode)
	{
		case MODE_NORMAL:
			clr_bit(REG_TCCR1,B1_WGM10);
			clr_bit(REG_TCCR1,B1_WGM11);
			clr_bit(REG_TCCR1,B1_WGM12);
			clr_bit(REG_TCCR1,B1_WGM13);
			break;
		/*Top OCR1A */
		case MODE_CTC:
			clr_bit(REG_TCCR1,B1_WGM10);
			clr_bit(REG_TCCR1,B1_WGM11);
			set_bit(REG_TCCR1,B1_WGM12);
			clr_bit(REG_TCCR1,B1_WGM13);
			break;
		case MODE_PWM8:
			set_bit(REG_TCCR1,B1_WGM10);
			clr_bit(REG_TCCR1,B1_WGM11);
			clr_bit(REG_TCCR1,B1_WGM12);
			clr_bit(REG_TCCR1,B1_WGM13);
			break;
		case MODE_PWM9:
			clr_bit(REG_TCCR1,B1_WGM10);
			set_bit(REG_TCCR1,B1_WGM11);
			clr_bit(REG_TCCR1,B1_WGM12);
			clr_bit(REG_TCCR1,B1_WGM13);
			break;
		case MODE_PWM10:
			set_bit(REG_TCCR1,B1_WGM10);
			set_bit(REG_TCCR1,B1_WGM11);
			clr_bit(REG_TCCR1,B1_WGM12);
			clr_bit(REG_TCCR1,B1_WGM13);
			break;
		case MODE_FASTPWM8:
			set_bit(REG_TCCR1,B1_WGM10);
			clr_bit(REG_TCCR1,B1_WGM11);
			set_bit(REG_TCCR1,B1_WGM12);
			clr_bit(REG_TCCR1,B1_WGM13);
			break;
		case MODE_FASTPWM9:
			clr_bit(REG_TCCR1,B1_WGM10);
			set_bit(REG_TCCR1,B1_WGM11);
			set_bit(REG_TCCR1,B1_WGM12);
			clr_bit(REG_TCCR1,B1_WGM13);
			break;
		case MODE_FASTPWM10:
			set_bit(REG_TCCR1,B1_WGM10);
			set_bit(REG_TCCR1,B1_WGM11);
			set_bit(REG_TCCR1,B1_WGM12);
			clr_bit(REG_TCCR1,B1_WGM13);
			break;
		case MODE_PPF_ICR1:
			clr_bit(REG_TCCR1,B1_WGM10);
			clr_bit(REG_TCCR1,B1_WGM11);
			clr_bit(REG_TCCR1,B1_WGM12);
			set_bit(REG_TCCR1,B1_WGM13);
			break;
		case MODE_PPF_OCR1A:
			set_bit(REG_TCCR1,B1_WGM10);
			clr_bit(REG_TCCR1,B1_WGM11);
			clr_bit(REG_TCCR1,B1_WGM12);
			set_bit(REG_TCCR1,B1_WGM13);
			break;
		case MODE_PP_ICR1:
			clr_bit(REG_TCCR1,B1_WGM10);
			set_bit(REG_TCCR1,B1_WGM11);
			clr_bit(REG_TCCR1,B1_WGM12);
			set_bit(REG_TCCR1,B1_WGM13);
			break;
		case MODE_PP_OCR1A:
			set_bit(REG_TCCR1,B1_WGM10);
			set_bit(REG_TCCR1,B1_WGM11);
			clr_bit(REG_TCCR1,B1_WGM12);
			set_bit(REG_TCCR1,B1_WGM13);
			break;
		/*Top ICR1 */
		case MODE_CTC_ICR1:
			clr_bit(REG_TCCR1,B1_WGM10);
			clr_bit(REG_TCCR1,B1_WGM11);
			set_bit(REG_TCCR1,B1_WGM12);
			set_bit(REG_TCCR1,B1_WGM13);
			break;
		case MODE_FASTPWM_ICR1A:
			clr_bit(REG_TCCR1,B1_WGM10);
			set_bit(REG_TCCR1,B1_WGM11);
			set_bit(REG_TCCR1,B1_WGM12);
			set_bit(REG_TCCR1,B1_WGM13);
			/*   */
			//clr_bit(REG_TCCR1,14);
			//set_bit(REG_TCCR1,15);
			break;
		case MODE_FASTPWM_OCR1A:
			set_bit(REG_TCCR1,B1_WGM10);
			set_bit(REG_TCCR1,B1_WGM11);
			set_bit(REG_TCCR1,B1_WGM12);
			set_bit(REG_TCCR1,B1_WGM13);
			break;


	}
	/*in case Wave Generation CTC OR Normal Mode  */
	if(u8Mode==MODE_CTC || u8Mode==MODE_NORMAL || u8Mode==MODE_CTC_ICR1)
	{
		switch(u8Wave)
		{
		/*OC1A && OC1B disconnected */
			case WAVE_NONE:
				clr_bit(REG_TCCR1,B1_COM1A0);
				clr_bit(REG_TCCR1,B1_COM1A1);
				clr_bit(REG_TCCR1,B1_COM1B0);
				clr_bit(REG_TCCR1,B1_COM1B0);
				break;
			/*		CHANNEL A			 */
			case WAVE1A_TOGONCOMP:
				set_bit(REG_TCCR1,B1_COM1A0);
				clr_bit(REG_TCCR1,B1_COM1A1);
				break;
			case WAVE1A_CLRONCOMP:
				clr_bit(REG_TCCR1,B1_COM1A0);
				set_bit(REG_TCCR1,B1_COM1A1);
				break;
			case WAVE1A_SETONCOMP:
				set_bit(REG_TCCR1,B1_COM1A0);
				set_bit(REG_TCCR1,B1_COM1A1);
				break;
			/*		CHANNEL B		 */
			case WAVE1B_TOGONCOMP:
				set_bit(REG_TCCR1,B1_COM1B0);
				clr_bit(REG_TCCR1,B1_COM1B1);
				break;
			case WAVE1B_CLRONCOMP:
				clr_bit(REG_TCCR1,B1_COM1B0);
				set_bit(REG_TCCR1,B1_COM1B1);
				break;
			case WAVE1B_SETONCOMP:
				set_bit(REG_TCCR1,B1_COM1B0);
				set_bit(REG_TCCR1,B1_COM1B1);
				break;
		}
	}
	else if(u8Mode==MODE_FASTPWM_ICR1A||u8Mode==MODE_FASTPWM_OCR1A||u8Mode)
	{

		switch(u8Wave)
		{
			case WAVE_NONE:
				clr_bit(REG_TCCR1,B1_COM1A0);
				clr_bit(REG_TCCR1,B1_COM1A1);
				clr_bit(REG_TCCR1,B1_COM1B0);
				clr_bit(REG_TCCR1,B1_COM1B0);
			    break;
			case PWM1A_NonInverted:
				clr_bit(REG_TCCR1,B1_COM1A0);
				set_bit(REG_TCCR1,B1_COM1A1);
				break;
			case PWM1A_Inverted:
				set_bit(REG_TCCR1,B1_COM1A0);
				set_bit(REG_TCCR1,B1_COM1A1);
				break;
			case PWM1B_NonInverted:
				clr_bit(REG_TCCR1,B1_COM1B0);
				set_bit(REG_TCCR1,B1_COM1B1);
				break;
			case PWM1B_Inverted:
				set_bit(REG_TCCR1,B1_COM1B0);
				set_bit(REG_TCCR1,B1_COM1B1);
				break;
		}
	}
}
/* Disable Timer/Counter1 Interrupt overflow */
extern void TIMER1_vidOVDisable()
{
	clr_bit(REG_TIMSK,B1_TOIE1);
}
/* Disable Timer/Counter Interrupt Compare match channel A */
extern void TIMER1_vidCMDisable()
{
	clr_bit(REG_TIMSK,B1_OCIE1A);
}
/*set TCNT1 Value to start count with */
extern void TIMER1_vidSetTCNT1(u16 u16Value)
{
	REG_TCNT1=u16Value;
}
/*set OCR1A  Value to Compare  with*/
extern void TIMER1_vidSetOCR1A(u16 u16Value)
{
	REG_OCR1A=u16Value;
}
/*set OCR1A  Value to Compare  with*/
extern void TIMER1_vidSetOCR1B(u16 u16Value)
{
	REG_OCR1B=u16Value;
}
/*set ICR1  Value to Compare  with*/
extern void TIMER1_vidSetICR1(u16 u16Value)
{
	REG_ICR1=u16Value;
}
/*  check compare match flag for channel A*/
/*
extern u8 TIMER1_u8CheckCMFlag()
{
	return get_bit(TIFR_REG,B1_OCF1A);
}
*/
/* */
/*CALL BACK INTERRUPT */

ISR(vect_TimerOVF1)
{
	Timer1_OVF();
}
void TIMER1_OVFCallBack(void (*pfn) (void))
{
	Timer1_OVF=pfn;
}

ISR(vect_TimerCOMP1A)
{
	Timer1_COMPA();
}
void TIMER1_COMPACallBack(void (*pfn) (void))
{
	Timer1_COMPA=pfn;
}
ISR(vect_TimerCOMP1B)
{
	Timer1_COMPB();
}
void TIMER1_COMPBCallBack(void (*pfn) (void))
{
	Timer1_COMPB=pfn;
}
ISR(vect_TimerOVF0)
{
	Timer0_OVF();
}
void TIMER0_OVFCallBack(void (*pfn) (void))
{
	Timer0_OVF=pfn;
}
ISR(vect_TimerCOMP0)
{
	Timer0_COMP();
}
void TIMER0_COMPCallBack(void (*pfn) (void))
{
	Timer0_COMP=pfn;
}
