/*
 * EEPROM_interface.h
 *
 * Created: 9/28/2024 3:43:53 PM
 *  Author: mahmo
 */ 


#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_

void EEPROM_voidSendDataToEEPROM ( u16 copy_u16address, u8 copy_u8data );

u8 EEPROM_voidRecieveDataFromEEPROM( u16 copy_u16address );



#endif /* EEPROM_INTERFACE_H_ */