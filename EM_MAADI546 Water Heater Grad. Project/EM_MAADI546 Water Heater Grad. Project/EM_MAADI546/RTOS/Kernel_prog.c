/*
 * Kernel_prog.c
 *
 * Created: 10/4/2024 5:15:40 PM
 *  Author: AMIT
 */ 

#include "../LIB/BIT_MATH.h"
#include "../LIB/STD_TYPE.h"
#include "../MCAL/TIM0/TIM0_interface.h"
#include "Kernel_interface.h"


Task_type TASK_ARR[TASK_NUM]={{0}} ; 
	


void Kernel_voidCreatTask(void(*ptr)(void),u16 periodicity , u8 priority){
	
	   if (TASK_ARR[priority].ptr_fun == 0)
	   {
		   TASK_ARR[priority].ptr_fun=ptr ;
		   TASK_ARR[priority].periodicity=periodicity ;
		   TASK_ARR[priority].task_state=RESUME ; 
	   }
	    
	
	
}

void Kernel_voidALU(void){
	
	   static u16 count=0 ; 
	   count++ ; 
	   
	   u8 loc_in=0 ; 
	   for (loc_in=0 ; loc_in<TASK_NUM ;loc_in++)
	   {
		   
		   if (count % TASK_ARR[loc_in].periodicity==0)
		   {
			    if (TASK_ARR[loc_in].ptr_fun !=0  && TASK_ARR[loc_in].task_state==RESUME)
			    {
					   //call
					   TASK_ARR[loc_in].ptr_fun() ;
			    }
			 
		   }
		   
		   
		   
	   }
	
	
	
	
}




void Kernel_voidStart(void){
	
	TIM0_voidInitCTC_OV(CTC_MODE) ; 
	TIM0_voidSetCallBack(Kernel_voidALU,CTC_MODE) ; 
	
}


	
void Kernel_voidDeleteTask(u8 priority){

 TASK_ARR[priority].ptr_fun=0 ; 

	
}

void Kernel_voidSuspend(u8 priority) {
	
	 TASK_ARR[priority].task_state=SUSPEND ; 
	
	
}
void Kernel_voidResume(u8 priority) {
	
	 TASK_ARR[priority].task_state=RESUME ;
	 
}