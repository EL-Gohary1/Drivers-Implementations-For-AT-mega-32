/*
 * WatchDog_program.c
 *
 * Created: 3/19/2024 10:28:50 AM
 *  Author: lenovo
 */ 

#include "Utils.h"
#include "StdType.h"
#include "Mem_Map32.h"
#include "WatchDog_interface.h"
#include "WatchDog_private.h"


void WDT_voidEnable(TimeOut_t copy_enumTime)
{
	WDTCR&=0xf8;
	WDTCR=copy_enumTime;
	//Enable
	SET_BIT(WDTCR,WDE);
}


void WDT_voidDisable(void)
{
	WDTCR |= (1<<WDTOE) | (1<<WDE);
	
	WDTCR  = 0x00;
}