/******************************************************************************
 * Module: Buzzer
 * File Name: buzzer.h
 * Description: Header file for the Buzzer driver
 * Author:	Yousif Adel
 *******************************************************************************/

#ifndef BUZZER_H_
#define BUZZER_H_
#include	"gpio.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define BUZZER_PORT_ID					PORTA_ID
#define BUZZER_PIN_ID					PIN0_ID

#define BUZZER_ON						LOGIC_HIGH
#define BUZZER_OFF						LOGIC_LOW

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 ● Description
	⮚ Setup the direction for the buzzer pin as output pin through the GPIO driver.
	⮚ Turn off the buzzer through the GPIO.
● Inputs: None
● Return: None
*/
void Buzzer_init();

/*
● Description
	⮚ Function to enable the Buzzer through the GPIO.
● Inputs: None
● Return: None
*/
void Buzzer_on(void);

/*
● Description
	⮚ Function to disable the Buzzer through the GPIO.
● Inputs: None
● Return: No
*/
void Buzzer_off(void);

#endif /* BUZZER_H_ */

