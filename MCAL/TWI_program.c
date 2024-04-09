/*
 * TWI_program.c
 *
 * Created: 3/15/2024 11:07:50 PM
 *  Author: Mahmoud EL-Gohary
 */ 


/* UTILES_LIB */
#include "StdType.h"
#include "Mem_Map32.h"
#include "Utils.h"

/* MCAL */
#include "TWI_interface.h"
#include "TWI_private.h"



void TWI_voidInitMaster(void)
{
	// Set Prescaller = 1 >> Set Freq. = 400KHZ
	TWBR = 12;
	CLR_BIT(TWSR, TWPS0);
	CLR_BIT(TWSR, TWPS1);
	
	// Enable TWI Peripheral
	SET_BIT(TWCR, TWEN);
}


void TWI_voidSendStartCondition(void)
{
	// Request Start Condition
	SET_BIT(TWCR, TWSTA);
	
	// Clear flag to start current job
	SET_BIT(TWCR, TWINT);
	
	// Busy Wait for the flag 
	while(0 == READ_BIT(TWCR, TWINT));
	
	// Check ACK = SC ACK
	while(TWI_STATUS_VALUE != TWI_START_CONDITION_ACK);
}


void TWI_voidSendRepeatedStartCondition(void)
{
	// Request Start Condition
	SET_BIT(TWCR, TWSTA);
	
	// Clear flag to start current job
	SET_BIT(TWCR, TWINT);
	
	// Busy Wait for the flag 
	while(0 == READ_BIT(TWCR, TWINT));
	
	// Check ACK = Repeated SC ACK
	while(TWI_STATUS_VALUE != TWI_REP_START_CONDITION_ACK);
}


void TWI_voidSendStopCondition(void)
{
	// Request Stop Condition
	SET_BIT(TWCR, TWSTO);
	
	// Clear flag to start current job
	SET_BIT(TWCR, TWINT);
}


void TWI_voidSendSlaveAddWithWrite(u8 copy_u8SlaveAdd)
{
	if(copy_u8SlaveAdd<128)
	{
		TWDR = (copy_u8SlaveAdd<<1);
		
		// Select write operation
		CLR_BIT(TWDR, 0);
		
		// Clear start condition bit
		CLR_BIT(TWCR, TWSTA);
		
		// Clear flag to start current job
	    SET_BIT(TWCR, TWINT);
		
		// Busy Wait for the flag 
	    while(0 == READ_BIT(TWCR, TWINT));
		
		// Check ACK = Master transmit ( slave address + Write request )
		while(TWI_STATUS_VALUE != TWI_SLAVE_ADDRESS_WRITE_ACK);
	}
	else
	{
		// return Error State
	}
}


void TWI_voidSendSlaveAddWithRead(u8 copy_u8SlaveAdd)
{
	if(copy_u8SlaveAdd<128)
	{
		TWDR = (copy_u8SlaveAdd<<1);
		
		// Select read operation
		SET_BIT(TWDR, 0);
		
		// Clear start condition bit
		CLR_BIT(TWCR, TWSTA);
		
		// Clear flag to start current job
	    SET_BIT(TWCR, TWINT);
		
		// Busy Wait for the flag 
	    while(0 == READ_BIT(TWCR, TWINT));
		
		// Check ACK = Master transmit ( slave address + read request ) 
		while(TWI_STATUS_VALUE != TWI_SLAVE_ADDRESS_READ_ACK);
	}
	else
	{
		// return Error State
	}
}


void TWI_voidTransmitMasterDataByte(u8 copy_u8TxData)
{
	// Write Data into data register
	TWDR = copy_u8TxData;
	
	// Clear flag to start current job
	SET_BIT(TWCR, TWINT);
	
	// Busy Wait for the flag 
	while(0 == READ_BIT(TWCR, TWINT));
	
	// Check ACK = Master transmit data ACK
	while(TWI_STATUS_VALUE != TWI_MASTER_DATA_TRANSMIT_ACK);
}


void TWI_voidReceiveMasterDataByteWithAck(u8* copy_pu8RxData)
{
	if(copy_pu8RxData!=NULL)
	{
		// Enable ACK
		SET_BIT(TWCR, TWEA);
		
		// Clear flag to start current job
	    SET_BIT(TWCR, TWINT);
		
		// Busy Wait for the flag 
	    while(0 == READ_BIT(TWCR, TWINT));
		
		// Check ACK = Master received data with ACK
		while(TWI_STATUS_VALUE != TWI_MASTER_DATA_RECIEVE_ACK);
		
		*copy_pu8RxData = TWDR;
		
		// Disable ACK
		CLR_BIT(TWCR, TWEA);
	}
	else
	{
		// return Error State
	}
}


void TWI_voidReceiveMasterDataByteWithNack(u8* copy_pu8RxData)
{
	if(copy_pu8RxData!=NULL)
	{
		// Clear flag to start current job
	    SET_BIT(TWCR, TWINT);
		
		// Busy Wait for the flag 
	    while(0 == READ_BIT(TWCR, TWINT));
		
		// Check ACK = Master received data with NACK
		while(TWI_STATUS_VALUE != TWI_MASTER_DATA_RECIEVE_NACK);
		
		*copy_pu8RxData = TWDR;
	}
	else
	{
		// return Error State
	}
}


