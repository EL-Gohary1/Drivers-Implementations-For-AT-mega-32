/*
 * UART_config.h
 *
 * Created: 3/22/2024 10:19:05 AM
 *  Author: lenovo
 */ 


#ifndef UART_CONFIG_H_
#define UART_CONFIG_H_
/*
 UART_1_STOP_BIT
 UART_2_STOP_BIT
*/
#define UART_NUM_STOP_BIT   UART_1_STOP_BIT

/*
UART_5_BIT_DATA
UART_6_BIT_DATA
UART_7_BIT_DATA
UART_8_BIT_DATA
*/
#define UART_NUM_BIT_DATA  UART_8_BIT_DATA   

/*
UART_EVEN_PARITY
UART_ODD_PARITY
UART_NO_PARITY
*/
#define UART_PARITY_Mode  UART_NO_PARITY


#endif /* UART_CONFIG_H_ */