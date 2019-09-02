/*
 * BUZZER.c
 *
 *  Created on: Sep 1, 2019
 *      Author: mahmo
 */
#include "../STD_Types.h"
#include "BUZZER.h"
#include "../MCAL/DIO.h"
#include "BUZZER_CFG.h"

void BUZZER_vidInit()
{
	DIO_vidSetPinDir(BUZZER_PORT,BUZZER_PIN,OUTPUT);
}
void BUZZER_vidON()
{
	DIO_vidSetPinValue(BUZZER_PORT,BUZZER_PIN,HIGH);
}

void BUZZER_vidOFF()
{
	DIO_vidSetPinValue(BUZZER_PORT,BUZZER_PIN,LOW);
}
