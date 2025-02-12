 /******************************************************************************
 * Module: UART
 * File Name: uart.h
 * Description: Header file for the AVR UART driver
 * Author: Yousif Adel
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include	"std_types.h"

/* Define The UART Speed Mode */
#define UART_SPEED_MODE 	ASYNCHRONOUS_DOUBLE_SPEED_MODE
/*******************************************************************************
 *                         Macros 		                                   *
 *******************************************************************************/
#if (UART_SPEED_MODE == ASYNCHRONOUS_DOUBLE_SPEED_MODE)
/* Macro responsible for calculate baud rate for Asynchronous Normal Mode*/
#define ASYNCHRONOUS_NORMAL_MODE(F_CPU, BAUD_RATE) (((F_CPU) / (BAUD_RATE * 16UL)) - 1)
#elif (UART_SPEED_MODE == ASYNCHRONOUS_NORMAL_SPEED_MODE)
/* Macro responsible for calculate baud rate for Asynchronous DOUPLE SPEED Mode*/
#define ASYNCHRONOUS_DOUBLE_SPEED_MODE(F_CPU, BAUD_RATE) (((F_CPU) / (BAUD_RATE * 8UL)) - 1)
#endif
/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
/* Description : responsible for UART Data Size */
typedef	enum
{
	FIVE_BITS,	SIX_BITS,	SEVEN_BITS, EIGHT_BITS,	RESERVED_ONE,	RESERVED_TWO, RESERVED_THREE, NINE_BITS
}UART_BitData;

/* Description : responsible for UART Parity bit value */
typedef	enum
{
	DISABLED,	RESERVED, EVEN_PARITY, ODD_PARITY
}UART_Parity;

/* Description : responsible for UART Stop Bit value */
typedef	enum
{
	ONE_BIT,	TWO_BIT
}UART_StopBit;

/* Description : responsible for UART Baud Rate value */
typedef	enum
{
	BD_2400 = 2400,
	BD_4800 = 4800,
	BD_9600 = 9600,
	BD_14400 = 14400,
	BD_19200 = 19200,
	BD_28800 = 28800,
	BD_38400 = 38400,
	BD_57600 = 57600,
	BD_76800 = 76800,
	BD_115200 = 115200,
	BD_230400 = 230400,
	BD_250000 = 250000,
	BD_500000 = 500000,
	BD_1000000 = 1000000
}UART_BaudRate;

/* Description : responsible for UART Select Mode */
typedef	enum
{
	ASYNCHRONOUS,	SYNCHRONOUS
}UART_SelectMode;

/* Description : responsible for UART speed mode */
typedef	enum
{
	ASYNCHRONOUS_NORMAL_SPEED,	ASYNCHRONOUS_DOUBLE_SPEED
}UART_SpeedMode;

typedef struct
{
	UART_BitData bit_data;
	UART_Parity parity;
	UART_StopBit stop_bit;
	UART_BaudRate baud_rate;
	UART_SelectMode select_mode;
	UART_SpeedMode speed_mode;

}UART_ConfigType;

/***************** UART Registers type structure declarations *******************/
typedef union
{
	uint16 TwoBytes;
	struct
	{
		uint8 RXB_Bits: 8;
		uint8 TXB_Bits: 8;
	}Bits;
}UART_UDR_Type;

typedef union
{
	uint8 Byte;
	struct
	{
		uint8 MPCM_Bit: 1;
		uint8 U2X_Bit: 1;
		uint8 PE_Bit: 1;
		uint8 DOR_Bit: 1;
		uint8 FE_Bit: 1;
		uint8 UDRE_Bit: 1;
		uint8 TXC_Bit: 1;
		uint8 RXC_Bit: 1;
	}Bits;
}UART_UCSRA_Type;

typedef union
{
	uint8 Byte;
	struct
	{
		uint8 TXB8_Bit:1;
		uint8 RXB8_Bit:1;
		uint8 UCSZ2_Bit:1;
		uint8 TXEN_Bit:1;
		uint8 RXEN_Bit:1;
		uint8 UDRIE_Bit:1;
		uint8 TXCIE_Bit:1;
		uint8 RXCIE_Bit:1;
	}Bits;
}UART_UCSRB_Type;

typedef union
{
	uint8 Byte;
	struct
	{
		uint8 UCPOL_Bit:1;
		uint8 USCZ0_Bit:1;
		uint8 USCZ1_Bit:1;
		uint8 USBS_Bit:1;
		uint8 UPM0_Bit:1;
		uint8 UPM1_Bit:1;
		uint8 UMSEL_Bit:1;
		uint8 URSEL_Bit:1;
	}Bits;
}UART_UCSRC_Type;

typedef union
{
	uint8 Byte;
	struct
	{
		uint8 UBRR_Bits:4;
		uint8 :1;
		uint8 :1;
		uint8 :1;
		uint8 URSEL_Bit:1;
	}Bits;
}UART_UBRRH_Type;

typedef union
{
	uint8 Byte;
}UART_UBRRL_Type;


/******************************************************************************/
typedef union {
	uint8 Byte;
	struct{
		uint8 C_Bit:1;
		uint8 Z_Bit:1;
		uint8 N_Bit:1;
		uint8 V_Bit:1;
		uint8 S_Bit:1;
		uint8 H_Bit:1;
		uint8 T_Bit:1;
		uint8 I_Bit:1;
	}Bits;
}SREG_Type;
/******************************************************************************/

/**************************** UART Registers Definitions ***********************/
#define UART_UCSRA_REG			(*(volatile UART_UCSRA_Type*)0x2B)
#define UART_UCSRB_REG			(*(volatile UART_UCSRB_Type*)(0x2A))

#define UART_UDR_REG			(*(volatile UART_UDR_Type*)0x2C)

#define UART_UCSRC_REG			(*(volatile UART_UCSRC_Type*)(0x40))
#define UART_UBRRH_REG			(*(volatile UART_UBRRH_Type *)(0x40))

#define UART_UBRRL_REG			(*(volatile UART_UBRRL_Type*)(0x29))
/*******************************************************************************/
#define S_REG      			(*(volatile SREG_Type*)0x5F)
/*******************************************************************************/


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(const UART_ConfigType * Config_Ptr);



/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);


/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); // Receive until #

#endif /* UART_H_ */

