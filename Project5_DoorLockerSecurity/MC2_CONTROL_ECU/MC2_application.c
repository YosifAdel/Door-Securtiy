/******************************************************************************
 * File Name: control_ecu_MC2.c
 * Description: (Control Interface) in the Door Locker Security System
 * Author: Yousif Adel
 * Date: 11/6/2023
 *******************************************************************************/
#include 	"buzzer.h"
#include 	"external_EEPROM.h"
#include	"dc_motor.h"
#include 	"uart.h"
#include 	"timer1.h"
#include	<util/delay.h>
#include 	"twi.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define ZERO							0

#ifdef TIMER1_COMPARE
#define COMPARE_VALUE					7812	// Compare Value for timer 1 if Compare mode defined
#endif

/* UART Values Between MC1 & MC2 */
#define MC1_READY 						0x01	// MC1 is ready
#define MC2_READY 						0x02	// MC2 is ready

#define CHANGE_PASSWORD					0x13	// change the password
#define SAVE_PASSWORD 					0x04	// save the password
#define PASSWORD_SAVED					0x05	// password has been saved
#define UNLOCK_THE_DOOR					0x12	// open the door [door sequence]
#define BUZZER_ON_BYTE					0x11	// turn the buzzer on	[buzzer sequence]
#define SEND_PASSWORD_TO_BE_CHECKED 	0x06	// send the password to be checked
#define PASSWORD_CHECK					0x12	// check if the password correct
#define PASSWORD_DOESNT_MATCH			0x08	// password WRONG
#define PASSWORD_MATCH					0x09	// password correct
#define BEGGINING_OF_EEPROM_ADDRESS		0x70	// the first address of the password at EEPROM

/* Password Configurations */
#define PASSWORD_SIZE					5		// Size of the password
#define WRONG_PASSWORD					0		// Indicates that is a wrong password
#define RIGHT_PASSWORD					1		// Indicates that is a correct password

#define MAX_NO_OF_WRONG_TIMES			3		// Maximum no of wrong times before buzzer turned ON

/* Main Options Configurations*/
#define OPEN_DOOR_OPTION				'+'		// Option that enable Opening the door
#define CHANGE_PASSWORD_OPTION			'-'		// Option that change the password of the system

/* Password Symbols */
#define SUBMIT_PASSWORD					'='		// Indicates that the user want to submit the password
#define PASSWORD_MARK					'*'		// Password mark that appears on LCD

/* Motor Movement Time & Speed Configurations */
#define MOTOR_CW_TIME					15
#define MOTOR_STOP_TIME					3
#define MOTOR_ACW_TIME					15
#define ERROR_TIME						60
#define DC_MOTOR_SPEED					100

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
static uint8 volatile g_tick = 0;		/* to count ticks */

uint8 g_responseByte; // to store the response

/*******************************************************************************
 *                           Structure Configurations                          *
 *******************************************************************************/
/* Set The UART Configurations */
UART_ConfigType UART_Configurations = {EIGHT_BITS, DISABLED, ONE_BIT, BD_9600, ASYNCHRONOUS, ASYNCHRONOUS_DOUBLE_SPEED};

/*
 * create configuration for timer to get interrupt every 1 second
 * To calculate 1second -> F = 1Hz
    	F = F(CPU)/N(1+x) = 8Mhz/ N(1+x) try different pre-scalar
    	N = 64  , x = 124999
    	N = 256 , x = 31249
    	N = 1024 , x = 7812
    so the better is N = 1024
 * Set The Timer 1 Configurations
 */
Timer1_ConfigType Timer1_Configuration = {ZERO, COMPARE_VALUE, F_CPU_1024, CTC_OCR1A};
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/* Description:
 * 	used to set the required time in each task.
 */
void Timer_callBack(void);

/* Description:
 * 	function to save the password in the EEPROM memory.
 */
void receive_password(void);

/* Description:
 * 	function to read the password from the EEPROM memory and check whether correct or wrong.
 */
void checkThePasswordAfterBeingStored(void);

/* Description:
 * 	function to activate the motor and do its sequence [unlocking , open , locking, locked].
 */
void motorSequence(void);

/* Description:
 * 	function to activate the buzzer and do its sequence.
 */
void buzzer_IS_OPENED(void);

/*Description:
 * check the state of response and do each task depends on the response
 * */
void responseProcesses(void);
/*******************************************************************************/

/* Application Code */
int main(void)
{
	/*Enable I-bit = 1*/
	S_REG.Bits.I_Bit = 1;


	/*set the configurations of the I2C and pass it to the structure*/
	TWI_ConfigType	TWI_Configurations =
	{0x01,BR_400K};

	/*initiate UART driver*/
	UART_init(&UART_Configurations);

	/*initiate I2C driver*/
	TWI_init(&TWI_Configurations);

	/* initialize timer 1 driver*/
	Timer1_init(&Timer1_Configuration);
	/* set the call back to pointer in the Timer 1 */
	Timer1_setCallBack(Timer_callBack);

	/*initiate Buzzer driver*/
	Buzzer_init();

	/*initiate DC_motor driver*/
	DcMotor_init();

	/* wait until MC2 receive that MC1 is ready*/
	while(UART_recieveByte()!=MC1_READY);

	/* receive the password to be inserted in the EEPROM*/
	receive_password();

	while(1)
	{

		/* store the state of the received byte */
		g_responseByte = UART_recieveByte();

		/* check the state of response and do each task depends on the response */
		responseProcesses();

	}
}

/*Description:
 * check the state of response and do each task depends on the response
 * */
void responseProcesses(void)
{
	switch(g_responseByte)
	{
	/* this means that the password has been sent*/
	case SEND_PASSWORD_TO_BE_CHECKED:
		/* check whether its correct or not*/
		checkThePasswordAfterBeingStored();
		break;

	/* this means that the password is correct and request to open the door*/
	case UNLOCK_THE_DOOR:
		/* Door sequence [motor]*/
		motorSequence();
		break;

	/* this means that the password is wrong 3 times and the buzzer opened*/
	case BUZZER_ON_BYTE:
		/* Open the Buzzer for specific time */
		buzzer_IS_OPENED();
		break;
	case CHANGE_PASSWORD:
		/*Change the password sequence*/
		receive_password();
		break;
	}
}


/* Description:
 * 	used to set the required time in each task.
 */
void Timer_callBack(void)
{
	g_tick++;
	/* clear the register*/
	TCNT1_REG.TwoBytes = 0;
}

/* Description:
 * 	function to save the password in the EEPROM memory.
 */
void receive_password(void)
{

	/* variable to receive each byte of the password*/
	uint8 pass;

	/* variable to count from 0 to password size*/
	uint8 passCounter;

	/* waits until the MC1 send the password to be stored at EEPROM*/
	while(UART_recieveByte() != SAVE_PASSWORD);

	/* loop to receive the password byte by byte*/
	for(passCounter = 0; passCounter<PASSWORD_SIZE;passCounter++)
	{
		/*send byte to till the MC1 that MC2 is ready to receive the password*/
		UART_sendByte(MC2_READY);

		/* receive each byte using this loop in pass variable*/
		pass = UART_recieveByte();

		/*after receive the byte in pass write it in the EEPROM*/
		EEPROM_writeByte((BEGGINING_OF_EEPROM_ADDRESS+passCounter) , pass);
		_delay_ms(10);
	}

	/* after the loop this means that the password has been stored in the EEPROM*/
	/* send byte to MC1 to tell him that the password has been saved*/
	UART_sendByte(PASSWORD_SAVED);
}

/* Description:
 * 	function to read the password from the EEPROM memory and check whether correct or wrong.
 */
void checkThePasswordAfterBeingStored(void)
{
	/* variable to count from 0 to password size*/
	uint8 passCounter;

	uint8 wrong_times = 0;	/* variable to store the wrong times that password have been submitted*/

	/* array to store the entered password*/
	uint8 entered_pass[PASSWORD_SIZE];

	/* array of the saved password [correct password]*/
	uint8 saved_pass[PASSWORD_SIZE];

	/* waits until MC1 send the password and MC2 received to be checked*/
	while(UART_recieveByte() != PASSWORD_CHECK);

	passCounter = 0;
	/* check if the two arrays of password are identical or not*/
	while(passCounter < PASSWORD_SIZE)
	{
		/*send byte to till the MC1 that MC2*/
		UART_sendByte(MC2_READY);

		/* receive each byte using this loop in pass variable*/
		entered_pass[passCounter] = UART_recieveByte();

		/*after receive the byte in pass write it in the EEPROM*/
		EEPROM_readByte((BEGGINING_OF_EEPROM_ADDRESS + passCounter) , &saved_pass[passCounter]);
		_delay_ms(10);

		/* if any character is different then both are not identical then it is not matched
		 * increase wrong times */
		if(entered_pass[passCounter] != saved_pass[passCounter])
		{
			wrong_times ++;
		}

		if(wrong_times == 0)
		{
			/* This means the person entered the password Correct*/
			UART_sendByte(PASSWORD_MATCH);
		}
		/* This means the person entered the password wrong*/
		else
		{
			UART_sendByte(PASSWORD_DOESNT_MATCH);
		}
		passCounter++;
	}

}

/* Description:
 * 	function to activate the motor and do its sequence [unlocking , open , locking, locked].
 */
void motorSequence(void)
{
	/* initialize timer 1 driver*/
	Timer1_init(&Timer1_Configuration);
	Timer1_setCallBack(Timer_callBack);

	/* 1. Unlock the Door for specific time , so the motor will operate in CW*/
	DcMotor_Rotate(CW, DC_MOTOR_SPEED);
	/* initiate the time for this specific time*/
	/*set g_tick = 0 to clear it*/
	g_tick = 0;
	/* waits until the motor movement CW time be done then break the loop*/
	while (g_tick != MOTOR_CW_TIME) {} ;

	/* 2. Open the Door for specific time , so the motor will operate in CW*/
	DcMotor_Rotate(OFF, ZERO);
	/* initiate the time for this specific time*/
	/*set g_tick = 0 to clear it*/
	g_tick = 0;
	/* waits until the motor stop time be done then break the loop*/
	while (g_tick != MOTOR_STOP_TIME) {} ;

	/* 3. Lock the Door for specific time , so the motor will operate in CW*/
	DcMotor_Rotate(ACW, DC_MOTOR_SPEED);

	/* initiate the time for this specific time*/
	/*set g_tick = 0 to clear it*/
	g_tick = 0;
	/* waits until the motor movement ACW be done then break the loop*/
	while (g_tick != MOTOR_ACW_TIME) {} ;


	/* 4. stop the motor and stop the timer*/
	DcMotor_Rotate(OFF,DC_MOTOR_SPEED);
	/* stop the timer */
	Timer1_deInit();
}

/* Description:
 * 	function to activate the buzzer and do its sequence.
 */
void buzzer_IS_OPENED(void)
{
	/* initialize timer 1 driver*/
	Timer1_init(&Timer1_Configuration);
	Timer1_setCallBack(Timer_callBack);

	/*set g_tick = 0 to clear it*/
	g_tick = 0;

	Buzzer_on();
	/* waits until the door open time be done then break the loop*/
	while (g_tick != ERROR_TIME) {} ;

	/*after the error time finish , turn the buzzer OFF*/
	Buzzer_off();

	/* stop the timer */
	Timer1_deInit();
	/*set g_tick = 0 to clear it*/
	g_tick = 0;
}
