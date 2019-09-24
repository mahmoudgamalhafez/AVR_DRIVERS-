/*
 * TIMER.h
 *
 *  Created on: Sep 7, 2019
 *      Author: mahmo
 */

#ifndef MCAL_TIMER_H_
#define MCAL_TIMER_H_
/*Timer_Counter Modes*/
	/*TIMER 0 */
#define MODE_PhaseCorrect  	2
#define	MODE_FASTPWM	 	3
	/*TIMER 0 && 1 */
#define	MODE_NORMAL 		0
#define MODE_CTC			1
	/*TIMER1 ONLY */
#define MODE_PWM8			4
#define MODE_PWM9			5
#define MODE_PWM10			6
#define MODE_FASTPWM8   	7
#define MODE_FASTPWM9		8
#define MODE_FASTPWM10		9
#define MODE_PPF_ICR1		10      //pwm phase frequency correct for top ICR1
#define MODE_PPF_OCR1A		11     //pwm phase frequency correct for top OCR1A
#define MODE_PP_ICR1		12    //pwm phase  correct top ICR1
#define MODE_PP_OCR1A		13   //pwm phase  correct top OCR1A
#define MODE_CTC_ICR1		14  //top ICR1A
#define MODE_FASTPWM_ICR1A  15 //top ICR1A
#define MODE_FASTPWM_OCR1A  16//top OCR1A

/*Timer_Counter Prescaling */
#define Prescaling_NOCLOCK			10
#define Prescaling_NOPRESCALING		11
#define Prescaling_8				12
#define Prescaling_64				13
#define Prescaling_256				14
#define Prescaling_1024				15
#define Prescaling_EXTFALLING		16
#define Prescaling_EXTRISING		17

/*TIMER0 Wave Generation */

#define WAVE_NONE		18
#define WAVE0_SETONCOMP	19
#define WAVE0_CLRONCOMP	20
#define WAVE0_TOGONCOMP	21
/* TIMER1 Wave Generantion Channel A  */
#define WAVE1A_SETONCOMP	22
#define WAVE1A_CLRONCOMP	23
#define WAVE1A_TOGONCOMP	24
/* TIMER1 Wave Generantion Channel B */
#define WAVE1B_SETONCOMP	25
#define WAVE1B_CLRONCOMP	26
#define WAVE1B_TOGONCOMP	27
/*TIMER0 PWM Generation */
#define PWM0_Inverted		28
#define PWM0_NonInverted	29
/*TIMER1 PWM Generation */
#define PWM1A_Inverted		30
#define PWM1A_NonInverted	31
#define PWM1B_Inverted		32
#define PWM1B_NonInverted	33





/*Fun Timer/Counter0*/
extern void TIMER0_vidOVEnable();
extern void TIMER0_vidCMEnable();
extern void TIMER0_vidInit(u8 Mode,u8 Prescaling,u8 WAVE_OR_PWM_GEN);
extern void TIMER0_vidOVDisable();
extern void TIMER0_vidCMDisable();
extern void TIMER0_vidSetTCNT0(u8 u8Value);
extern u8   TIMER0_u8GetTCNT0();
extern void TIMER0_vidSetOCR0(u8 u8Value);

/*Fun Timer/Counter1*/
extern void TIMER1_vidOVEnable();
extern void TIMER1_vidCMEnable();
extern void TIMER1_vidInit(u8 Mode,u8 Prescaling,u8 WAVE_OR_PWM_GEN);
extern void TIMER1_vidOVDisable();
extern void TIMER1_vidCMDisable();
extern void TIMER1_vidSetTCNT1(u16 Value);
extern void TIMER1_vidSetOCR1A(u16 Value);
extern void TIMER1_vidSetOCR1B(u16 u16Value);
extern void TIMER1_vidSetICR1(u16 Value);

//extern u8 TIMER1_u8CheckCMFlag();



void TIMER0_COMPCallBack(void (*pfn) (void));
void TIMER0_OVFCallBack(void (*pfn) (void));
void TIMER1_COMPBCallBack(void (*pfn) (void));
void TIMER1_COMPACallBack(void (*pfn) (void));
void TIMER1_OVFCallBack(void (*pfn) (void));





#endif /* MCAL_TIMER_H_ */
