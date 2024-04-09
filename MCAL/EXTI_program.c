

/***************************************************************
       NAME    :EXTI_interface.h
	   create  :03/03/2024 1:25:25 PM
	   version :_v1_
	   Author  :mahmoud elgohary
****************************************************************/
#include "Utils.h"
#include "StdType.h"
#include "Mem_Map32.h"
#include "EXTI_interface.h"
#include "EXTI_Config.h"
#include "EXTI_Private.h"
   
void EXINT_voidEnable(EXTINT_Source_t copy_enum_InterruptSrc, EXTI_senseControl_t copy_enum_SenseControl)
{
	switch(copy_enum_InterruptSrc)
	{
		case EX_INT0:
		switch(copy_enum_SenseControl)
		{
			case LOW_LEVEL:
			CLR_BIT(MCUCR,ISC00);
			CLR_BIT(MCUCR,ISC00);
			break;
			case ANY_LOGIC_CHANGE:
			SET_BIT(MCUCR,ISC00);
			CLR_BIT(MCUCR,ISC01);
			break;
			case FALLING_EDGE:
			CLR_BIT(MCUCR,ISC00);
			SET_BIT(MCUCR,ISC01);
			break;
			case RISING_EDGE:
			SET_BIT(MCUCR,ISC00);
			SET_BIT(MCUCR,ISC01);
			break;
		}
		SET_BIT(GICR,INT0); //ENABLE
		break;
		case EX_INT1:
		switch(copy_enum_SenseControl)
		{
			case ANY_LOGIC_CHANGE:
			SET_BIT(MCUCR,ISC10);
			CLR_BIT(MCUCR,ISC11);
			break;
			case RISING_EDGE:
			SET_BIT(MCUCR,ISC10);
			SET_BIT(MCUCR,ISC11);
			break;
			case FALLING_EDGE:
			CLR_BIT(MCUCR,ISC10);
			SET_BIT(MCUCR,ISC11);
			break;
			case LOW_LEVEL:
			CLR_BIT(MCUCR,ISC10);
			CLR_BIT(MCUCR,ISC11);
			break;
		}
		SET_BIT(GICR,INT1); //ENABLE
		break;
		case EX_INT2:
		switch (copy_enum_SenseControl)
		{
			case FALLING_EDGE:
			CLR_BIT(MCUCR,ISC2);
			break;
			case RISING_EDGE:
			SET_BIT(MCUCR,ISC2);
			break;
			default:
			CLR_BIT(MCUCR,ISC2);
		}
		SET_BIT(GICR,INT2); //ENABLE
		break;
	}
}

void EXINT_voidDisable(EXTINT_Source_t copy_enum_InterruptSrc)
{
    	switch(copy_enum_InterruptSrc)
    	{
	    	case EX_INT0:
	    	CLR_BIT(GICR,INT0); //DISABLE
	    	break;
	    	case EX_INT1:
	    	CLR_BIT(GICR,INT1); //DISABLE
	    	break;
	    	case EX_INT2:
	    	CLR_BIT(GICR,INT2); //DISABLE
	    	break;
    	}
}

/****************************Pointer to functions to be assigned to ISR*********************************/

static void (*INT0_Fptr) (void)=NULLPTR;
static void (*INT1_Fptr) (void)=NULLPTR;
static void (*INT2_Fptr) (void)=NULLPTR;

/************************************Call back functions*********************************************/
void EXI_voidSetCallBack(EXTINT_Source_t copy_enum_InterruptSrc,void(*LocalPtr)(void))
{
	switch(copy_enum_InterruptSrc){
		case EX_INT0:
		INT0_Fptr=LocalPtr;
		break;
		case EX_INT1:
		INT1_Fptr=LocalPtr;
		break;
		case EX_INT2:
		INT2_Fptr=LocalPtr;
		break;
	}
}
/*******************************ISR********************************/
ISR(INT0_vect)
{
	if (INT0_Fptr!=NULLPTR)
	{
		INT0_Fptr();
	}
}
ISR(INT1_vect)
{
	if (INT1_Fptr!=NULLPTR)
	{
		INT1_Fptr();
	}
}
ISR(INT2_vect)
{
	if (INT2_Fptr!=NULLPTR)
	{
		INT2_Fptr();
	}
}