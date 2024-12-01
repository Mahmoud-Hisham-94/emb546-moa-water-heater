/*
 * SPI_prog.c
 *
 * Created: 9/21/2024 4:26:05 PM
 *  Author: AMIT
 */ 
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPE.h" 
#include "../DIO/DIO_interface.h"
#include "SPI_interface.h"
#include "SPI_reg.h"




void SPI_voidMasterInit(void){
	
	 DIO_voidSetPinDir(SPI_PORT,MOSI_PIN,OUTPUT) ; 
	 DIO_voidSetPinDir(SPI_PORT,MISO_PIN,INPUT) ;
	 DIO_voidSetPinDir(SPI_PORT,CLK_PIN,OUTPUT) ;
	 DIO_voidSetPinDir(SPI_PORT,SS_PIN,OUTPUT) ;
	 
	 /* select spi clock */
	 SET_BIT(SPCR_REG,0) ; 
	 SET_BIT(SPCR_REG,1) ;
	 
	 
	/*select spi mode : master mode */
	SET_BIT(SPCR_REG,4) ; 

	/* enable spi*/
	SET_BIT(SPCR_REG,6) ; 
}
void SPI_voidSlaveInit(void){
	
	 DIO_voidSetPinDir(SPI_PORT,MOSI_PIN,INPUT) ;
	 DIO_voidSetPinDir(SPI_PORT,MISO_PIN,OUTPUT) ;
	 DIO_voidSetPinDir(SPI_PORT,CLK_PIN,INPUT) ;
	 DIO_voidSetPinDir(SPI_PORT,SS_PIN,INPUT) ;
	 
	 /*select spi mode : master mode */
	 CLR_BIT(SPCR_REG,4) ;

	 /* enable spi*/
	 SET_BIT(SPCR_REG,6) ;
	
}
void SPI_voidMasterSendData( u8 copy_u8data) {
	
	SPDR_REG=copy_u8data ; 
	while(GET_BIT(SPSR_REG,7)==0) ; 
	
}
u8 SPI_u8SlaveReciveData(){
	
	
	
	while(GET_BIT(SPSR_REG,7)==0) ;
       return SPDR_REG ; 
}
