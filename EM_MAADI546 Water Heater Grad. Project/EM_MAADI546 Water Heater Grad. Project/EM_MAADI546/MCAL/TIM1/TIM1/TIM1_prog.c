/*
 * TIM1_prog.c
 *
 * Created: 9/7/2024 4:16:51 PM
 *  Author: AMIT
 */ 
#include "../../LIB/BIT_MATH.h" 
#include "../../LIB/STD_TYPE.h" 
#include "TIM1_reg.h" 
#include "TIM1_interface.h"



void TIMER1_voidFastPWM10BitRes(u8 copy_u8_pin , u8 copy_u8_duty) {
	
	    /* select mode : 10 bit fast pwm */
	      SET_BIT(TCCR1A_REG,0) ; 
	      SET_BIT(TCCR1A_REG,1) ;
		  SET_BIT(TCCR1B_REG,3) ; 
		  CLR_BIT(TCCR1B_REG,4) ;
		/* SET prescaler */
		
	    TCCR1B_REG&=0b11111000 ; 
	    TCCR1B_REG|=TIM1_PRESCALER ; 		  
		/* select pin */ 
		
		switch(copy_u8_pin){
		
		
		  case OC1A_PIN : 
		                  /* select fastpwm mode : non inverting */
						  CLR_BIT(TCCR1A_REG,6) ; 
						  SET_BIT(TCCR1A_REG,7) ;   
						  
						   OCR1A_REG = copy_u8_duty*10.24 ; 
						  break ; 
						  
		  case OC1B_PIN :
		  	             /* select fastpwm mode : non inverting */
		  	             CLR_BIT(TCCR1A_REG,4) ;
		  	             SET_BIT(TCCR1A_REG,5) ;
		  	  
		  	         OCR1B_REG = copy_u8_duty*10.24 ; 
		  	  break ;
		}
		  
		  
	
	
}
