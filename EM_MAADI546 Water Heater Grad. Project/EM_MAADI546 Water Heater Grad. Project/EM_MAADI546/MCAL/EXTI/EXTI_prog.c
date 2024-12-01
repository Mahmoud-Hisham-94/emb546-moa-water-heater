/*
 * EXTI_prog.c
 *
 * Created: 8/24/2024 4:22:03 PM
 *  Author: AMIT
 */ 
#include "../../LIB/STD_TYPE.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/INTERRUPT_VECTOR.h"
#include "EXTI_interface.h" 
#include "EXTI_reg.h" 

void (*INT_PTR[3])(void) = {null };

void EXTI_voidInit(u8 copy_u8interrupt, u8 copy_u8sense ){
	
	   switch(copy_u8interrupt){
		   
		   case _INT_0 :  
		                 if(copy_u8sense == LOW_LEVEL){
							 
							 CLR_BIT(MCUCR_REG,0) ; 
							 CLR_BIT(MCUCR_REG,1) ; 
						 }
						 else if (copy_u8sense==ANY_LOGICAL_CHANCH)
						 {
							  SET_BIT(MCUCR_REG,0) ;
							  CLR_BIT(MCUCR_REG,1) ;
						 }
						 else if (copy_u8sense ==FALLING_EDGE)
						 {
							  CLR_BIT(MCUCR_REG,0) ;
							  SET_BIT(MCUCR_REG,1) ;
						 }
						 else if (copy_u8sense==RISING_EDGE)
						 {
							  SET_BIT(MCUCR_REG,0) ;
							  SET_BIT(MCUCR_REG,1) ;
						 }
						 
						 else{
						 } break;
		   case _INT_1 :
		   if(copy_u8sense == LOW_LEVEL){
			   
			   CLR_BIT(MCUCR_REG,2) ;
			   CLR_BIT(MCUCR_REG,3) ;
		   }
		   else if (copy_u8sense==ANY_LOGICAL_CHANCH)
		   {
			   SET_BIT(MCUCR_REG,2) ;
			   CLR_BIT(MCUCR_REG,3) ;
		   }
		   else if (copy_u8sense ==FALLING_EDGE)
		   {
			   CLR_BIT(MCUCR_REG,2) ;
			   SET_BIT(MCUCR_REG,3) ;
		   }
		   else if (copy_u8sense==RISING_EDGE)
		   {
			   SET_BIT(MCUCR_REG,2) ;
			   SET_BIT(MCUCR_REG,3) ;
		   }
		   
		   else{
		   }
		   break ; 
		  case _INT_2 : 
		              if (copy_u8sense ==FALLING_EDGE)
		              {
						  CLR_BIT(MCUCSR_REG,6) ; 
		              }
					  else if (copy_u8sense==RISING_EDGE)
					  {
						  SET_BIT(MCUCSR_REG,6) ;
						  
					  }
		             break ; 
		   
	   }
	
	
	
	
}

void EXTI_voidSetCallBack(void (*ptr) (void) , u8 num) {
	if (num == _INT_0)
	{
		INT_PTR[0]=ptr;
	}
	if (num == _INT_1)
	{
		INT_PTR[1]=ptr;
	}
	if (num == _INT_2)
	{
		INT_PTR[2]=ptr;
	}
}

void EXT0_voidEnable(void) {
	
	SET_BIT(GICR_REG,6) ; 
	
}
void EXT0_voidDisable(void){
	
	CLR_BIT(GICR_REG,6) ;
	
}
void EXT1_voidEnable(void) {
	
	SET_BIT(GICR_REG,7) ;
	
}
void EXT1_voidDisable(void){
	
	CLR_BIT(GICR_REG,7) ;
	
}
void EXT2_voidEnable(void) {
	
	SET_BIT(GICR_REG,5) ;
	
}
void EXT2_voidDisable(void){
	
	CLR_BIT(GICR_REG,5) ;
	
}
ISR(INT_0)	{
	INT_PTR[0]();
}


ISR(INT_1)	{
	
	INT_PTR[1]() ;
}

ISR(INT_2)	{
	INT_PTR[2]() ;
}
