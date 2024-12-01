/*
 * TIM2_reg.h
 *
 * Created: 9/10/2024 1:28:29 AM
 *  Author: mahmo
 */ 


#ifndef TIM2_REG_H_
#define TIM2_REG_H_

#define TCCR2_REG    *((volatile u8*)0x45)
#define TIMSK_REG    *((volatile u8*)0x59)
#define TCNT2_REG    *((volatile u8*)0x44)
#define TIFR_REG     *((volatile u8*)0x58)
#define OCR2_REG     *((volatile u8*)0x43)




#endif /* TIM2_REG_H_ */