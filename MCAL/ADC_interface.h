 
/***************************************************************
       NAME    :ADC_interface.h
	   create  :3/4/2024 11:09:25 AM
	   version :_v1_
	   Author  :mahmoud elgohary
****************************************************************/

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_



#define ADC_LEFT_ADJUST  0
#define ADC_RIGTH_ADJUST 1


typedef enum{
    Free_Running_mode=0,
	Analog_Comparator,
	External_Interrupt_Request_0,
	Timer_Counter0_Compare_Match,
	Timer_Counter0_Overflow,
	Timer_Counter_Compare_Match_B,
	Timer_Counter1_Overflow,
	Timer_Counter1_Capture_Event,
	  
}Trigger_Source_t;

typedef enum{
	ADC_Prescaler2=1,
	ADC_Prescaler4,
	ADC_Prescaler8,
	ADC_Prescaler16,
	ADC_Prescaler32,
	ADC_Prescaler64,
	ADC_Prescaler128,
}ADC_Prescaler_t;

typedef enum{
	Vref_AREV,
	Vref_AVCC,
	Vref_256
}ADC_Vref_t;

typedef enum{
	ADC0=0,
	ADC1,
	ADC2,
	ADC3,
	ADC4,
	ADC5,
	ADC6,
	ADC7,
	ALL_Channel
}ADC_Channel_t;

/********************************************************************************************************************
extern const u16* const ADC_pu16_ArrayReadFreeRunningModed;
                                                             - pointer to array of 8 element to read 8 channel 
                                                             - channel 0   in ADC_pu16_ArrayReadFreeRunningModed[0]
													         - channel 1   in ADC_pu16_ArrayReadFreeRunningModed[1]
                                                             - channel 2   in ADC_pu16_ArrayReadFreeRunningModed[2]
                                                             - channel 3   in ADC_pu16_ArrayReadFreeRunningModed[3]
                                                                to channel 7


extern const u16* const ADC_pu16AutoTriggerRead; 
                                                      - pointer to u16 to read ADC in auto trigger mode
													  - *ADC_pu16AutoTriggerRead
***********************************************************************************************************************/

/******************************************************************************************************************************
* \Syntax			: void ADC_vInit(ADC_Prescaler_t Copy_enumPrescaler, ADC_Vref_t Copy_enumVoltRef  )
* \Description		: ADC Initialization to select Prescaler & Volt Ref & Disable interrupt & Disable Auto trigger
*                     & prebuild cofig to set way of store result in reg Left adjust or Right adjust
*
*
* \Sync\Async		: Synchronous
* \Reenrancy    	: None Reentrant
* \Parameters (in)	: @ Copy_enumPrescaler: Specified Prescaler
*                       This parameter can be One of  ADC_Prescaler_t Enum Values to Select Prescaler:
*                        @ ADC_Prescaler2   : prescaler 2
*                        @ ADC_Prescaler4   : prescaler 4 
*                        @ ADC_Prescaler8   : prescaler 8
*                        @ ADC_Prescaler16  : prescaler 16
*                        @ ADC_Prescaler32  : prescaler 32
*						 @ ADC_Prescaler64  : prescaler 64
*                        @ ADC_Prescaler128 : prescaler 128
*                     @ Copy_enumVoltRef: Specified the volt reference
*                       This parameter can be One of  ADC_Vref_t enum values:
*                        @ Vref_AREV:   Vref
*                        @ Vref_AVCC:   5   volt 
*                        @ Vref_256:   2.56 volt
*                        
* \Return value     : None
******************************************************************************************************************************/
void ADC_vInit(ADC_Prescaler_t Copy_enumPrescaler, ADC_Vref_t Copy_enumVoltRef  );




/******************************************************************************************************************************
* \Syntax			: u16 ADC_vReadDigitalValueSingleConversionBlocking(ADC_Channel_t Copy_enumChannel);
* \Description		: ADC Read channel just select channel & start conversion but it's function disable AutoTrigger 
*                     & busy wait until conversion end and return Value
*
*
* \Sync\Async		: Synchronous
* \Reenrancy    	: None Reentrant
* \Parameters (in)	: @ Copy_enumChannel: Specified channel
*                       This parameter can be One of  ADC_Channel_t Enum Values to Select channel:
*                        @ ADC0 : channel 0
*                        @ ADC1 : channel 1
*                        @ ADC2 : channel 2
*                        @ ADC3 : channel 3
*                        @ ADC4 : channel 4
*						 @ ADC5 : channel 5
*                        @ ADC6 : channel 6
*						 @ ADC7	  channel 7
*
* \Return value     : @ ADC Value and it u16
******************************************************************************************************************************/
u16 ADC_vReadDigitalValueSingleConversionBlocking(ADC_Channel_t Copy_enumChannel);




/******************************************************************************************************************************
* \Syntax			: void ADC_vStartSingleConversionNoBlocking(ADC_Channel_t Copy_enumChannel)
* \Description		: ADC Read channel no blocking when conversion finished the ADC_u8BinaryFlagConversionComplete is set 
*                     and can get it's value using function "ADC_vGetFlagConversionComplete" if it return 1 can read ADC value
*                     using "ADC_vGetValueAfterConversion" and it's func return value
*
* \Sync\Async		: ASynchronous
* \Reenrancy    	: None Reentrant
* \Parameters (in)	: @ Copy_enumChannel: Specified channel
*                       This parameter can be One of  ADC_Channel_t Enum Values to Select channel:
*                        @ ADC0 : channel 0
*                        @ ADC1 : channel 1
*                        @ ADC2 : channel 2
*                        @ ADC3 : channel 3
*                        @ ADC4 : channel 4
*						 @ ADC5 : channel 5
*                        @ ADC6 : channel 6
*						 @ ADC7 : channel 7
*
* \Return value     : None
******************************************************************************************************************************/
void ADC_vStartSingleConversionNoBlocking(ADC_Channel_t Copy_enumChannel);



/******************************************************************************************************************************
* \Syntax			: u8 ADC_vGetFlagConversionComplete(void)
* \Description		: use for check if the conversion is complete in normal mode or auto trigger mode or free running mode complete one cycle
*             
*
* \Sync\Async		: Synchronous
* \Reenrancy    	: Reentrant
* \Parameters (in)	: None
*
* \Return value     : one if conversion complete or zero if not. 
******************************************************************************************************************************/
u8 ADC_vGetFlagConversionComplete(void);


/******************************************************************************************************************************
* \Syntax			: u16 ADC_vGetValueAfterConversion(void)
* \Description		: use after check if the conversion is complete if finished this function will return ADC value if not will return last value
*
*
* \Sync\Async		: Synchronous
* \Reenrancy    	: none Reentrant
* \Parameters (in)	: None
*
* \Return value     : ADC Value
******************************************************************************************************************************/
u16 ADC_vGetValueAfterConversion(void);

/******************************************************************************************************************************
* \Syntax			: void ADC_vDisableAutoTrigger(void)
* \Description		: Disable Auto Trigger Mode
*
* \Sync\Async		: Synchronous
* \Reenrancy    	: None Reentrant
* \Parameters (in)	: None
*
* \Return value     : None
******************************************************************************************************************************/
void ADC_vDisableAutoTrigger(void);


/******************************************************************************************************************************
* \Syntax			: void ADC_vDisableInterrupt(void)
* \Description		: Disable Interrupt ADC Conversion Complete
*
* \Sync\Async		: Synchronous
* \Reenrancy    	: None Reentrant
* \Parameters (in)	: None
*
* \Return value     : None
******************************************************************************************************************************/
void ADC_vDisableInterrupt(void);

/******************************************************************************************************************************
* \Syntax			: void ADC_vEnableInterrupt(void)
* \Description		: Enable Interrupt ADC Conversion Complete 
*
* \Sync\Async		: Synchronous
* \Reenrancy    	: None Reentrant
* \Parameters (in)	: None
*
* \Return value     : None
******************************************************************************************************************************/
void ADC_vEnableInterrupt(void);

/******************************************************************************************************************************
* \Syntax			: void ADC_vEnableAutoTrigger(Trigger_Source_t Copy_enumTriggermode,ADC_Channel_t Copy_enumChannel)
* \Description		: ADC Enable auto trigger Before it select trigger source and select channel 
*                 
*
* \Sync\Async		: Synchronous
* \Reenrancy    	: None Reentrant
* \Parameters (in)	: @ Copy_enumTriggermode: Specified Trigger source
*                       This parameter can be One of  Trigger_Source_t Enum Values to Select mode:
*                        @ Free_Running_mode            
*                        @ Analog_Comparator            
*                        @ External_Interrupt_Request_0 
*                        @ Timer_Counter0_Compare_Match 
*                        @ Timer_Counter0_Overflow      
*						 @ Timer_Counter_Compare_Match_ 
*                        @ Timer_Counter1_Overflow      
*                        @ Timer_Counter1_Capture_Event 
*                     @ Copy_enumChannel: Specified the Channel in Auto Trigger mode
*                        This parameter can be One of  ADC_Channel_t Enum Values to Select channel:
*                         @ ADC0 : channel 0
*                         @ ADC1 : channel 1
*                         @ ADC2 : channel 2
*                         @ ADC3 : channel 3
*                         @ ADC4 : channel 4
*                         @ ADC5 : channel 5
*                         @ ADC6 : channel 6
*                         @ ADC7 : channel 7
*
* \Return value     : None
******************************************************************************************************************************/
void ADC_vEnableAutoTrigger(Trigger_Source_t Copy_enumTriggermode,ADC_Channel_t Copy_enumChannel); 


/******************************************************************************************************************************
* \Syntax			: void ADC_vFreeRunningModeInit(void)
* \Description		: start conversion and set ISR Function 
*                     Before use it's function make sure Enable Interrupt ADC Conversion Complete
*
* \Sync\Async		: Synchronous
* \Reenrancy    	: none Reentrant
* \Parameters (in)	: None
*
* \Return value     : ADC Value
******************************************************************************************************************************/
void ADC_vFreeRunningModeInit(void);//should enable interrupt after use this function


/******************************************************************************************************************************
* \Syntax			: void ADC_vAutoTriggerInit(void)
* \Description		: Set ISR Function
*                     Before use it's function make sure Enable Interrupt ADC Conversion Complete
*
* \Sync\Async		: Synchronous
* \Reenrancy    	: none Reentrant
* \Parameters (in)	: None
*
* \Return value     : ADC Value
******************************************************************************************************************************/
void ADC_vAutoTriggerInit(void);//should enable interrupt after use this function


/******************************************************************************************************************************
* \Syntax			: void ADC_vEnableADC(void)
* \Description		: Enable ADC peripheral
*
* \Sync\Async		: Synchronous
* \Reenrancy    	: None Reentrant
* \Parameters (in)	: None
*
* \Return value     : None
******************************************************************************************************************************/
void ADC_vEnableADC(void);

/******************************************************************************************************************************
* \Syntax			: void ADC_vDisableADC(void)
* \Description		: Disable ADC peripheral
*
* \Sync\Async		: Synchronous
* \Reenrancy    	: None Reentrant
* \Parameters (in)	: None
*
* \Return value     : None
******************************************************************************************************************************/
void ADC_vDisableADC(void);

/******************************************************************************************************************************
* \Syntax			: void ADC_vSetVoltReference(void)
* \Description		: Set Volt Ref
*                     If these bits are changed during a conversion, the change will not go in effect until this conversion is complete
*
* \Sync\Async		: Synchronous
* \Reenrancy    	: None Reentrant
* \Parameters (in)	: @ Copy_enumVoltRef: Specified the volt reference
*                       This parameter can be One of  ADC_Vref_t enum values:
*                        @ Vref_AREV:   Vref
*                        @ Vref_AVCC:   5   volt
*                        @ Vref_256:   2.56 volt
* \Return value     : None
******************************************************************************************************************************/
void ADC_vSetVoltReference(ADC_Vref_t copy_enumVref);


/******************************************************************************************************************************
* \Syntax			: void ADC_SetCallBack(void(*LocalPtr)(void))
* \Description		: To Set Function Do In ISR when conversion complete by Passing Address of Function
*                     can't use in free running mode or auto trigger or single conversion no blocking
*                     make sure enable interrupt conversion complete
*
* \Sync\Async		: Synchronous
* \Reenrancy    	: Reentrant
* \Parameters (in)	: @ LocalPtr: Specified The Address of Function that will do in ISR
*
* \Return value     : None
******************************************************************************************************************************/
void ADC_SetCallBack(void(*LocalPtr)(void));  //should enable interrupt after use this function



#endif