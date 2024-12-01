/*
 * TIM1_prog.c
 *
 * Created: 9/7/2024 4:11:46 PM
 *  Author: mahmo
 */ 

#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPE.h"
#include "TIM1_reg.h"
#include "TIM1_interface.h"

void	TIMER1_voidFastPWM10BitRes(u8 copy_u8_Pin , u8 copy_u8_duty)
{
	/* select mode : 10 bit fast PWM */
	SET_BIT(TCCR1A_REG,0);
	SET_BIT(TCCR1A_REG,1);
	SET_BIT(TCCR1B_REG,3);
	CLR_BIT(TCCR1B_REG,4);
	
	/* Set Prescaler */
	TCCR1B_REG&=0b11111000 ;
	TCCR1B_REG|=TIM1_PRESCALER ;
	/* Select PIN */
	switch (copy_u8_Pin)
	{
		case OC1A_PIN :
		/* select fast PWM mode : non inverting */
		CLR_BIT(TCCR1A_REG,6);
		SET_BIT(TCCR1A_REG,7);
		OCR1A_REG = copy_u8_duty * 10.24 ;
		break;
		
		case OC1B_PIN :
		CLR_BIT(TCCR1A_REG,4);
		SET_BIT(TCCR1A_REG,5);
		OCR1B_REG = copy_u8_duty * 10.24 ;
		break;
		
	}
	
}

void TIMER1_voidFastPWMICR1 ( void )
{
	/*select mode : 10 bit fast PWM */

	CLR_BIT(TCCR1A_REG,0);
	SET_BIT(TCCR1A_REG,1);
	SET_BIT(TCCR1B_REG,3);
	SET_BIT(TCCR1B_REG,4);

	/*SET PRESCALER */

	TCCR1B_REG&=0b11111000 ;
	TCCR1B_REG|=TIM1_PRESCALER ;
	
	/* select fast PWM mode : non inverting */
	
	CLR_BIT(TCCR1A_REG,4);
	SET_BIT(TCCR1A_REG,5);
	
	/* SET ICR */

	ICR1_REG=40000;
	
}

void TIMER1_voidSetOCRVal ( u16 copy_u16val )
{
	/* 2000: 0  --> 4000: 180 */ /* 1000 --> 5100 */ 

	OCR1B_REG = ( (copy_u16val * ( 4100/180 )) + 1000 ) ;
}