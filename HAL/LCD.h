/*
+ * LCD.h
 *
 *  Created on: Aug 23, 2019
 *      Author: elProf
 */

#ifndef HAL_LCD_H_
#define HAL_LCD_H_

extern void LCD_vidInit(void);
extern void LCD_vidWriteChar(u8 ch);
extern u8 	LCD_u8WriteString(u8 *PointerToString);
extern void LCD_vidShiftRight();
extern void LCD_vidShiftLeft();
extern void LCD_vidSetCursor(u8 Line,u8 Position);
extern u8 	LCD_u8ReadAddCounter();
extern void LCD_ClearData(u8 Line);
extern void LCD_CreatCustomPattern(u8 *Pattern,u8 Position);
extern void LOC_vidSendInstruction(u8 Ins);

#endif /* HAL_LCD_H_ */
