/******************************************************************************
 * Module: PWM
 * File Name: pwm.c
 * Description: Source file for the AVR PWM driver
 * Author:	Yousif Adel
 *******************************************************************************/
#include <avr/io.h>
#include "pwm.h"

/*******************************************************************************
 *                              Functions Definitions                         *
 *******************************************************************************/
/*
 * Description:
➢ The function responsible for trigger the Timer0 with the PWM Mode.
➢ Setup the PWM mode with Non-Inverting.
➢ Setup the prescaler with F_CPU/8.
 * F_PWM=(F_CPU)/(256*N) = (10^6)/(256*8) = 500Hz , Compare register , updating by duty cycle
➢ Setup the compare value based on the required input duty cycle
➢ Setup the direction for OC0 as output pin through the GPIO driver.
➢ The generated PWM signal frequency will be 500Hz to control the DC Motor speed.
 */
void PWM_Timer0_Start (uint8 duty_cycle)
{

	/* 1.  Set Timer Initial Value to 0*/
	TCNT0 = 0;

	/* 2. set the compare value in OCR0*/
		/*The DutyCycle Is In Percentage So We Have To Make Some Calculations*/
	OCR0=(uint8)(((float32)duty_cycle/100)*255);

	/* 3. configure PB3/OC0 as output
	      pin --> pin where the PWM signal is generated from MC
	*/
	SET_BIT(PWM_PORT_ID,PWM_PIN_ID);
//	DDRB |= (1<<PB3);
	/*
	 * 4. Configure timer control register
	 *		 a. Fast PWM mode FOC0=0
	 *		 b. Fast PWM Mode WGM01=1 & WGM00=1
	 * 		 c. Clear OC0 when match occurs (non inverted mode) =>  COM00=0 & COM01=1
	 * 		 d. clock = F_CPU/8 CS00=0 CS01=1 CS02=0
	 */
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01);
}
