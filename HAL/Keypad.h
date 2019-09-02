/*
 * Keypad.h
 *
 *  Created on: Sep 7, 2018
 *      Author: elProf
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_




typedef enum
{
	Key_No1 = 1 ,
	Key_No2 = 2 ,
	Key_No3 = 3 ,
	Key_No4 = 5,
	Key_No5 = 6,
	Key_No6 = 7,
	Key_No7 = 9,
	Key_No8 = 10,
	Key_No9 = 11,
	Key_No0 = 14,
	Key_A = 4,
	Key_B = 8,
	Key_C = 12,
	Key_D = 16,
	Key_STAR = 13,
	Key_HASH = 15,
	Key_NONE = 0
}KeyPadKey ;


void KEYPAD_vidInit(void);
u8 KEYPAD_u8GetPressedKey(void);

#endif /* KEYPAD_H_ */
