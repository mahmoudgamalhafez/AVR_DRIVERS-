/*
 * Keypad.c
 *
 *  Created on: Sep 7, 2018
 *      Author: elProf
 */
#include "../STD_Types.h"
#include "Keypad.h"
#include "../MCAL/DIO.h"
#include "Keypad_Cfg.h"


#define NO_OF_ROWS	((u8)4)
#define NO_OF_COLMS	((u8)4)

static u8 Columns[] = {C1_PIN , C2_PIN , C3_PIN, C4_PIN} ;
static u8 Rows[] = {R1_PIN , R2_PIN , R3_PIN, R4_PIN} ;

void KEYPAD_vidInit(void)
{
	u8 u8PinNo ;

	for(u8PinNo = 0 ; u8PinNo < 4 ; u8PinNo++)
	{
		/*Set columns as output*/
		DIO_vidSetPinDir(C_PORT,Columns[u8PinNo],OUTPUT) ;

		/*Set Coloms HIGH*/
		DIO_vidSetPinValue(C_PORT,Columns[u8PinNo],HIGH);

		/*Set Rows as input*/
		DIO_vidSetPinDir(R_PORT,Rows[u8PinNo],INPUT) ;

		/*Activate pull-up resistors */
		DIO_vidSetPinValue(R_PORT,Rows[u8PinNo],HIGH) ;
	}
}

KeyPadKey KEYPAD_u8GetPressedKey(void)
{
	u8 u8ColNo , u8RowNo , u8RetVal = 0 ;

	for (u8ColNo = 0 ; u8ColNo < NO_OF_COLMS ; u8ColNo++)
	{
		/*Activate column*/
		DIO_vidSetPinValue(C_PORT , Columns[u8ColNo] , LOW) ;

		for(u8RowNo=0 ; u8RowNo < NO_OF_ROWS ; u8RowNo++)
		{
			if (DIO_u8GetPinaValue(R_PORT,Rows[u8RowNo] ) == LOW)
				{
					u8RetVal =  ( (u8RowNo * NO_OF_COLMS) + u8ColNo+1) ;
					/*wait to depress the key*/
					while(DIO_u8GetPinaValue(R_PORT,Rows[u8RowNo] ) == LOW);
				}
		}

		/*Deactivate column*/
		DIO_vidSetPinValue(C_PORT , Columns[u8ColNo] , HIGH) ;
	}


	return u8RetVal ;
}

