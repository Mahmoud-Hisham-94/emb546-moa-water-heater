/*
 * LED_interface.h
 *
 * Created: 8/10/2024 4:41:52 PM
 *  Author: mahmo
 */ 
#include "DIO_interface.h"
#include "DIO_reg.h"


#ifndef LED_INTERFACE_H_
#define LED_INTERFACE_H_

void LED_voidON (u8 copy_u8port,u8 copy_u8pin);
void LED_voidOFF (u8 copy_u8port,u8 copy_u8pin);
void LED_voidToggle (u8 copy_u8port,u8 copy_u8pin);



#endif /* LED_INTERFACE_H_ */