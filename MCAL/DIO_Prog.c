
#include "Utils.h"
#include "StdType.h"
#include "Mem_Map32.h"
#include "DIO_interface.h"
#include "DIO_Private.h"

static void DIO_Initpin(DIO_Pin_type pin,DIO_PinMode_type mode)
{
	u8 pin_num=pin%8;
	DIO_Port_type port=pin/8;
	switch(mode)
	{
		case OUTPUT:
		switch(port)
		{
			case PA:
			SET_BIT(DDRA,pin_num);
			CLR_BIT(PORTA,pin_num);
			break;
			case PB:
			SET_BIT(DDRB,pin_num);
			CLR_BIT(PORTB,pin_num);
			break;
            case PC:
            SET_BIT(DDRC,pin_num);
            CLR_BIT(PORTC,pin_num);
            break;
			case PD:
			SET_BIT(DDRD,pin_num);
			CLR_BIT(PORTD,pin_num);
			break;			
		}
		break;
		case INFREE:
		switch(port)
		{
			case PA:
			CLR_BIT(DDRA,pin_num);
			CLR_BIT(PORTA,pin_num);
			break;
			case PB:
			CLR_BIT(DDRB,pin_num);
			CLR_BIT(PORTB,pin_num);
			break;
			case PC:
			CLR_BIT(DDRC,pin_num);
			CLR_BIT(PORTC,pin_num);
			break;
			case PD:
			CLR_BIT(DDRD,pin_num);
			CLR_BIT(PORTD,pin_num);
			break;
		}
		break;
		case INPULL:
		switch(port)
		{
			case PA:
			CLR_BIT(DDRA,pin_num);
			SET_BIT(PORTA,pin_num);
			break;
			case PB:
			CLR_BIT(DDRB,pin_num);
			SET_BIT(PORTB,pin_num);
			break;
			case PC:
			CLR_BIT(DDRC,pin_num);
			SET_BIT(PORTC,pin_num);
			break;
			case PD:
			CLR_BIT(DDRD,pin_num);
			SET_BIT(PORTD,pin_num);
			break;
		}
		break;
	}
	
}


void DIO_WritePin(DIO_Pin_type pin,DIO_PinVoltage_type volt)
{
	u8 pin_num=pin%8;
	DIO_Port_type port=pin/8;
	switch (volt)
	{
		case LOW:
		switch (port)
		{
			case PA:
			CLR_BIT(PORTA,pin_num);
			break;
			case PB:
			CLR_BIT(PORTB,pin_num);
			break;
			case PC:
			CLR_BIT(PORTC,pin_num);
			break;
			case PD:
			CLR_BIT(PORTD,pin_num);
			break;
		}
		break;
		case HIGH:
		switch (port)
		{
			case PA:
			SET_BIT(PORTA,pin_num);
			break;
			case PB:
			SET_BIT(PORTB,pin_num);
			break;
			case PC:
			SET_BIT(PORTC,pin_num);
			break;
			case PD:
			SET_BIT(PORTD,pin_num);
			break;
		}
	}
}

DIO_PinVoltage_type DIO_ReadPin(DIO_Pin_type pin)
{
	u8 pin_num=pin%8;
	DIO_Port_type port=pin/8;
	DIO_PinVoltage_type volt=LOW;
	switch (port)
	{
		case PA:
		volt=READ_BIT(PINA,pin_num);
		break;
		case PB:
		volt=READ_BIT(PINB,pin_num);
		break;
		case PC:
		volt=READ_BIT(PINC,pin_num);
		break;
		case PD:
		volt=READ_BIT(PIND,pin_num);
		break;
	}
	return volt; 
}


void DIO_Init(void)
{
	DIO_Pin_type Pin;
	for(Pin=0;Pin<TOTAL_PINS;Pin++)
	{
		DIO_Initpin(Pin,PinsModeArray[Pin]);
	}
}

extern void DIO_WritePort(DIO_Port_type port,u8 value)
{
	switch (port)
	{
		case PA:
		PINA=value;
		break;
		case PB:
		PINB=value;
		break;
		case PC:
		PINC=value;
		break;
		case PD:
		PIND=value;
		break;
	}
}

extern void DIO_TogglePin(DIO_Pin_type pin)
{
	u8 pin_num=pin%8;
	DIO_Port_type port=pin/8;
	switch (port)
	{
		case PA:
		TOG_BIT(PORTA,pin_num);
		break;
		case PB:
		TOG_BIT(PORTB,pin_num);
		break;
		case PC:
		TOG_BIT(PORTC,pin_num);
		break;
		case PD:
		TOG_BIT(PORTD,pin_num);
		break;
	}
	
}