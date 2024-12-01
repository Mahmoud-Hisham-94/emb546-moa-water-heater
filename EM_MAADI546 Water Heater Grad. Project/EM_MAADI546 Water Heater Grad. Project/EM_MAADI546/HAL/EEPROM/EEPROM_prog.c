/*
 * EXTEP_prog.c
 *
 * Created: 9/28/2024 3:42:36 PM
 *  Author: mahmo
 */ 

#include "../../LIB/STD_TYPE.h"
#include "../../MCAL/TWI/TWI_interface.h"
#define F_CPU 16000000UL
#include <util/delay.h>

void EEPROM_voidSendDataToEEPROM ( u16 copy_u16address, u8 copy_u8data )
{
	u8 DeviceAddress = (0b01010000 | (copy_u16address>>8));
	TWI_TWI_statusStartCondition();
	TWI_TWI_statusSendSlaveAdressWithWrite(DeviceAddress);
	TWI_TWI_statusMasterSendData((u8)copy_u16address);
	TWI_TWI_statusMasterSendData(copy_u8data);
	TWI_voidStopCondition();
	_delay_ms(5);
}

u8 EEPROM_voidRecieveDataFromEEPROM( u16 copy_u16address )
{
	u8 loc_u8data;
	u8 DeviceAddress = (0b01010000 | (copy_u16address>>8));
	TWI_TWI_statusStartCondition();
	TWI_TWI_statusSendSlaveAdressWithWrite(DeviceAddress);
	TWI_TWI_statusMasterSendData((u8)copy_u16address);
	TWI_TWI_statusRepeatedStart();
	TWI_TWI_statusSendSlaveAdressWithRead(DeviceAddress);
	TWI_TWI_statusMasterReciveData(&loc_u8data);
	TWI_voidStopCondition();
	_delay_ms(5);
	return loc_u8data;
}
