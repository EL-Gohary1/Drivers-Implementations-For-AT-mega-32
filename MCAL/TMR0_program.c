/*
 * TMR0_program.c
 *
 * Created: 3/23/2024 2:08:31 PM
 *  Author: lenovo
 */ 
#include "Utils.h"
#include "StdType.h"
#include "Mem_Map32.h"
#include "TMR0_interface.h"
#include "TMR0_config.h"
#include "TMR0_private.h"


void TIMER0_Init(Timer0Mode_type mode,Timer0Scaler_type scaler)
{
	switch (mode)
	{
		case TIMER0_NORMAL_MODE:
		CLR_BIT(TCCR0,WGM00);
		CLR_BIT(TCCR0,WGM01);
		break;
		case TIMER0_PHASECORRECT_MODE:
		SET_BIT(TCCR0,WGM00);
		CLR_BIT(TCCR0,WGM01);
		break;
		case TIMER0_CTC_MODE:
		CLR_BIT(TCCR0,WGM00);
		SET_BIT(TCCR0,WGM01);
		break;
		case TIMER0_FASTPWM_MODE:
		SET_BIT(TCCR0,WGM00);
		SET_BIT(TCCR0,WGM01);
		break;
	}
	TCCR0&=0XF8;//0b11111000
	TCCR0|=scaler;
}

void TIMER0_OC0Mode(OC0Mode_type mode)
{
	switch (mode)
	{
		case OC0_DISCONNECTED:
		CLR_BIT(TCCR0,COM00);
		CLR_BIT(TCCR0,COM01);
		break;
		case OC0_TOGGLE:
		SET_BIT(TCCR0,COM00);
		CLR_BIT(TCCR0,COM01);
		break;
		case OC0_NON_INVERTING:
		CLR_BIT(TCCR0,COM00);
		SET_BIT(TCCR0,COM01);
		break;
		case OC0_INVERTING:
		SET_BIT(TCCR0,COM00);
		SET_BIT(TCCR0,COM01);
		break;
	}
}

void TIMER0_OV_InterruptEnable(void)
{
	SET_BIT(TIMSK,TOIE0);
}
void TIMER0_OV_InterruptDisable(void)
{
	CLR_BIT(TIMSK,TOIE0);
}
void TIMER0_OC_InterruptEnable(void)
{
	SET_BIT(TIMSK,OCIE0);
}
void TIMER0_OC_InterruptDisable(void)
{
	CLR_BIT(TIMSK,OCIE0);
}


/*************************Pointer to functions to be assigned to ISR*********************************/
static void (*PRV_pfunCallBackOVF)(void)=NULLPTR;
static void (*PRV_pfunCallBackOC)(void)=NULLPTR;
/******************************************************************************************/

void TMR0_voidSetCallBack(TMR0_Interrupt_source_t copy_enumInterruptSource,void (*copy_ptr)(void) )
{
	if (copy_ptr!=NULLPTR)
	{
		switch (copy_enumInterruptSource)
		{
			case TMR0_NORMAL_OVER_FLOW:
			PRV_pfunCallBackOVF=copy_ptr;
			break;
			case TMR0_NORMAL_COMPARE_MATCH:
			PRV_pfunCallBackOC=copy_ptr;
			break;
		}
	}
	else
	{
		//error state
	}
}

ISR(TIMER0_COMP_vect)
{
     if(PRV_pfunCallBackOC!=NULLPTR)
	{
		PRV_pfunCallBackOC();
	}
}

ISR(TIMER0_OVF_vect)
{
	if(PRV_pfunCallBackOVF!=NULLPTR)
	{
		PRV_pfunCallBackOVF();
	}
}

