

/***************************************************************
       NAME    :Spi_interface.h
	   create  :3/5/2024 9:24:03 AM
	   version :_v1_
	   Author  :mahmoud elgohary
****************************************************************/

#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_

/*
extern volatile const u8* const SPI_pu8RxData
   \note: by this pointer you can read data received and it updated in ISR
*/

typedef enum{
	MASTER,
	SLAVE
}SPI_Mode_t;

/******************************************************************************************************************************
* \Syntax			: void SPI_voidInit(SPI_Mode_t Copy_enumMode)
* \Description		: Initialization SPI by Passing SPI mode if Master or Slave note:this Function Disable interrupt && Send data from Least to Most
*                     && prescaller is 128 && Polarity and phase are zero  
*                     
* \Sync\Async		: Synchronous
* \Reenrancy    	: None Reentrant
* \Parameters (in)	: @ Copy_enumMode: Specified if the Microcrotroller is Slave or Master 
*                       This parameter can be One of  SPI_Mode_t Enum Values to Select Mode:
*                        @ MASTER :  Master Mode
*                        @ SLAVE  :  Slave Mode
* \Return value     : None                                           
******************************************************************************************************************************/
void SPI_voidInit(SPI_Mode_t Copy_enumMode);

/******************************************************************************************************************************
* \Syntax			: void SPI_voidTransieveBlocking(u8 Copy_u8TxData,u8* Copy_pu8RxData)
* \Description		: send data in Copy_u8TxData and receive data in Copy_pu8RxData
*
*	
* \Sync\Async		: Synchronous
* \Reenrancy    	: None Reentrant
* \Parameters (in)	: @ Copy_u8TxData: variable of 8 bit 
*                       This parameter can be 0 to 255:
*                     @ Copy_pu8RxData: pointer to unsigned number to store received data  
* \Return value     : None                                           
******************************************************************************************************************************/
void SPI_voidTransieveBlocking(u8 Copy_u8TxData,u8* Copy_pu8RxData);

/******************************************************************************************************************************
* \Syntax			: void SPI_voidSetCallBack(void(*Copy_FPtrUser)(void))
* \Description		: To Set Function Do In ISR by Passing Address of Function After recive data and update SPI_u8RxData
*
*	
* \Sync\Async		: Synchronous
* \Reenrancy    	: Reentrant
* \Parameters (in)	: @ Copy_FPtrUser: Specified The Address of Function that will do in ISR           
* \Return value     : None                                           
******************************************************************************************************************************/
void SPI_voidSetCallBack(void(*Copy_FPtrUser)(void));

/******************************************************************************************************************************
* \Syntax			: void SPI_voidTransieveNoBlocking(u8 Copy_u8TxData)
* \Description		: TO Send data Copy_u8TxData by write it in Specified Register you should make sure the spi is enabled && global interrupt && spi interrupt
*                     and the received data will be updated auto in ISR and read received data By pointer Called SPI_pu8RxData
*
*	
* \Sync\Async		: ASynchronous
* \Reenrancy    	: Reentrant
* \Parameters (in)	: @ Copy_u8TxData: This parameter is Data to send must be 8 bit 
* \Return value     : None                                           
******************************************************************************************************************************/
void SPI_voidTransieveNoBlocking(u8 Copy_u8TxData);

/******************************************************************************************************************************
* \Syntax			: void SPI_voidEnableInterrupt(void);
* \Description		: Enable SPI Interrupt to send interrupt request when transfer is complete
*
*	
* \Sync\Async		: Synchronous
* \Reenrancy    	: None Reentrant
* \Parameters (in)	: None
* \Return value     : None                                           
******************************************************************************************************************************/
void SPI_voidEnableInterrupt(void);

/******************************************************************************************************************************
* \Syntax			: void SPI_voidEnableInterrupt(void);
* \Description		: Disable SPI Interrupt
*
*	
* \Sync\Async		: Synchronous
* \Reenrancy    	: None Reentrant
* \Parameters (in)	: None
* \Return value     : None                                           
******************************************************************************************************************************/
void SPI_voidDisableInterrupt(void);



#endif