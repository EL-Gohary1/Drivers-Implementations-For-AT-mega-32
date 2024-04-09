/*
 * WatchDog_interface.h
 *
 * Created: 3/19/2024 10:29:21 AM
 *  Author: lenovo
 */ 


#ifndef WATCHDOG_INTERFACE_H_
#define WATCHDOG_INTERFACE_H_

typedef enum{
	timeout_16ms=0,
	timeout_32ms,
	timeout_65ms,
	timeout_130ms,
	timeout_260ms,
	timeout_520ms,
	timeout_1000ms,
	timeout_2100ms,
}TimeOut_t;


void WDT_voidEnable(TimeOut_t copy_enumTime);

void WDT_voidDisable(void);




#endif /* WATCHDOG_INTERFACE_H_ */