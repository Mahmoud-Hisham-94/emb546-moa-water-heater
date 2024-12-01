/*
 * EM_MAADI546.c
 *
 * Created: 8/30/2024 2:15:51 PM
 * Author : mahmo
 */ 

#include "../LIB/BIT_MATH.h"
#include "../LIB/STD_TYPE.h"
#include "../MCAL/DIO/DIO_interface.h"
#include "../MCAL/TWI/TWI_interface.h"
#include "../HAL/EEPROM/EEPROM_interface.h"
#include "../FreeRTOS/FreeRTOS.h"
#include "../FreeRTOS/task.h"
#include "../FreeRTOS/semphr.h"
#include "../FreeRTOS/queue.h"
#include "../HAL/SSD/SSD_interface.h"
#include "../MCAL/ADC/ADC_interface.h"
#include "../MCAL/TIM0/TIM0_interface.h"
#include "../MCAL/TIM2/TIM2_interface.h"
#define F_CPU 16000000UL
#include <util/delay.h>

TaskHandle_t t1;
SemaphoreHandle_t SSD ;
QueueHandle_t temp1;

u8 Time_y=0 ;
f32 Temperature_Reading[10];
u8 Average_Temp ;
void Time (void);



void task1 (void)
{
	u8 SSD_disp_0  =0;
	u8 SSD_disp_10 =0;
	static u8 current_preset_temp ;
	static u8 on_off=0;
	static u8 ssd_blinking =0;
	
	
	while (1)
	{
		xQueueReceive(temp1,&on_off,100);
		// check whether up or down button is pressed to enter temperature setting mode
		if ((DIO_u8ReadpinVal(DIO_PORTD,DIO_PIN2)==1) || (DIO_u8ReadpinVal(DIO_PORTD,DIO_PIN6)==1))
			{
				while((DIO_u8ReadpinVal(DIO_PORTD,DIO_PIN2)==1) || (DIO_u8ReadpinVal(DIO_PORTD,DIO_PIN6)==1));
				
				xSemaphoreTake(SSD,10);	
				// in temperature setting mode if on/off button is pressed it shuts down the system
				if (on_off==1)
				{
					// get the Preset temperature from the EEPROM
					current_preset_temp = EEPROM_voidRecieveDataFromEEPROM(0);
					
					// temperature setting mode ends after 5 seconds if no buttons are pressed
					for (u8 z=0 ; z<249 ; z++)
					{
						// to break the loop if on/off button is pressed
						if (DIO_u8ReadpinVal(DIO_PORTB,DIO_PIN0)==1)
						{break;}
						// counter for SSD blinking
						ssd_blinking ++;
						if (ssd_blinking==23)
						{
							DIO_voidSetPinDir(DIO_PORTB,DIO_PIN1,INPUT); // SSD enable 1
							DIO_voidSetPinDir(DIO_PORTB,DIO_PIN2,INPUT); // SSD enable 2
						}
						else if (ssd_blinking==27)
						{
							DIO_voidSetPinDir(DIO_PORTB,DIO_PIN1,OUTPUT); // SSD enable 1
							DIO_voidSetPinDir(DIO_PORTB,DIO_PIN2,OUTPUT); // SSD enable 2
							ssd_blinking=0;
						}
						/* if up button is pressed increase the preset temperature by 5 with  
						   maximum value being 75 degrees ,and store new value in EEPROM */
						if ((DIO_u8ReadpinVal(DIO_PORTD,DIO_PIN2)==1) && (current_preset_temp<=70))
						{
							while(DIO_u8ReadpinVal(DIO_PORTD,DIO_PIN2)==1);
							current_preset_temp = current_preset_temp + 5;
							EEPROM_voidSendDataToEEPROM(0,current_preset_temp);
							z=0;
							ssd_blinking=0;
						}
						/* if down button is pressed decrease the preset temperature by 5 with  
						   minimum value being 35 degrees ,and store new value in EEPROM */
						if ((DIO_u8ReadpinVal(DIO_PORTD,DIO_PIN6)==1) && (current_preset_temp>=40))
						{
							while(DIO_u8ReadpinVal(DIO_PORTD,DIO_PIN6)==1);
							current_preset_temp = current_preset_temp - 5;
							EEPROM_voidSendDataToEEPROM(0,current_preset_temp);
							z=0;
							ssd_blinking=0;
						}
						
						// display the set temperature while in temperature setting mode
						SSD_disp_0 =current_preset_temp%10;
						SSD_disp_10=current_preset_temp/10;
						
						DIO_voidSetPinVal(DIO_PORTB,DIO_PIN2,HIGH);
						DIO_voidSetPinVal(DIO_PORTB,DIO_PIN1,LOW);
						SSD_voidDisplayNum(SSD_disp_10) ;
						_delay_ms(20);
						DIO_voidSetPinVal(DIO_PORTB,DIO_PIN1,HIGH);
						DIO_voidSetPinVal(DIO_PORTB,DIO_PIN2,LOW);
						SSD_voidDisplayNum(SSD_disp_0) ;
						_delay_ms(20);
					}
				}	
				xSemaphoreGive(SSD);	
		}
		vTaskDelay(20);
	}
}


void task2 (void)
{		
	u8 SSD_disp_0  =0;
	u8 SSD_disp_10 =0;
	
	while (1)
		{

			xSemaphoreTake(SSD,10);
			SSD_disp_0 =Average_Temp%10;
			SSD_disp_10=Average_Temp/10;
			// display the temperature from lm35 sensor
			for (u8 z=0 ; z<2 ; z++)
				{
					DIO_voidSetPinVal(DIO_PORTB,DIO_PIN2,HIGH);
					DIO_voidSetPinVal(DIO_PORTB,DIO_PIN1,LOW);
					SSD_voidDisplayNum(SSD_disp_10) ;
					_delay_ms(20);
					DIO_voidSetPinVal(DIO_PORTB,DIO_PIN1,HIGH);
					DIO_voidSetPinVal(DIO_PORTB,DIO_PIN2,LOW);
					SSD_voidDisplayNum(SSD_disp_0) ;
					_delay_ms(20);
				}
			xSemaphoreGive(SSD);
			vTaskDelay(20);
		}
}

void task3 (void)
{
	 u8 temperature ;
	 u8 current_preset_temp;
	 u8 temp = 0;
	 
	while (1)
		{	
			current_preset_temp=EEPROM_voidRecieveDataFromEEPROM(0);
			temperature=Average_Temp;

				if (((temperature)  <= (current_preset_temp - 5)) || (temp==1))
				{
					if ((temperature)  < (current_preset_temp + 4))
					{
						temp=1;
						// Turn the heater on
						DIO_voidSetPinVal(DIO_PORTC,DIO_PIN2,HIGH);
						DIO_voidSetPinVal(DIO_PORTC,DIO_PIN7,LOW);
						// Red Led blinking while the heater is on
						if (Time_y==0) {DIO_voidSetPinVal(DIO_PORTC,DIO_PIN5,HIGH);}
						else  		   {DIO_voidSetPinVal(DIO_PORTC,DIO_PIN5,LOW) ;}
						
					}
						
					else if ((temperature)  = (current_preset_temp + 4))
					{
						temp=0;
						DIO_voidSetPinVal(DIO_PORTC,DIO_PIN2,LOW);
						DIO_voidSetPinVal(DIO_PORTC,DIO_PIN5,LOW);
					}
				}
				if ((temperature) >= (current_preset_temp + 5))
				{
					
					// Red led on but not blinking while cooling fan is on
					DIO_voidSetPinVal(DIO_PORTC,DIO_PIN5,HIGH);
					// turn the heater off
					DIO_voidSetPinVal(DIO_PORTC,DIO_PIN2,LOW);
					// turn the cooling fan on
					DIO_voidSetPinVal(DIO_PORTC,DIO_PIN7,HIGH);
					DIO_voidSetPinVal(DIO_PORTC,DIO_PIN4,LOW);
					DIO_voidSetPinVal(DIO_PORTC,DIO_PIN3,HIGH);
				}

			vTaskDelay(20);
		}
}


void task4 (void)
{
	static u8 count = 0;
	
		while(1)
		{
			if ((DIO_u8ReadpinVal(DIO_PORTB,DIO_PIN0)==1) && count==0)
				{
					while(DIO_u8ReadpinVal(DIO_PORTB,DIO_PIN0)==1);
					DIO_voidSetPinDir(DIO_PORTB,DIO_PIN1,OUTPUT); // SSD enable 1
					DIO_voidSetPinDir(DIO_PORTB,DIO_PIN2,OUTPUT); // SSD enable 2
					DIO_voidSetPinDir(DIO_PORTC,DIO_PIN2,OUTPUT); // heater relay
					DIO_voidSetPinDir(DIO_PORTC,DIO_PIN7,OUTPUT); // cooling fan relay
					DIO_voidSetPinDir(DIO_PORTC,DIO_PIN5,OUTPUT); // heater led indicator 
					DIO_voidSetPinVal(DIO_PORTD,DIO_PIN3,HIGH);   // on-off green led
					count ++;
					
				}
			else if ((DIO_u8ReadpinVal(DIO_PORTB,DIO_PIN0)==1) && count==1)
				{
					while(DIO_u8ReadpinVal(DIO_PORTB,DIO_PIN0)==1);
					DIO_voidSetPinDir(DIO_PORTB,DIO_PIN1,INPUT); // SSD enable 1
					DIO_voidSetPinDir(DIO_PORTB,DIO_PIN2,INPUT); // SSD enable 2
					DIO_voidSetPinDir(DIO_PORTC,DIO_PIN2,INPUT); // heater relay
					DIO_voidSetPinDir(DIO_PORTC,DIO_PIN7,INPUT); // cooling fan relay
					DIO_voidSetPinDir(DIO_PORTC,DIO_PIN5,INPUT); // heater led indicator 
					DIO_voidSetPinVal(DIO_PORTD,DIO_PIN3,LOW);	 // on-off green led
					count = 0;
				}
				xQueueSend(temp1,&count,100);
			vTaskDelay(20);
		}
}



int main(void)
{
	
	// TWI initialization
	TWI_voidMasterInit(0);
	
	// enable global interrupt
	GI_voidEnable();
	
	// initializing timer 0 CTC mode and set call back Function
	TIM0_voidInitCTC_OV(1);
	TIM0_voidSetCallBack(Time,1);
	 
	// setting initial value of temp in EEPROM
	EEPROM_voidSendDataToEEPROM(0,60);

	// input buttons Dir
	DIO_voidSetPinDir(DIO_PORTB,DIO_PIN0,INPUT);  // on_off
	DIO_voidSetPinDir(DIO_PORTD,DIO_PIN2,INPUT);  // up
	DIO_voidSetPinDir(DIO_PORTD,DIO_PIN6,INPUT);  // down
	
	// on/off Led indicators Dir
	DIO_voidSetPinDir(DIO_PORTD,DIO_PIN3,OUTPUT);   // on-off green led	
	
	// DC motor Dir
	DIO_voidSetPinDir(DIO_PORTD , DIO_PIN4 , INPUT);
	DIO_voidSetPinDir(DIO_PORTD , DIO_PIN7 , OUTPUT);
	DIO_voidSetPinDir(DIO_PORTC , DIO_PIN3 , OUTPUT);
	DIO_voidSetPinDir(DIO_PORTC , DIO_PIN4 , OUTPUT);
	
	// setting timer 2 for motor speed control
	TIM2_voidFastPWM(99);
	
	// ADC initialization for temperature sensor
	ADC_voidInit();

	// Creating Project tasks
	xTaskCreate(&task1,"task1",80,NULL,2,NULL); // temperature setting mode task
	xTaskCreate(&task2,"task2",80,NULL,3,NULL); // lm35 sensor temperature display task
	xTaskCreate(&task3,"task3",80,NULL,4,NULL); // decision based on temperature avg. and preset temperature task
	xTaskCreate(&task4,"task4",80,NULL,1,NULL); // on/off button task
	
	// Creating seven segments displays semaphore
	SSD = xSemaphoreCreateBinary();
	
	// Creating temp handles for tasks
	temp1 = xQueueCreate(1,sizeof(u8));

	//Starting tasks scheduler
	vTaskStartScheduler();
	
}

// define a function to pass to the set call back function
// sense temperature every 100 ms and calculates the average temperature of the last 10 readings
// responsible for the led blinking every 1 sec
// counter values were changed for the simulation to work properly 
void Time (void)
{
	static u16 counter1=0;
	static u16 counter2=0;
	f32 total =0;
	static f32 temperature=0;
	static u16 i=0;
	
	counter1 ++;
	counter2 ++;
		
	if (counter1==10)
	{
		temperature=(f32)ADC_u16ReadChannel(ADC_0);
		temperature=temperature*500/1023;
		Temperature_Reading[i] = temperature;
		for (u8 x=0 ; x<10 ; x++)
		{
			total=total+Temperature_Reading[x];
		}
		Average_Temp=(u32)total/10;
		i++;
		if (i==10) {i=0;}
		counter1 = 0 ;
	}
	if (counter2==100)
	{
		if (Time_y==1)	{Time_y=0;}
		else			{Time_y=1;}
		counter2= 0 ;
	}
}
