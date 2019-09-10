/*
 * E_INTERRUPT.h
 *
 *  Created on: Sep 3, 2019
 *      Author: mahmo
 */

#ifndef MCAL_E_INTERRUPT_H_
#define MCAL_E_INTERRUPT_H_

/*TRIGGRING*/
#define LOW					0
#define	LOGICAL_CHANGE		1
#define FALLING_EDGE		2
#define RISING_EDGE			3
/* External Interrupt Request 0 */
#define vect_INT0			1
/* External Interrupt Request 1 */
#define vect_INT1			2
/* External Interrupt Request 2 */
#define vect_INT3			3


/*
#  define ISR(vector, ...)            \
    void vector (void) __attribute__ ((signal,__INTR_ATTRS)) __VA_ARGS__; \
    void vector (void)
*/
/* */
void EINTERRUPT_vidGEnable();
void EINTERRUPT_vidGDisable();
void EINTERRUPT_vidENINT0(u8 Triggering);
void EINTERRUPT_vidENINT1(u8 Triggering);
void EINTERRUPT_vidENINT2(u8 Triggering);

#endif /* MCAL_E_INTERRUPT_H_ */
