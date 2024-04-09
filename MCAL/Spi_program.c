

 /***************************************************************
       NAME    :Spi_program.h
	   create  :3/5/2024 9:25:15 AM
	   version :_v1_
	   Author  :mahmoud elgohary
****************************************************************/
#include "Utils.h"
#include "StdType.h"
#include "Mem_Map32.h"
#include "Spi_interface.h"
#include "Spi_private.h"
#include "Spi_config.h"


void SPI_voidInit(SPI_Mode_t Copy_enumMode)
{	
   if(Copy_enumMode==MASTER)
   {
	    //DISABLE INTERRUPT
	   	CLR_BIT(SPI_REGS->SPCR_REG,SPIE);
	    //DATA ORDER LSB
	    SET_BIT(SPI_REGS->SPCR_REG,DORD);
	    //MASTER
	    SET_BIT(SPI_REGS->SPCR_REG,MSTR);
	    //POLARITY
	    CLR_BIT(SPI_REGS->SPCR_REG,CPOL);
	    //PHASE
	    CLR_BIT(SPI_REGS->SPCR_REG,CPHA);
	    //PRESCALLER
    	SET_BIT(SPI_REGS->SPCR_REG,SPR0);
    	SET_BIT(SPI_REGS->SPCR_REG,SPR1);
    	CLR_BIT(SPI_REGS->SPSR_REG,SPI2X);

    }
    else
    {
    	//DISABLE INTERRUPT
    	CLR_BIT(SPI_REGS->SPCR_REG,SPIE);
    	//DATA ORDER LSB
    	SET_BIT(SPI_REGS->SPCR_REG,DORD);
    	//SLAVE
    	CLR_BIT(SPI_REGS->SPCR_REG,MSTR);
    	//POLARITY
    	CLR_BIT(SPI_REGS->SPCR_REG,CPOL);
    	//PHASE 
    	CLR_BIT(SPI_REGS->SPCR_REG,CPHA);
    }
	
	//ENABLE SPI
	SET_BIT(SPI_REGS->SPCR_REG,SPE);
}

void SPI_voidTransieveBlocking(u8 Copy_u8TxData,u8* Copy_pu8RxData)
{
	if(Copy_pu8RxData!=NULLPTR)
	{
		SPI_REGS->SPDR_REG=Copy_u8TxData;
		while(READ_BIT(SPI_REGS->SPSR_REG,SPIF)==0);
		*Copy_pu8RxData=SPI_REGS->SPDR_REG;
	}
	else
	{
		//RETURN ERROR
	}
}


void SPI_voidTransieveNoBlocking(u8 Copy_u8TxData)
{
	//write data
	SPI_REGS->SPDR_REG=Copy_u8TxData;
}


static volatile u8 SPI_u8RxData;


volatile const u8* const SPI_pu8RxData=&SPI_u8RxData;



void SPI_voidEnableInterrupt(void)
{
	SET_BIT(SPI_REGS->SPCR_REG,SPIE);
}

void SPI_voidDisableInterrupt(void)
{
	CLR_BIT(SPI_REGS->SPCR_REG,SPIE);
}

static void SPI_voidResieveNoBlocking(void)
{
	SPI_u8RxData=SPI_REGS->SPDR_REG;
}

/****************************Pointer to functions to be assigned to ISR*********************************/
static void (*SPI_FPtrUser)(void)=NULLPTR;
/********************************************************************************************/

/************************************Call back functions*********************************************/
void SPI_voidSetCallBack(void(*Copy_FPtrUser)(void))
{
	SPI_FPtrUser=Copy_FPtrUser;
}
/*******************************************ISR*************************************************/
ISR(SPI_STC_vect)
{
	SPI_voidResieveNoBlocking();
	if(SPI_FPtrUser!=NULLPTR)
    {
		SPI_FPtrUser();
	}
}
/********************************************************************************************/

