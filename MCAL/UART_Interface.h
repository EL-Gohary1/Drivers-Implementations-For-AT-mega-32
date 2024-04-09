/*
 * UART_Interface.h
 *
 * Created: 3/22/2024 10:19:27 AM
 *  Author: lenovo
 */ 


#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_



#define  FREQ_CPU  8000000


#if  FREQ_CPU  ==  8000000
typedef enum {
	UART_BAUDRATE_1200		=	(0x340),
	UART_BAUDRATE_2400		=	(0xcc),
	UART_BAUDRATE_4800		=	(0x67),
	UART_BAUDRATE_9600		=	(0x33),
	UART_BAUDRATE_19200		=	(0x19),
	UART_BAUDRATE_115200	=	(0x3)
}UART_BAUDRATE_t;

#elif FREQ_CPU ==   16000000
typedef enum {
	UART_BAUDRATE_1200		=	(0x340),
	UART_BAUDRATE_2400		=	(0x1A0),
	UART_BAUDRATE_4800		=	(0xCF),
	UART_BAUDRATE_9600		=	(0x67),
	UART_BAUDRATE_19200		=	(0x51),
	UART_BAUDRATE_115200	=	(0x8)
}UART_BAUDRATE_t;
#endif



void USART_vInit(UART_BAUDRATE_t copy_enumBaudRate);

void USART_vSendDataBlock(u8 copy_u8Data);

void USART_vSendDataNoBlock(u8 copy_u8Data);

void USART_vReceiveDataBlock(u8* copy_pu8Data);

void USART_vReceiveDataNoBlock( u8* copy_pu8Data);


void UART_TX_SetCallBack(void (*LocalFptr)(void));

void UART_RX_SetCallBack(void (*LocalFptr)(void));

void USART_vRX_InterruptEnable(void);

void USART_vRX_InterruptDisable(void);

void USART_vTX_InterruptEnable(void);

void USART_vTX_InterruptDisable(void);


#endif /* UART_INTERFACE_H_ */