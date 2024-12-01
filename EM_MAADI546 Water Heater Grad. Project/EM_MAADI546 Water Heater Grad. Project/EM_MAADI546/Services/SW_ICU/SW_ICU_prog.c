/*
 * SW_ICU_prog.c
 *
 * Created: 9/14/2024 3:45:44 PM
 *  Author: AMIT
 */ 
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPE.h" 
#include "../../MCAL/EXTI/EXTI_interface.h"
#include "../../MCAL/TIM1/TIM1_interface.h"


/*ISR APP */

volatile u16 TP=0 ;
volatile u16 TON=0 ;

void SW_ICU_voidInit(){
	
	static u8 count=0 ;
	count++ ;
	if (count==1)
	{
		TIMER1_voidRest() ;
		EXTI_voidInit(_INT_0,FALLING_EDGE) ;
		
	}
	if (count==2)
	{
		TON=TIMER1_u16ReadVal() ;
		EXTI_voidInit(_INT_0,RISING_EDGE) ;
		
		
	}
	if (count==3)
	{
		TP=TIMER1_u16ReadVal() ;
		TIMER1_voidRest() ;
		count=0 ;
	}
	
	
	
}

