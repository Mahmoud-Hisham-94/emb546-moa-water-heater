/*
 * TIM0_prog.c
 *
 * Created: 9/6/2024 4:34:53 PM
 *  Author: AMIT
 */ 
#include "../../LIB/BIT_MATH.h" 
#include "../../LIB/STD_TYPE.h"
#include "../../LIB/interrupt_vector.h"
#include "TIM0_reg.h" 
#include "TIM0_interface.h" 


void (*TIM0_PTR[2])(void)={null} ; 


void TIM0_voidInitCTC_OV( u8 copy_u8mode){
	
	
	/*  set prescaler */
	
	TCCR0_REG&=0b11111000 ;
	
	TCCR0_REG|=TIM0_PRESCALER ;
	
	
	
	 if(copy_u8mode==OV_MODE){
		 
		 /*select mode : normal mode */
		 CLR_BIT(TCCR0_REG,3) ;
		 CLR_BIT(TCCR0_REG,6) ;
		 
		 
		 /*enable  timer0 overflow interrupt */
		 SET_BIT(TIMSK_REG,0) ;
	 }
	 else if (copy_u8mode==CTC_MODE)
	 {
		 
		   
		   /*select mode : normal mode */
		   SET_BIT(TCCR0_REG,3) ;
		   CLR_BIT(TCCR0_REG,6) ;
		   
		    
		    /*enable  timer0 CTC interrupt */
		    SET_BIT(TIMSK_REG,1) ;
			
			/* SET OCR VAL */
			
			OCR0_REG=Tim0_OCR_VAL ; 
		 
	 }

}

/*
0% ----> 100%
dc ----> Duty Cycle
*/

void TIM0_voidFastPWM (u8 copy_dc)
{
	/* Select Mode : Fast PWM Mode */
	SET_BIT(TCCR0_REG,3) ;
	SET_BIT(TCCR0_REG,6) ;
	
	/* Set Prescaler */
	TCCR0_REG&=0b11111000 ;
	TCCR0_REG|=TIM0_PRESCALER ;
	
	#if FASTPWMMODE == NONINVERTING_MODE
	SET_BIT(TCCR0_REG,5);
	CLR_BIT(TCCR0_REG,4);
	#elif FASTPWMMODE == INVERTING_MODE
	SET_BIT(TCCR0_REG,5);
	SET_BIT(TCCR0_REG,4);
	#endif

	OCR0_REG=copy_dc*2.56;

	
}



void TIM0_voidSetCallBack(void(*ptr)(void) , u8 interrupt_mode){
	
	
	 switch(interrupt_mode){
		 
		 case OV_MODE :  TIM0_PTR[0]=ptr ; break; 
		 case CTC_MODE : TIM0_PTR[1]=ptr ; break; 
		 
	 }
	
}




ISR(TIMER0_OVF){
	

	TIM0_PTR[0]() ; 
	
}


ISR(TIMER0_COMP){
	TIM0_PTR[1]() ; 
	
	
}