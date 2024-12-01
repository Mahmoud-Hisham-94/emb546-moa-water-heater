/*
 * SSD_prog.c
 *
 * Created: 8/10/2024 5:16:58 PM
 *  Author: AMIT
 */ 
#include "../../LIB/BIT_MATH.h" 
#include "../../LIB/STD_TYPE.h" 
#include "../../MCAL/DIO/DIO_interface.h"
#include "SSD_config.h"


void SSD_voidDisplayNum(u8 copy_u8num){
	
	DIO_voidSetPortDir(SSD_PORT,0xf0) ;  // 11110000
	
	DIO_voidSetPortVal(SSD_PORT,copy_u8num<<4) ; 
	
	
}
