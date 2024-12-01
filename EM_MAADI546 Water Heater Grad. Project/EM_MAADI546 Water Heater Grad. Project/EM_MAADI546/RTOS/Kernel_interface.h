/*
 * Kernel_interface.h
 *
 * Created: 10/4/2024 5:15:55 PM
 *  Author: AMIT
 */ 


#ifndef KERNEL_INTERFACE_H_
#define KERNEL_INTERFACE_H_


typedef struct {
	
	   void(*ptr_fun)(void) ; 
	   u16 periodicity;
	    u8 task_state ;
	}Task_type;
	
	

void Kernel_voidCreatTask(void(*ptr)(void),u16 periodicity , u8 priority) ; 

void Kernel_voidStart(void) ; 
	
	
void Kernel_voidDeleteTask(u8 priority) ; 
void Kernel_voidSuspend(u8 priority) ; 
void Kernel_voidResume(u8 priority) ;

	
	
	
#define  RESUME    0 
#define  SUSPEND   1 	
	
#define  TASK_NUM    3 	







#endif /* KERNEL_INTERFACE_H_ */