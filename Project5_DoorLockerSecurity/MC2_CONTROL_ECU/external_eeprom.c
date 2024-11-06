 /******************************************************************************
 * Module: External EEPROM
 * File Name: external_eeprom.c
 * Description: Source file for the External EEPROM driver
 * Author: Yousif Adel
 *******************************************************************************/
#include "external_eeprom.h"
#include "twi.h"

/*******************************************************************************
 *                      Functions Definitions                                   *
 *******************************************************************************/

uint8 EEPROM_writeByte(uint16 u16addr,uint8 u8data)
{
	/* 1. Send the Start Bit */
	TWI_start();
	if(TWI_getStatus() != TWI_START)	return ERROR;

    /* 2. Send the device address, we need to get A8 A9 A10 address bits from the
     * memory location address and R/W=0 (write) */
	TWI_writeByte((uint8) ((0xA0) | ((u16addr&0x7000)>>7)));
	if(TWI_getStatus() !=  TWI_MT_SLA_W_ACK)	return ERROR;

    /* 3. Send the required memory location address */
	TWI_writeByte((uint8) u16addr);
	if(TWI_getStatus() !=  TWI_MT_DATA_ACK)	return ERROR;

    /* 4. write byte to eeprom */
	TWI_writeByte(u8data);
	if(TWI_getStatus() !=  TWI_MT_DATA_ACK)	return ERROR;

    /* 5. Send the Stop Bit */
	TWI_stop();

	return SUCCESS;
}

uint8 EEPROM_readByte(uint16 u16addr,uint8 *u8data)
{
	/* 1. Send the Start Bit */
	TWI_start();
	if(TWI_getStatus() != TWI_START)	return ERROR;

    /* 2. Send the device address, we need to get A8 A9 A10 address bits from the
     * memory location address and R/W=0 (write) */
	TWI_writeByte((uint8) ((0xA0) | ((u16addr&0x7000)>>7)));
	if(TWI_getStatus() !=  TWI_MT_SLA_W_ACK)	return ERROR;

    /* 3. Send the required memory location address */
	TWI_writeByte((uint8) u16addr);
	if(TWI_getStatus() !=  TWI_MT_DATA_ACK)	return ERROR;

	/* 4. Send the Repeated Start Bit */
	TWI_start();
	if(TWI_getStatus() != TWI_REP_START)	return ERROR;


    /* 5. Send the device address, we need to get A8 A9 A10 address bits from the
     * memory location address and R/W=1 (read) */
	TWI_writeByte((uint8) ((0xA0) | (((u16addr&0x7000)>>7) | 1)));
	if(TWI_getStatus() !=  TWI_MT_SLA_R_ACK)	return ERROR;

    /* 6. Read Byte from Memory without send ACK */
	*u8data = TWI_readByteWithNACK();
	if(TWI_getStatus() !=  TWI_MR_DATA_NACK)	return ERROR;

    /* 7. Send the Stop Bit */
	TWI_stop();

	return SUCCESS;
}
