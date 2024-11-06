/******************************************************************************
 * Module: DC Motor
 * File Name: dc_motor.c
 * Description: Source file for the AVR DC_motor driver
 * Author:	Yousif Adel
 *******************************************************************************/
#include "gpio.h"
#include "dc_motor.h"
#include "pwm.h"

/*******************************************************************************
 *                              Functions Definitions                         *
 *******************************************************************************/
/*
 * decription:
 * The Function responsible for setup the direction for the two motor pins through the GPIO driver.
   Stop at the DC-Motor at the beginning through the GPIO driver.*/
void DcMotor_init(void)
{
	GPIO_setupPinDirection(DC_MOTOR_PORT_ID,DC_MOTOR_First_PIN_ID,PIN_OUTPUT);	/* PC0 Output Pin */
	GPIO_setupPinDirection(DC_MOTOR_PORT_ID,DC_MOTOR_Second_PIN_ID,PIN_OUTPUT);	/* PC1 Output Pin */

	/* Turn off the motor */
	GPIO_writePin(DC_MOTOR_PORT_ID,DC_MOTOR_First_PIN_ID,LOGIC_LOW);
	GPIO_writePin(DC_MOTOR_PORT_ID,DC_MOTOR_Second_PIN_ID,LOGIC_LOW);
}


/*
 * The function responsible for rotate the DC Motor CW/ or A-CW or stop the motor based on the state input state value.
 * Send the required duty cycle to the PWM driver based on the required speed value.*/

void DcMotor_Rotate(DcMotor_State state,uint8 speed)
{
		PWM_Timer0_Start(speed);
		switch(state)
		{
		case OFF:
			/* Stop the motor */
			GPIO_writePin(DC_MOTOR_PORT_ID,DC_MOTOR_First_PIN_ID,LOGIC_LOW);
			GPIO_writePin(DC_MOTOR_PORT_ID,DC_MOTOR_Second_PIN_ID,LOGIC_LOW);
			break;
		case ON:
			/* Rotates the motor CW */
			GPIO_writePin(DC_MOTOR_PORT_ID,DC_MOTOR_First_PIN_ID,LOGIC_HIGH);
			GPIO_writePin(DC_MOTOR_PORT_ID,DC_MOTOR_Second_PIN_ID,LOGIC_LOW);
			break;
		default:
			/*Do Nothing*/
		break;
		}
}
