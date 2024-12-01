/*
 * TIM1_reg.h
 *
 * Created: 9/7/2024 4:11:26 PM
 *  Author: mahmo
 */ 


#ifndef TIM1_REG_H_
#define TIM1_REG_H_

#define  TCCR1A_REG			*((volatile u8*)0x4F)
#define  TCCR1B_REG			*((volatile u8*)0x4E)
#define  TCNT1_REG			*((volatile u16*)0x4C)
#define  OCR1A_REG			*((volatile u16*)0x4A)
#define  OCR1B_REG			*((volatile u16*)0x48)
#define  ICR1_REG			*((volatile u16*)0x46)
#define  TIMSK_REG			*((volatile u8*)0x59)
#define  TIFR_REG		    *((volatile u8*)0x58)



#endif /* TIM1_REG_H_ */