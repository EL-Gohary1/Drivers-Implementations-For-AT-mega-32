/*
 * UART_private.h
 *
 * Created: 3/22/2024 10:19:46 AM
 *  Author: lenovo
 */ 


#ifndef UART_PRIVATE_H_
#define UART_PRIVATE_H_


#define ONE_STOP  0
#define TWO_STOP  1

#define NO_PARITY    0
#define EVEN_PARITY  2
#define ODD_PARITY   3


#define UART_5_BIT_DATA				(0<<UCSZ0)
#define UART_6_BIT_DATA				(1<<UCSZ0)
#define UART_7_BIT_DATA				(2<<UCSZ0)
#define UART_8_BIT_DATA				(3<<UCSZ0)

#define UART_1_STOP_BIT				(0<<USBS)
#define UART_2_STOP_BIT				(1<<USBS)

#define UART_EVEN_PARITY			(2<<UPM0)
#define UART_ODD_PARITY				(3<<UPM0)
#define UART_NO_PARITY				(0<<UPM0)


#endif /* UART_PRIVATE_H_ */