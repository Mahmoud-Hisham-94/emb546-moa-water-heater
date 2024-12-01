/*
 * LED_prog.c
 *
 * Created: 8/10/2024 4:42:06 PM
 *  Author: mahmo
 */ 

#include "../../LIB/STD_TYPE.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "../../MCAL/DIO/DIO_reg.h"

void LED_voidON (u8 copy_u8port,u8 copy_u8pin)
{
	DIO_voidSetPinDir(u8 copy_u8port,u8 copy_u8pin,OUTPUT);
	DIO_voidSetPinVal(u8 copy_u8port,u8 copy_u8pin,HIGH);
}
void LED_voidOFF (u8 copy_u8port,u8 copy_u8pin);
void LED_voidToggle (u8 copy_u8port,u8 copy_u8pin);
