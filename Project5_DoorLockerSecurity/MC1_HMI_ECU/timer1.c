 /******************************************************************************
 * Module: TIMER 1
 * File Name: timer1.c
 * Description: Source file for the AVR TIMER 1 driver
 * Author: Yousif Adel
 *******************************************************************************/
#include	"timer1.h"
#include	<avr/interrupt.h>
/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callBackPtr)(void) = NULL_PTR;

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/
#ifdef TIMER1_COMPARE
#if(CTC_CHANNEL == A)
ISR(TIMER1_COMPA_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}
#elif (CTC_CHANNEL == B)
ISR(TIMER1_COMPB_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}
#endif	/* End Of Channel of Compare Mode*/
#endif /* End of Compare Mode */

#ifdef TIMER1_NORMAL
ISR(TIMER1_OVF_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}
#endif		/* Normal Mode */

/*******************************************************************************
 *                      Functions Definitions                                   *
 *******************************************************************************/
/*
● Description:
  	  ⮚ Function to initialize the Timer driver
● Inputs: pointer to the configuration structure with type Timer1_ConfigType.
● Return: None
 */
void Timer1_init(const Timer1_ConfigType * Config_Ptr)
{
	/* 1. Set timer1 initial count */
	TCNT1_REG.TwoBytes = Config_Ptr->initial_value;

	/* 2. Non PWM mode FOC1A=1 and FOC1B=1 */
	TCCR1A_REG.Bits.FOC1A_Bit = 1;
	TCCR1A_REG.Bits.FOC1B_Bit = 1;

	/* 3. Set the mode using WGM10 [TCCR1A] , WGM11 [TCCR1A], WGM12[TCCR1B] */
	TCCR1A_REG.Bits.WGM10_Bit =  ((Config_Ptr->mode) & 0x01);
	TCCR1A_REG.Bits.WGM11_Bit =  (((Config_Ptr->mode) & 0x02) >> 1);
	TCCR1B_REG.Bits.WGM12_Bit =  (((Config_Ptr->mode) & 0x04) >> 2);

	/* 4. set the Pre-Scalar*/
	TCCR1B_REG.Bits.CS10_Bit = ((Config_Ptr->prescaler) & 0x01);
	TCCR1B_REG.Bits.CS11_Bit =  (((Config_Ptr->prescaler) & 0x02) >> 1);
	TCCR1B_REG.Bits.CS12_Bit =  (((Config_Ptr->prescaler) & 0x04) >> 2);

	/* disconnect OC1A/OC1B on compare match, set OC1A/OC1B at BOTTOM */
#ifdef TIMER1_NORMAL
	/* enable Normal Interrupt Enable*/
	TIMSK_REG.Bits.TOIE1_Bit = 1;
#endif

#ifdef TIMER1_COMPARE
#if (CTC_CHANNEL == A)
	/* 1. Set the Compare value in channel A if we using compare mode */
	OCR1A_REG.TwoBytes = Config_Ptr->compare_value;
	/* 2. enable compare interrupt enable*/
	TIMSK_REG.Bits.OCIE1A_Bit= 1;
#elif (CTC_CHANNEL == B)
	/* 1. Set the Compare value in channel B if we using compare mode */
	OCR1B_REG.TwoBytes = Config_Ptr->compare_value;
	/* 2. enable compare interrupt enable*/
	TIMSK_REG.Bits.OCIE1B_Bit= 1;
#endif
#endif
}

/*
● Description:
	⮚ Function to disable the Timer1.
● Inputs: None
● Return: None
 */
void Timer1_deInit(void)
{
	/* Clear Timer1 Registers */
	TCCR1A_REG.Byte = 0;
	TCCR1B_REG.Byte = 0;
}

/*
● Description:
	⮚ Function to set the Call Back function address.
● Inputs: pointer to Call Back function.
● Return: None
 */

void Timer1_setCallBack(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr = a_ptr;
}
