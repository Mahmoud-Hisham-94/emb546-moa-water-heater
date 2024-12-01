/*
 * TIM2_prog.c
 *
 * Created: 9/10/2024 1:28:47 AM
 *  Author: mahmo
 */ 

#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPE.h"
#include "../../LIB/interrupt_vector.h"
#include "TIM2_reg.h"
#include "TIM2_interface.h"


void (*TIM2_PTR[2])(void)={null} ;


void TIM2_voidInitCTC_OV( u8 copy_u8mode){
	
	
	/*  set prescaler */
	
	TCCR2_REG&=0b11111000 ;
	
	TCCR2_REG|=TIM2_PRESCALER ;
	
	
	
	if(copy_u8mode==OV_MODE){
		
		/*select mode : normal mode */
		CLR_BIT(TCCR2_REG,3) ;
		CLR_BIT(TCCR2_REG,6) ;
		
		
		/*enable  timer2 overflow interrupt */
		SET_BIT(TIMSK_REG,6) ;
	}
	else if (copy_u8mode==CTC_MODE)
	{
		
		
		/*select mode : normal mode */
		SET_BIT(TCCR2_REG,3) ;
		CLR_BIT(TCCR2_REG,6) ;
		
		
		/*enable  timer2 CTC interrupt */
		SET_BIT(TIMSK_REG,7) ;
		
		/* SET OCR VAL */
		
		OCR2_REG=Tim2_OCR_VAL ;
		
	}

}

/*
0% ----> 100%
dc ----> Duty Cycle
*/

void TIM2_voidFastPWM (u8 copy_dc)
{
	/* Select Mode : Fast PWM Mode */
	SET_BIT(TCCR2_REG,3) ;
	SET_BIT(TCCR2_REG,6) ;
	
	/* Set Prescaler */
	TCCR2_REG&=0b11111000 ;
	TCCR2_REG|=TIM2_PRESCALER ;
	
	#if FASTPWMMODE == NONINVERTING_MODE
	SET_BIT(TCCR2_REG,5);
	CLR_BIT(TCCR2_REG,4);
	#elif FASTPWMMODE == INVERTING_MODE
	SET_BIT(TCCR2_REG,5);
	SET_BIT(TCCR2_REG,4);
	#endif
	OCR2_REG=copy_dc*2.56;
	
}



void TIM2_voidSetCallBack(void(*ptr)(void) , u8 interrupt_mode){
	
	
	switch(interrupt_mode){
		
		case OV_MODE :  TIM2_PTR[0]=ptr ; break;
		case CTC_MODE : TIM2_PTR[1]=ptr ; break;
		
	}
	
}




ISR(TIMER2_OVF){
	

	TIM2_PTR[0]() ;
	
}


ISR(TIMER2_COMP){
	TIM2_PTR[1]() ;
	
	
}