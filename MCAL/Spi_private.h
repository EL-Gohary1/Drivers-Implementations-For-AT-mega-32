

/***************************************************************
       NAME    :Spi_private.h
	   create  :3/5/2024 9:26:59 AM
	   version :_v1_
	   Author  :mahmoud elgohary
****************************************************************/

#ifndef SPI_PRIVATE_H_
#define SPI_PRIVATE_H_

/******************************************************************************************************************************
* \Syntax			: static void SPI_voidResieveNoBlocking(void);
* \Description		: private function called in ISR to update SPI_u8RxData is static global variable
*
*	
* \Sync\Async		: Synchronous
* \Reenrancy    	: Reentrant
* \Parameters (in)	: None
* \Return value     : None                                           
******************************************************************************************************************************/
static void SPI_voidResieveNoBlocking(void);

typedef struct{
	volatile u8 SPCR_REG;
	volatile u8	SPSR_REG;
	volatile u8	SPDR_REG;
	
}SPI_t;

#define SPI_REGS  ((volatile SPI_t *)0x2d)




#endif