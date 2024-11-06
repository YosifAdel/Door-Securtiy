/******************************************************************************
 * Module: DC Motor
 * File Name: dc_motor.h
 * Description: Header file for the AVR DC_motor driver
 * Author:	Yousif Adel
 *******************************************************************************/
#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
#define DC_MOTOR_PORT_ID						PORTB_ID
#define DC_MOTOR_First_PIN_ID					PIN0_ID
#define DC_MOTOR_Second_PIN_ID					PIN1_ID

typedef enum
{
	OFF,ON
}DcMotor_State;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
/*
 * decription:
 * The Function responsible for setup the direction for the two motor pins through the GPIO driver.
   Stop at the DC-Motor at the beginning through the GPIO driver.*/
void DcMotor_init(void);

/*
 * The function responsible for rotate the DC Motor CW/ or A-CW or stop the motor based on the state input state value.
 * Send the required duty cycle to the PWM driver based on the required speed value.*/

void DcMotor_Rotate(DcMotor_State state,uint8 speed);

#endif	/* DC_MOTOR_H_*/

