/*
 * macros.h
 *
 *  Created on: Aug 11, 2018
 *      Author: hamed
 */

#ifndef MACROS_H_
#define MACROS_H_
#define set_bit(Data,Bit) Data|= (1<<Bit)
#define clr_bit(Data,Bit) Data&= ~(1<<Bit)
#define toggle_bit(Data,Bit) Data^= (1<<Bit)
#define get_bit(Data,Bit) (Data>>Bit)&1
#define assign_bit(Data,Bit,Val) (Val==1)? (set_bit(Data,Bit)):(clr_bit(Data,Bit))

#define ISR(vect_no)      void vect(vect_no)(void) __attribute__ ((signal)) ; \
						void vect(vect_no) (void)

#define vect(x) __vector_##x

#endif /* MACROS_H_ */
