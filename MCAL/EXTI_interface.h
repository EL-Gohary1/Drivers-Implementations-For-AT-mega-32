

/***************************************************************
       NAME    :EXTI_interface.h
	   create  :03/03/2024 1:25:25 PM
	   version :_v1_
	   Author  :mahmoud elgohary
****************************************************************/

#ifndef  EXTI_INTERFACE_H_
#define  EXTI_INTERFACE_H_



typedef enum{
	EX_INT0=0,
	EX_INT1,
	EX_INT2
}EXTINT_Source_t;


typedef enum{
	LOW_LEVEL=0,
	ANY_LOGIC_CHANGE,
	FALLING_EDGE,
	RISING_EDGE
}EXTI_senseControl_t;

/******************************************************************************************************************************
* \Syntax			: void EXINT_voidEnable(EXTINT_Source_t copy_enum_InterruptSrc, EXTI_senseControl_t copy_enum_SenseControl)
* \Description		: Enable External Interrupt by Passing External Interrupt source and Interrupt Sense Control
*
*	
* \Sync\Async		: Synchronous
* \Reenrancy    	: None Reentrant
* \Parameters (in)	: @ copy_enum_InterruptSrc: Specified the Exernal Interrupt to Enable 
*                       This parameter can be One of  EXTINT_Source_t Enum Values to Select Exernal Interrupt Number:
*                        @ EX_INT0: Exernal Interrupt Zero
*                        @ EX_INT1: Exernal Interrupt One
*                        @ EX_INT2: Exernal Interrupt Two
*                     @ copy_enum_SenseControl: Specified the  Interrupt Sense
*                       This parameter can be One of  EXTI_senseControl_t enum values:
*                        @ LOW_LEVEL:         The low level of INTX generates an interrupt request
*                        @ ANY_LOGIC_CHANGE:  Any logical change on INTX generates an interrupt request.
*                        @ FALLING_EDGE:      The falling edge of INTX generates an interrupt request
*                        @ RISING_EDGE:       The rising edge of INTX generates an interrupt request.
*                        For EXT_INT2 there is Two Sense Control mode 1)FALLING_EDGE 2)RISING_EDGE
* \Return value     : None                                           
******************************************************************************************************************************/
void EXINT_voidEnable(EXTINT_Source_t copy_enum_InterruptSrc, EXTI_senseControl_t copy_enum_SenseControl);

/******************************************************************************************************************************
* \Syntax			: void EXINT_voidDisable(EXTINT_Source_t copy_enum_InterruptSrc)
* \Description		: Disable External Interrupt by Passing External Interrupt source
*
*	
* \Sync\Async		: Synchronous
* \Reenrancy    	: None Reentrant
* \Parameters (in)	: @ copy_enum_InterruptSrc: Specified the Exernal Interrupt to Enable 
*                       This parameter can be One of  EXTINT_Source_t Enum Values to Select Exernal Interrupt Number:
*                        @ EX_INT0: Exernal Interrupt Zero
*                        @ EX_INT1: Exernal Interrupt One
*                        @ EX_INT2: Exernal Interrupt Two
* \Return value     : None                                           
******************************************************************************************************************************/
void EXINT_voidDisable(EXTINT_Source_t copy_enum_InterruptSrc);

/******************************************************************************************************************************
* \Syntax			: void EXI_voidSetCallBack(EXTINT_Source_t copy_enum_InterruptSrc,void(*LocalPtr)(void))
* \Description		: To Set Function Do In ISR by Passing External Interrupt Source and Address of Function
*
*	
* \Sync\Async		: Synchronous
* \Reenrancy    	: Reentrant
* \Parameters (in)	: @ copy_enum_InterruptSrc: Specified the Exernal Interrupt to Enable 
*                       This parameter can be One of  EXTINT_Source_t Enum Values to Select Exernal Interrupt Number:
*                        @ EX_INT0: Exernal Interrupt Zero
*                        @ EX_INT1: Exernal Interrupt One
*                        @ EX_INT2: Exernal Interrupt Two
*                     @ LocalPtr: Specified The Address of Function that will do in ISR           
* \Return value     : None                                           
******************************************************************************************************************************/
void EXI_voidSetCallBack(EXTINT_Source_t copy_enum_InterruptSrc,void(*LocalPtr)(void));


#endif
