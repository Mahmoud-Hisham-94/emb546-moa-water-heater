/*
 * TIM1_interface.h
 *
 * Created: 9/7/2024 4:16:16 PM
 *  Author: AMIT
 */ 


#ifndef TIM1_INTERFACE_H_
#define TIM1_INTERFACE_H_


/* select prescaler */

#define  NO_PRESCALER      0x01
#define  _8_PRESCALER      0x02
#define  _64_PRESCALER     0x03
#define  _256_PRESCALER    0x04
#define  _1024_PRESCALER   0x05

#define TIM1_PRESCALER      _64_PRESCALER





#define  OC1A_PIN      0 
#define  OC1B_PIN      1 



void TIMER1_voidFastPWM10BitRes(u8 copy_u8_pin , u8 copy_u8_duty) ; 


#endif /* TIM1_INTERFACE_H_ */