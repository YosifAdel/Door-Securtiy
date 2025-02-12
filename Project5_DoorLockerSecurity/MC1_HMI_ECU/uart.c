 /******************************************************************************
 * Module: UART
 * File Name: uart.c
 * Description: Source file for the AVR UART driver
 * Author: Yousif Adel
 *******************************************************************************/

#include	"uart.h"
#include 	"common_macros.h" /* To use the macros like SET_BIT */
#include	<avr/io.h>

/*******************************************************************************
 *                      Functions Definitions                                   *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(const UART_ConfigType * Config_Ptr)
{
	uint16 ubrr_value = 0;

	/************************** UCSRA Description ***************************/
	/* set the speed mode to the register whether it is normal or double speed */
	UART_UCSRA_REG.Bits.U2X_Bit = Config_Ptr->speed_mode;


	/************************** UCSRB Description ***************************/
	/* Enable Transmitter & receiver*/
	UART_UCSRB_REG.Bits.RXEN_Bit = 1;
	UART_UCSRB_REG.Bits.TXEN_Bit = 1;

	/* Set the third bits of the character size into the register UCSRC [UCSZ2] */
	UART_UCSRB_REG.Bits.UCSZ2_Bit = (((Config_Ptr->bit_data) & 0x04) >> 2);


	/************************** UCSRC Description ***************************/
	/* The URSEL must be one when writing the UCSRC */
	UART_UCSRC_REG.Bits.URSEL_Bit = 1;

	/* set the Select mode to the register whether it is synchronous or asynchronous */
	UART_UCSRC_REG.Bits.UMSEL_Bit = Config_Ptr->select_mode;

	/* set the Parity mode to the register*/
	UART_UCSRC_REG.Bits.UPM0_Bit = ((Config_Ptr->parity) & 0x01);
	UART_UCSRC_REG.Bits.UPM1_Bit = (((Config_Ptr->parity) & 0x02) >> 1);

	/* set the Stop Bit Select to the register*/
	UART_UCSRC_REG.Bits.USBS_Bit = Config_Ptr->stop_bit;

	/* Set the 2 bits of the character size into the register UCSRC [UCSZ0 UCSZ1]
	   - insert the required data bits in the second 2 bits (UCSZ1 , UCSZ0)of UCSRC Register
	 */
	UART_UCSRC_REG.Bits.USCZ0_Bit = ((Config_Ptr->bit_data) & 0x01);
	UART_UCSRC_REG.Bits.USCZ1_Bit = (((Config_Ptr->bit_data) & 0x02) >> 1);


	/* Calculate the UBRR register value */
#if (UART_SPEED_MODE == ASYNCHRONOUS_DOUBLE_SPEED_MODE)
	ubrr_value = (uint16)(((F_CPU / (Config_Ptr->baud_rate * 8UL))) - 1);
#elif (UART_SPEED_MODE == ASYNCHRONOUS_NORMAL_SPEED)
	ubrr_value = (uint16)(((F_CPU / (Config_Ptr->baud_rate * 16UL))) - 1);
#elif ((UART_SPEED_MODE != ASYNCHRONOUS_DOUBLE_SPEED_MODE) && (UART_SPEED_MODE != ASYNCHRONOUS_NORMAL_SPEED))
	/* Invalid speed setting, return */
	return;
#endif

	/* First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH*/
	UART_UBRRH_REG.Byte = ubrr_value>>8;
	UART_UBRRL_REG.Byte = ubrr_value;
}



/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data)
{
	/*
	 * UDRE flag is set when the Tx buffer (UDR) is empty and ready for
	 * transmitting a new byte so wait until this flag is set to one
	 */
	while(BIT_IS_CLEAR(UART_UCSRA_REG.Byte,UART_UCSRA_REG.Bits.UDRE_Bit)){}

	/*
	 * Put the required data in the UDR register and it also clear the UDRE flag as
	 * the UDR register is not empty now
	 */
	UART_UDR_REG.TwoBytes = data;

	/************************* Another Method *************************
	UDR = data;
	while(BIT_IS_CLEAR(UCSRA,TXC)){} // Wait until the transmission is complete TXC = 1
	SET_BIT(UCSRA,TXC); // Clear the TXC flag
	*******************************************************************/
}


/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void)
{
	/* RXC flag is set when the UART receive data so wait until this flag is set to one */
	while(BIT_IS_CLEAR(UART_UCSRA_REG.Byte,UART_UCSRA_REG.Bits.RXC_Bit)){}

	/*
	 * Read the received data from the Rx buffer (UDR)
	 * The RXC flag will be cleared after read the data
	 */
    return (uint8)UART_UDR_REG.TwoBytes;
}

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str)
{
	uint8 i = 0;

	/* Send the whole string */
	while(Str[i] != '\0')
	{
		UART_sendByte(Str[i]);
		i++;
	}

	/************************* Another Method *************************
	while(*Str != '\0')
	{
		UART_sendByte(*Str);
		Str++;
	}
	*******************************************************************/
}

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str)
{
	uint8 i = 0;

	/* Receive the first byte */
	Str[i] = UART_recieveByte();

	/* Receive the whole string until the '#' */
	while(Str[i] != '#')
	{
		i++;
		Str[i] = UART_recieveByte();
	}

	/* After receiving the whole string plus the '#', replace the '#' with '\0' */
	Str[i] = '\0';

}
