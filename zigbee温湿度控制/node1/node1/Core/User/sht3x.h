#ifndef __SHT30_H_
#define __SHT30_H_

#include "stm32f1xx.h"                  // Device header
#include "i2c.h"
 
 void SHT30_Reset(void);
 uint8_t SHT30_Init(void);
 uint8_t SHT30_Read_Dat(uint8_t* dat);
 uint8_t CheckCrc8(uint8_t* const message, uint8_t initial_value);
 uint8_t SHT30_Dat_To_Float(uint8_t* const dat, float* temperature, float* humidity);
 

 #endif
/*while??

	uint8_t dat[6] = {0};
	float temperature = 0.0;
	float humidity = 0.0;
	
	SHT30_Reset();
	if(SHT30_Init() == HAL_OK)
		printf("sht30 init is ok!\r\n");
	else
		printf("sht30 init is not ok!\r\n");
		
*/
/*while??

	if(SHT30_Read_Dat(dat) == HAL_OK)
	{
		if(SHT30_Dat_To_Float(dat,&temperature,&humidity) == HAL_OK)
		{
			printf("TEMP:%f,HUM:%f\r\n",temperature,humidity);
		}
		else printf("sht30 check failed!\r\n");
	}
	else printf("sht30 read date failed!\r\n");
	
*/
