/*
 * TMR0_interface.h
 *
 * Created: 3/23/2024 2:07:51 PM
 *  Author: lenovo
 */ 


#ifndef TMR0_INTERFACE_H_
#define TMR0_INTERFACE_H_


typedef enum{
	TIMER0_STOP=0,
	TIMER0_SCALER_1,
	TIMER0_SCALER_8,
	TIMER0_SCALER_64,
	TIMER0_SCALER_256,
	TIMER0_SCALER_1024,
	EXTERNALl_FALLING,
	EXTERNAL_RISING
}Timer0Scaler_type;

typedef enum
{
	TIMER0_NORMAL_MODE=0,
	TIMER0_PHASECORRECT_MODE,
	TIMER0_CTC_MODE,
	TIMER0_FASTPWM_MODE

}Timer0Mode_type;


typedef enum
{
	OC0_DISCONNECTED=0,
	OC0_TOGGLE,
	OC0_NON_INVERTING,
	OC0_INVERTING

}OC0Mode_type;

typedef enum
{
	TMR0_NORMAL_OVER_FLOW=0,
	TMR0_NORMAL_COMPARE_MATCH
}TMR0_Interrupt_source_t;

#define TMR0_voidSetTimer0Value(Copy_u8Preload)           ((TCNT0)=(Copy_u8Preload))
#define TMR0_u8GetTime0()                                  (TCNT0)
 
void TIMER0_Init(Timer0Mode_type mode,Timer0Scaler_type scaler);

void TIMER0_OC0Mode(OC0Mode_type mode);

void TIMER0_OV_InterruptEnable(void);

void TIMER0_OV_InterruptDisable(void);

void TIMER0_OC_InterruptEnable(void);

void TIMER0_OC_InterruptDisable(void);

void TMR0_voidSetCallBack(TMR0_Interrupt_source_t copy_enumInterruptSource,void (*copy_ptr)(void) );



#endif /* TMR0_INTERFACE_H_ */