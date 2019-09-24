/*
 * LCD.c
 *
 *  Created on: Aug 23, 2019
 *      Author: elProf
 */

#include "../STD_Types.h"
#include "../macros.h"
#include "LCD.h"

#define F_CPU	8000000UL
#include 	"util/delay.h"
#include 	"../MCAL/DIO.h"
#include 	"LCD_CFG.h"

static void LOC_vidSendInstruction(u8 Ins);
//static void Check_Busy_Flag();


#define	FUNCTION_SET		0b00111100
#define DISPLAY_CONTROL		0b00001100
#define DISPLAY_CLEAR		0b00000001
#define ENTRY_MODE_SET		0b00000110

#define SHIFT_RIGHT			0b00011100
#define SHIFT_LEFT			0b00011000

#define CGRAM_ADDRESS 		0x48

extern void LCD_vidInit(void)
{
	DIO_vidSetPortDir(LCD_DATAPORT,OUTPUT);
	DIO_vidSetPinDir(LCD_RWPORT,LCD_RWPIN,OUTPUT);
	DIO_vidSetPinDir(LCD_EPORT,LCD_EPIN,OUTPUT);
	DIO_vidSetPinDir(LCD_RSPORT,LCD_RSPIN,OUTPUT);

	_delay_ms(30);
	LOC_vidSendInstruction(FUNCTION_SET);
	_delay_ms(2);
	LOC_vidSendInstruction(DISPLAY_CONTROL);
	_delay_ms(2);
	LOC_vidSendInstruction(DISPLAY_CLEAR);
	_delay_ms(2);
	LOC_vidSendInstruction(ENTRY_MODE_SET);
	_delay_ms(2);
}


static void LOC_vidSendInstruction(u8 Ins)
{
	/*set RW=0*/
	DIO_vidSetPinValue(LCD_RWPORT,LCD_RWPIN,LOW);
	/*set RS=0*/
	DIO_vidSetPinValue(LCD_RSPORT,LCD_RSPIN,LOW);
	/*set D0~D7*/
	DIO_vidSetPortValue(LCD_DATAPORT,Ins);
	/*Enable Falling edge*/
	DIO_vidSetPinValue(LCD_EPORT,PIN1,HIGH);
	_delay_ms(1);
	DIO_vidSetPinValue(LCD_EPORT,PIN1,LOW);
}

extern void LCD_vidWriteChar(u8 ch)
{
	/*set RW=0*/
	DIO_vidSetPinValue(LCD_RWPORT,LCD_RWPIN,LOW);
	/*set RS=1*/
	DIO_vidSetPinValue(LCD_RSPORT,LCD_RSPIN,HIGH);
	/*set D0~D7*/
	DIO_vidSetPortValue(LCD_DATAPORT,ch);
	/*Enable Falling edge*/
	DIO_vidSetPinValue(LCD_EPORT,LCD_EPIN,HIGH);
	_delay_ms(1);
	DIO_vidSetPinValue(LCD_EPORT,LCD_EPORT,LOW);

}
extern u8 LCD_u8WriteString(u8 *PointerToString)
{
	u8 NumberOfChars=0;
	while(*PointerToString){
		LCD_vidWriteChar(*PointerToString++);
		NumberOfChars++;

	}
	return NumberOfChars;
}
extern void LCD_vidShiftRight()
{
	//Check_Busy_Flag();
	//_delay_ms(2);
	LOC_vidSendInstruction(SHIFT_RIGHT);
}
extern void LCD_vidShiftLeft()
{
	//_delay_ms(2);
	LOC_vidSendInstruction(SHIFT_LEFT);
}

extern void LCD_vidSetCursor(u8 Line,u8 Position)
{
	switch(Line%2)
	{
		case 1:
			LOC_vidSendInstruction(0x80+0x00+Position);
			break;
		case 0:
			LOC_vidSendInstruction(0x80+0x40+Position);
			break;
		default:
			break;
	}
}
extern void LCD_vidClearScreen()
{
	LOC_vidSendInstruction(DISPLAY_CLEAR);
	LOC_vidSendInstruction(0x80);//return to first position
	//_delay_ms(2);
}

extern void LCD_ClearData(u8 Line)
{
	u8 i;
	LCD_vidSetCursor(Line,0);
	for(i=0;i<16;i++)
		LCD_vidWriteChar(' ');
	LCD_vidSetCursor(Line%2,0);
}
void LCD_CreatCustomPattern(u8 *Pattern,u8 Position)
{
	u8 i;
//	LCD_vidWriteChar('a');
	LOC_vidSendInstruction(CGRAM_ADDRESS);
	for(i=0;i<8;i++)
		LCD_vidWriteChar(*(Pattern+i));

	LOC_vidSendInstruction(0x80+0x00+Position);
	LCD_vidWriteChar(1);

}

/*Read address counter to determine position */
/*
extern u8 	LCD_u8ReadAddCounter()
{
	u8  temp ;
	DIO_vidSetPinValue(LCD_RWPORT,LCD_RWPIN,HIGH);
	DIO_vidSetPinValue(LCD_RSPORT,LCD_RSPIN,LOW);
	DIO_vidSetPortDir(LCD_DATAPORT,INPUT);
	DIO_vidSetPinValue(LCD_EPORT,LCD_EPIN,HIGH);
	temp=DIO_vidGetPortValue(LCD_DATAPORT);
	temp-=0x80; //CLEAR LAST BIT BUSY FLAG
//	temp&=~(1<<PIN7); //
	DIO_vidSetPortDir(LCD_DATAPORT,OUTPUT);
	return temp;
}
/*NOT WORKING */
/*
static void Check_Busy_Flag()
{

	DIO_vidSetPinValue(LCD_RWPORT,LCD_RWPIN,HIGH);

	DIO_vidSetPinValue(LCD_RSPORT,LCD_RSPIN,LOW);

	DIO_vidSetPortDir(LCD_DATAPORT,INPUT);
	while(DIO_u8GetPinaValue(LCD_DATAPORT,PIN7) ){
		DIO_vidSetPinValue(LCD_EPORT,LCD_EPIN,HIGH);
		_delay_ms(1);
		DIO_vidSetPinValue(LCD_EPORT,LCD_EPORT,LOW);
	}
	DIO_vidSetPortDir(LCD_DATAPORT,OUTPUT);
}

*/
