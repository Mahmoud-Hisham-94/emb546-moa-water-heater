/*
 * SPI_interface.h
 *
 * Created: 9/21/2024 4:25:42 PM
 *  Author: AMIT
 */ 


#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_

#define  _Fosc4_PRESCALER      0x00
#define  _Fosc16_PRESCALER     0x01
#define  _Fosc64_PRESCALER     0x02
#define  _Fosc128_PRESCALER    0x03
#define  _Fosc2_PRESCALER      0x04
#define  _Fosc8_PRESCALER      0x05
#define  _Fosc32_PRESCALER     0x06
#define  _FosC64_PRESCALER     0x07

#define   SPI_PRESCALER       _Fosc128_PRESCALER


#define   SPI_PORT        DIO_PORTB
#define   MOSI_PIN        DIO_PIN5
#define   MISO_PIN        DIO_PIN6
#define   SS_PIN          DIO_PIN4
#define   CLK_PIN         DIO_PIN7 





void SPI_voidMasterInit(void) ; 
void SPI_voidSlaveInit(void) ;
void SPI_voidMasterSendData( u8 copy_u8data) ;
u8 SPI_u8SlaveReciveData() ; 




#endif /* SPI_INTERFACE_H_ */