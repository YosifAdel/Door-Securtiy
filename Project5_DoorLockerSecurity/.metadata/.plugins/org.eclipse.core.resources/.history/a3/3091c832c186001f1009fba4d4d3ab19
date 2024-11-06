 /******************************************************************************
 * Module: TIMER 1
 * File Name: timer1.h
 * Description: Header file for the AVR TIMER 1 driver
 * Author: Yousif Adel
 *******************************************************************************/
#ifndef TIMER1_H_
#define TIMER1_H_

#include	"std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define MODE			COMPARE

#if(Mode == COMPARE)
#define TIMER1_COMPARE
#define CTC_CHANNEL		A

#elif(MODE == NORMAL)
#define TIMER1_NORMAL

/* not supported in this driver PWM */
#elif(MODE == PWM)
#define TIMER1_PWM
#endif

/************************* Timer1 Registers type structure declarations ************************/
typedef union {
	uint8 Byte;
	struct{
		uint8 WGM10_Bit:1;
		uint8 WGM11_Bit:1;
		uint8 FOC1A_Bit:1;
		uint8 FOC1B_Bit:1;
		uint8 COM1B0_Bit:1;
		uint8 COM1B1_Bit:1;
		uint8 COM1A0_Bit:1;
		uint8 COM1A1_Bit:1;
	}Bits;
}Timer1_TCCR1A_Type;

typedef union {
	uint8 Byte;
	struct{
		uint8 CS10_Bit:1;
		uint8 CS11_Bit:1;
		uint8 CS12_Bit:1;
		uint8 WGM12_Bit:1;
		uint8 WGM13_Bit:1;
		uint8 :1;
		uint8 ICES1_Bit:1;
		uint8 ICNC1_Bit:1;
	}Bits;
}Timer1_TCCR1B_Type;

typedef union
{
	uint16 TwoBytes;
	struct
	{
		uint16 Bit0:1;
		uint16 Bit1:1;
		uint16 Bit2:1;
		uint16 Bit3:1;
		uint16 Bit:1;
		uint16 Bit5:1;
		uint16 Bit6:1;
		uint16 Bit7:1;
		uint16 Bit8:1;
		uint16 Bit9:1;
		uint16 Bit10:1;
		uint16 Bit11:1;
		uint16 Bit12:1;
		uint16 Bit13:1;
		uint16 Bit14:1;
		uint16 Bit15:1;
	}Bits;
}Timer1_TCNT1_Type;

typedef union
{
	uint16 TwoBytes;
	struct
	{
		uint16 Bit0:1;
		uint16 Bit1:1;
		uint16 Bit2:1;
		uint16 Bit3:1;
		uint16 Bit:1;
		uint16 Bit5:1;
		uint16 Bit6:1;
		uint16 Bit7:1;
		uint16 Bit8:1;
		uint16 Bit9:1;
		uint16 Bit10:1;
		uint16 Bit11:1;
		uint16 Bit12:1;
		uint16 Bit13:1;
		uint16 Bit14:1;
		uint16 Bit15:1;
	}Bits;
}Timer1_OCR1A_Type;

typedef union
{
	uint16 TwoBytes;
	struct
	{
		uint16 Bit0:1;
		uint16 Bit1:1;
		uint16 Bit2:1;
		uint16 Bit3:1;
		uint16 Bit:1;
		uint16 Bit5:1;
		uint16 Bit6:1;
		uint16 Bit7:1;
		uint16 Bit8:1;
		uint16 Bit9:1;
		uint16 Bit10:1;
		uint16 Bit11:1;
		uint16 Bit12:1;
		uint16 Bit13:1;
		uint16 Bit14:1;
		uint16 Bit15:1;
	}Bits;
}Timer1_OCR1B_Type;

typedef union
{
	uint16 TwoBytes;
	struct
	{
		uint16 Bit0:1;
		uint16 Bit1:1;
		uint16 Bit2:1;
		uint16 Bit3:1;
		uint16 Bit:1;
		uint16 Bit5:1;
		uint16 Bit6:1;
		uint16 Bit7:1;
		uint16 Bit8:1;
		uint16 Bit9:1;
		uint16 Bit10:1;
		uint16 Bit11:1;
		uint16 Bit12:1;
		uint16 Bit13:1;
		uint16 Bit14:1;
		uint16 Bit15:1;
	}Bits;
}Timer1_ICR1_Type;

typedef union {
	uint8 Byte;
	struct{
		uint8 TOIE0_Bit:1;
		uint8 OCIE0_Bit:1;
		uint8 TOIE1_Bit:1;
		uint8 OCIE1B_Bit:1;
		uint8 OCIE1A_Bit:1;
		uint8 TICIE1_Bit:1;
		uint8 TOIE2_Bit:1;
		uint8 OCIE2_Bit:1;
	}Bits;
}Timers_TIMSK_Type;

typedef union {
	uint8 Byte;
	struct{
		uint8 TOV0_Bit:1;
		uint8 OCF0_Bit:1;
		uint8 TOV1_Bit:1;
		uint8 OCF1B_Bit:1;
		uint8 OCF1A_Bit:1;
		uint8 ICF1_Bit:1;
		uint8 TOV2_Bit:1;
		uint8 OCF2_Bit:1;
	}Bits;
}Timers_TIFR_Type;


/******************************************************************************/

/*********************************** Timer1 Registers Definitions *************/
#define TCNT1_REG     (*(volatile Timer1_TCNT1_Type*)0x4C)
#define TCCR1A_REG    (*(volatile Timer1_TCCR1A_Type*)0x4F)
#define TCCR1B_REG    (*(volatile Timer1_TCCR1B_Type*)0x4E)
#define TIFR_REG      (*(volatile Timers_TIFR_Type*)0x58)
#define TIMSK_REG     (*(volatile Timers_TIMSK_Type*)0x59)
#define OCR1A_REG     (*(volatile Timer1_OCR1A_Type*)0x4A)
#define OCR1B_REG     (*(volatile Timer1_OCR1B_Type*)0x48)
#define ICR1_REG      (*(volatile Timer1_ICR1_Type*)0x46)

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

typedef enum
{
	NORMAL,CTC_OCR1A = 4
}Timer1_Mode;

typedef enum
{
	NO_CLOCK,
	F_CPU_CLOCK, F_CPU_8, F_CPU_64, F_CPU_256, F_CPU_1024,
	EXTERNAL_CLOCK_FALLING,
	EXTERNAL_CLOCK_RISING
}Timer1_Prescaler;

typedef struct {
	uint16 initial_value;
#if(MODE == COMPARE)
	uint16 compare_value; // it will be used in compare mode only.
#endif
	Timer1_Prescaler prescaler;
	Timer1_Mode mode;
} Timer1_ConfigType;


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
● Description:
  	  ⮚ Function to initialize the Timer driver
● Inputs: pointer to the configuration structure with type Timer1_ConfigType.
● Return: None
 */
void Timer1_init(const Timer1_ConfigType * Config_Ptr);

/*
● Description:
	⮚ Function to disable the Timer1.
● Inputs: None
● Return: None
*/
void Timer1_deInit(void);

/*
● Description:
	⮚ Function to set the Call Back function address.
● Inputs: pointer to Call Back function.
● Return: None
*/
void Timer1_setCallBack(void(*a_ptr)(void));

#endif /* TIMER1_H_ */
