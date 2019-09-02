/*
 * Stepper_Motor.c
 *
 *  Created on: Sep 2, 2019
 *      Author: mahmo
 */
/*interfacing stepper motor with ATmega32 and the Darlington pair
 * ULN2003 IC
 *
 * */
#include "../STD_Types.h"
#include "Stepper_Motor.h"
#include "../MCAL/DIO.h"
#include "Stepper_Motor_CFG.h"
#include "util/delay.h"


void StepperMotor_vidInit()
{
	DIO_vidSetPinDir(StepperMotor_PORT,StepperMotor_BLUE_PIN,OUTPUT);
	DIO_vidSetPinDir(StepperMotor_PORT,StepperMotor_PINK_PIN,OUTPUT);
	DIO_vidSetPinDir(StepperMotor_PORT,StepperMotor_YELLOW_PIN,OUTPUT);
	DIO_vidSetPinDir(StepperMotor_PORT,StepperMotor_ORANGE_PIN,OUTPUT);
}

void StepperMotor_vidRotateCW()
{
	DIO_vidSetPinValue(StepperMotor_PORT,StepperMotor_BLUE_PIN,HIGH);
	DIO_vidSetPinValue(StepperMotor_PORT,StepperMotor_PINK_PIN,LOW);
	DIO_vidSetPinValue(StepperMotor_PORT,StepperMotor_YELLOW_PIN,LOW);
	DIO_vidSetPinValue(StepperMotor_PORT,StepperMotor_ORANGE_PIN,LOW);
	_delay_ms(5);
	DIO_vidSetPinValue(StepperMotor_PORT,StepperMotor_BLUE_PIN,LOW);
	DIO_vidSetPinValue(StepperMotor_PORT,StepperMotor_PINK_PIN,HIGH);
	DIO_vidSetPinValue(StepperMotor_PORT,StepperMotor_YELLOW_PIN,LOW);
	DIO_vidSetPinValue(StepperMotor_PORT,StepperMotor_ORANGE_PIN,LOW);
	_delay_ms(5);
	DIO_vidSetPinValue(StepperMotor_PORT,StepperMotor_BLUE_PIN,LOW);
	DIO_vidSetPinValue(StepperMotor_PORT,StepperMotor_PINK_PIN,LOW);
	DIO_vidSetPinValue(StepperMotor_PORT,StepperMotor_YELLOW_PIN,HIGH);
	DIO_vidSetPinValue(StepperMotor_PORT,StepperMotor_ORANGE_PIN,LOW);
	_delay_ms(5);
	DIO_vidSetPinValue(StepperMotor_PORT,StepperMotor_BLUE_PIN,LOW);
	DIO_vidSetPinValue(StepperMotor_PORT,StepperMotor_PINK_PIN,LOW);
	DIO_vidSetPinValue(StepperMotor_PORT,StepperMotor_YELLOW_PIN,LOW);
	DIO_vidSetPinValue(StepperMotor_PORT,StepperMotor_ORANGE_PIN,HIGH);
	_delay_ms(5);
}
void StepperMotor_vidRotateACW()
{
	DIO_vidSetPinValue(StepperMotor_PORT,StepperMotor_BLUE_PIN,LOW);
	DIO_vidSetPinValue(StepperMotor_PORT,StepperMotor_PINK_PIN,LOW);
	DIO_vidSetPinValue(StepperMotor_PORT,StepperMotor_YELLOW_PIN,LOW);
	DIO_vidSetPinValue(StepperMotor_PORT,StepperMotor_ORANGE_PIN,HIGH);
	_delay_ms(5);
	DIO_vidSetPinValue(StepperMotor_PORT,StepperMotor_BLUE_PIN,LOW);
	DIO_vidSetPinValue(StepperMotor_PORT,StepperMotor_PINK_PIN,LOW);
	DIO_vidSetPinValue(StepperMotor_PORT,StepperMotor_YELLOW_PIN,HIGH);
	DIO_vidSetPinValue(StepperMotor_PORT,StepperMotor_ORANGE_PIN,LOW);
	_delay_ms(5);
	DIO_vidSetPinValue(StepperMotor_PORT,StepperMotor_BLUE_PIN,LOW);
	DIO_vidSetPinValue(StepperMotor_PORT,StepperMotor_PINK_PIN,HIGH);
	DIO_vidSetPinValue(StepperMotor_PORT,StepperMotor_YELLOW_PIN,LOW);
	DIO_vidSetPinValue(StepperMotor_PORT,StepperMotor_ORANGE_PIN,LOW);
	_delay_ms(5);
	DIO_vidSetPinValue(StepperMotor_PORT,StepperMotor_BLUE_PIN,HIGH);
	DIO_vidSetPinValue(StepperMotor_PORT,StepperMotor_PINK_PIN,LOW);
	DIO_vidSetPinValue(StepperMotor_PORT,StepperMotor_YELLOW_PIN,LOW);
	DIO_vidSetPinValue(StepperMotor_PORT,StepperMotor_ORANGE_PIN,LOW);
	_delay_ms(5);
}
