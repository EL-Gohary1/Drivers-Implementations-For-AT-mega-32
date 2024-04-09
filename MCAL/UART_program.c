/*
 * UART_program.c
 *
 * Created: 3/22/2024 10:18:03 AM
 *  Author: lenovo
 */ 
#include "StdType.h"
#include "Utils.h"
#include "Mem_Map32.h"
#include "UART_private.h"
#include "UART_Interface.h"
#include "UART_config.h"


void USART_vInit(UART_BAUDRATE_t copy_enumBaudRate)
{
	/* Set baud rate */
	UBRRL= (u8)copy_enumBaudRate;
	UBRRH= (u8)(copy_enumBaudRate>>8);
	
	//Set frame format
	UCSRC = ((1<< URSEL) | UART_NUM_STOP_BIT | UART_NUM_BIT_DATA | UART_PARITY_Mode);
	
	/* enable */
	SET_BIT(UCSRB,TXEN);
	SET_BIT(UCSRB,RXEN);
	
}

void USART_vSendDataBlock(u8 copy_u8Data)
{
    while(!READ_BIT(UCSRA,UDRE));
    UDR=copy_u8Data;
}

void USART_vReceiveDataBlock(u8* copy_pu8Data)
{
	if (copy_pu8Data!=NULLPTR)
	{
		while(!READ_BIT(UCSRA,RXC));
		*copy_pu8Data=UDR;
	}
}

void USART_vReceiveDataNoBlock(u8* copy_pu8Data)
{
	if (copy_pu8Data!=NULLPTR)
	{
			*copy_pu8Data=UDR;
	}
}

void USART_vSendDataNoBlock(u8 copy_u8data)
{
	UDR=copy_u8data;
}

/**********************************UART_Interrupt**************************************/
void USART_vRX_InterruptEnable(void)
{
SET_BIT(UCSRB,RXCIE);
}

void USART_vRX_InterruptDisable(void)
{
CLR_BIT(UCSRB,RXCIE);
}

void USART_vTX_InterruptEnable(void)
{
SET_BIT(UCSRB,TXCIE);
}

void USART_vTX_InterruptDisable(void)
{
CLR_BIT(UCSRB,TXCIE);
}

/**********************************Pointers******************************************/
static void (*UART_RX_Fptr) (void);
static void (*UART_TX_Fptr) (void);
/*********************************set call back functions***************************************/
void UART_RX_SetCallBack(void (*LocalFptr)(void))
{
	UART_RX_Fptr = LocalFptr;
}

void UART_TX_SetCallBack(void (*LocalFptr)(void))
{
	UART_TX_Fptr = LocalFptr;
}
/*********************************** ISR *************************************/
ISR(USART_RXC_vect)
{
	if (UART_RX_Fptr!=NULLPTR)
	{
		UART_RX_Fptr();
	}
}

ISR(USART_TXC_vect)
{
	if (UART_TX_Fptr!=NULLPTR)
	{
		UART_TX_Fptr();
	}
}


