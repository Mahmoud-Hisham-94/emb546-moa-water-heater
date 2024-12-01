/*
 * TIM2_interface.h
 *
 * Created: 9/10/2024 1:28:10 AM
 *  Author: mahmo
 */ 


#ifndef TIM2_INTERFACE_H_
#define TIM2_INTERFACE_H_

/* select prescaler */

#define  NO_PRESCALER      0x01
#define  _8_PRESCALER      0x02
#define  _64_PRESCALER     0x03
#define  _256_PRESCALER    0x04
#define  _1024_PRESCALER   0x05

#define TIM2_PRESCALER      _64_PRESCALER


/* TIMER MODE */

#define  OV_MODE      0
#define  CTC_MODE     1

/* FAST PWM MODE */
#define  INVERTING_MODE 0
#define  NONINVERTING_MODE 1
/* Select Fast PWM mode */
#define FASTPWMMODE     NONINVERTING_MODE

/* OCR VAL */

#define  Tim2_OCR_VAL   249

void TIM2_voidInitCTC_OV( u8 copy_u8mode);

void TIM2_voidFastPWM (u8 copy_dc);

void TIM2_voidSetCallBack(void(*ptr)(void) , u8 interrupt_mode) ;



#endif /* TIM2_INTERFACE_H_ */