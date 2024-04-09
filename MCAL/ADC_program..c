
 
/***************************************************************
       NAME    :ADC_program.h
	   create  :3/4/2024 11:09:25 AM
	   version :_v1_
	   Author  :Mahmoud El-gohary
****************************************************************/
#include "Utils.h"
#include "StdType.h"
#include "Mem_Map32.h"
#include "ADC_interface.h"
#include "ADC_config.h"
#include "ADC_Private.h"


/******************************************************************/
static volatile u16 ADC_u16ADCValue;                       //  is update by isr 
static volatile u8 ADC_u8BinaryFlagConversionComplete=0;   // in is set if auto trigger finished and cycle on free running finished and if asy normal finished
/******************************************************************/
static volatile u16 ADC_Arru16ADCReadFreeRunningMode[8]={0};
static volatile u16 ADC_u16AutoTriggerRead;

//   const  //
volatile const u16* const ADC_pu16AutoTriggerRead=&ADC_u16AutoTriggerRead;                     //extern
volatile const u16* const ADC_pu16_ArrayReadFreeRunningModed=ADC_Arru16ADCReadFreeRunningMode; //extern
/*******************************************************************/


void ADC_vInit(ADC_Prescaler_t Copy_enumPrescaler, ADC_Vref_t Copy_enumVoltRef )
{
		// clock
		ADCSRA=ADCSRA&0xf8;
		ADCSRA=ADCSRA|Copy_enumPrescaler;
		
		switch(Copy_enumVoltRef)
		{
			case Vref_AREV:
			CLR_BIT(ADMUX,REFS0);
			CLR_BIT(ADMUX,REFS1);
			break;
			case Vref_AVCC:
			SET_BIT(ADMUX,REFS0);
			CLR_BIT(ADMUX,REFS1);
			break;
			case Vref_256:
			SET_BIT(ADMUX,REFS0);
			SET_BIT(ADMUX,REFS1);
			break;
		}
		
		CLR_BIT(ADCSRA,ADIE);//Disable interrupt
		
		CLR_BIT(ADCSRA,ADATE);//Disable Auto trigger
		
		// way of store result in reg
		#if ADC_ADJUST_MODE ==  ADC_LEFT_ADJUST
		SET_BIT(ADMUX,ADLAR);  
		#else
		CLR_BIT(ADMUX,ADLAR);
		#endif
		
		SET_BIT(ADCSRA,ADEN);   //ADC enable
}

/****************************************************************************************************************************/

u16 ADC_vReadDigitalValueSingleConversionBlocking(ADC_Channel_t Copy_enumChannel)
{
	/* select channel*/
	ADMUX=ADMUX&0xE0;
	ADMUX=ADMUX|Copy_enumChannel;
	/*Disable Auto trigger*/
	CLR_BIT(ADCSRA,ADATE);
	/* start conversion*/
	SET_BIT(ADCSRA,ADSC);
	/* wait until conversion end*/
	while(READ_BIT(ADCSRA,ADSC));  //busy wait or blocking loop
	/* read register */
	CLR_BIT(ADCSRA,ADIF);//Clear flag interrupt
	return ADC;
}

/****************************************************************************************************************************/

 static void ADC_vReadDigitalValueSingleConversionNoBlockingInterrupt(void)
 {
	 ADC_u16ADCValue = ADC;
	 ADC_u8BinaryFlagConversionComplete=1;
 }
void ADC_vStartSingleConversionNoBlocking(ADC_Channel_t Copy_enumChannel)
{
	ADC_u8BinaryFlagConversionComplete=0;   //flag
	/* select channel*/
	ADMUX=ADMUX&0xE0;
	ADMUX=ADMUX|Copy_enumChannel;
	/*Disable Auto trigger*/
	CLR_BIT(ADCSRA,ADATE);
	/* start conversion*/
	SET_BIT(ADCSRA,ADSC);
	ADC_SetCallBack(ADC_vReadDigitalValueSingleConversionNoBlockingInterrupt);
}

/****************************************************************************************************************************/
 u8 ADC_vGetFlagConversionComplete(void)
 {
	 return ADC_u8BinaryFlagConversionComplete;
 }
/****************************************************************************************************************************/
 u16 ADC_vGetValueAfterConversion(void)
 {
	 return ADC_u16ADCValue;
 }
/****************************************************************************************************************************/
void ADC_vDisableAutoTrigger(void)
{
	CLR_BIT(ADCSRA,ADATE);//Disable Auto trigger
}
/****************************************************************************************************************************/
void ADC_vEnableInterrupt(void)
{
	/*Enable Interrupt conversion complete*/
	SET_BIT(ADCSRA,ADIE);
	//default global interrupt enable
}
/****************************************************************************************************************************/
void ADC_vDisableInterrupt(void)
{
	/*Disable Interrupt*/
	CLR_BIT(ADCSRA,ADIE);
}
/****************************************************************************************************************************/
 void ADC_vEnableADC(void)
 {
	 SET_BIT(ADCSRA,ADEN);   //ADC enable
 }
/****************************************************************************************************************************/
 void ADC_vDisableADC(void)
 {
	 CLR_BIT(ADCSRA,ADEN);   //ADC Disable
 }
/****************************************************************************************************************************/
 
 void ADC_vEnableAutoTrigger(Trigger_Source_t Copy_enumTriggermode,ADC_Channel_t Copy_enumChannel)
 {
	 if (Copy_enumChannel!=ALL_Channel)
	 {
		 /* select channel*/
		 ADMUX=ADMUX&0xE0;
		 ADMUX=ADMUX|Copy_enumChannel;
	 }

	 /*Select trigger source*/
	 SFIOR&=0x0F;
	 SFIOR|=Copy_enumTriggermode<<5;
	 
	 /*Enable Auto trigger*/
	 SET_BIT(ADCSRA,ADATE);
	 
 }
/****************************************************************************************************************************/
static void ADC_vFreeRunningModeORAutiTrigger(void)      //this fuction called in isr
{
	static volatile u8 ADC_u8CounterFlag=0;
	if ((SFIOR>>5)==0)
	{
		ADC_Arru16ADCReadFreeRunningMode[ADC_u8CounterFlag] =ADC;
		ADC_u8CounterFlag++;
		if (ADC_u8CounterFlag==8)
		{
			ADC_u8CounterFlag=0;
			ADC_u8BinaryFlagConversionComplete=1;
		}
	}
	else
	{
		ADC_u16AutoTriggerRead=ADC;
		ADC_u8BinaryFlagConversionComplete=1;
	}
}
void ADC_vFreeRunningModeInit(void)
{
	/* start conversion*/
	SET_BIT(ADCSRA,ADSC);
	ADC_SetCallBack(ADC_vFreeRunningModeORAutiTrigger);
}

/****************************************************************************************************************************/
void ADC_vAutoTriggerInit(void)
{
	ADC_SetCallBack(ADC_vFreeRunningModeORAutiTrigger);
}
/****************************************************************************************************************************/

void ADC_vSetVoltReference(ADC_Vref_t copy_enumVref)
{
    switch(copy_enumVref)
    {
    	case Vref_AREV:
    	CLR_BIT(ADMUX,REFS0);
    	CLR_BIT(ADMUX,REFS1);
    	break;
    	case Vref_AVCC:
    	SET_BIT(ADMUX,REFS0);
    	CLR_BIT(ADMUX,REFS1);
    	break;
    	case Vref_256:
    	SET_BIT(ADMUX,REFS0);
    	SET_BIT(ADMUX,REFS1);
    	break;
    }	
}

/****************************Pointer to functions to be assigned to ISR*********************************/

static void (*ADC_Fptr_AutoTrigger) (void)=NULLPTR;

/*******************************************************************************************************/

/************************************Call back functions***should be static or remove and assign in pointer to func direct *************************/
void ADC_SetCallBack(void(*LocalPtr)(void))
{
	if (LocalPtr!=NULLPTR)
	{
	     ADC_Fptr_AutoTrigger=LocalPtr;
	}
}
/***************************************************ISR*****************************************************/
ISR(ADC_vect)
{
	if (ADC_Fptr_AutoTrigger!=NULLPTR)
	{
		ADC_Fptr_AutoTrigger();
	}
}