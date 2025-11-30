#include "dht11.h"
#include <stdio.h>

#define W1DQ_Input()	\
{\
	GPIO_InitTypeDef GPIO_InitStruct = {0};\
 	GPIO_InitStruct.Pin = DHT11_Pin;\
 	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;\
 	GPIO_InitStruct.Pull = GPIO_PULLUP;\
 	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;\
 	HAL_GPIO_Init(DHT11_GPIO_Port, &GPIO_InitStruct);\
}

#define W1DQ_Output()	\
{\
	GPIO_InitTypeDef GPIO_InitStruct = {0};\
 	GPIO_InitStruct.Pin = DHT11_Pin;\
 	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;\
 	GPIO_InitStruct.Pull = GPIO_NOPULL;\
 	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;\
 	HAL_GPIO_Init(DHT11_GPIO_Port, &GPIO_InitStruct);\
}

#define W1DQ_Write(x)	HAL_GPIO_WritePin(DHT11_GPIO_Port, DHT11_Pin,\
		(x==1)?GPIO_PIN_SET : GPIO_PIN_RESET)

#define W1DQ_Read()	HAL_GPIO_ReadPin(DHT11_GPIO_Port, DHT11_Pin)

void delay_us(uint16_t time)
{
	uint16_t i=0;  
   while(time--)
   {
      i=10;
      while(i--) ;    
   }
}
static void DHT11_StartSignal(void)
{
	W1DQ_Output();

	W1DQ_Write(0);
	HAL_Delay(20);
	
	W1DQ_Write(1);
	delay_us(30);

	W1DQ_Input();
}
uint8_t DHT11_RespondSignal(void)
{
	uint8_t retry = 0;

	while(W1DQ_Read() && retry < 100)
	{
		retry++;
		delay_us(1);
	}
	if(retry >= 100)
	{
		printf("The host receives no response signal!\r\n");
		return 1;
	}

	retry = 0;

	while(!W1DQ_Read() && retry < 100)
	{
		retry++;
		delay_us(1);
	}

	if(retry >= 100)
	{
		printf("DHT11 has not received a start signal!\r\n");
		return 1;
	}

	return 0;
}
uint8_t DHT11_ReadBit(void)
{
	uint8_t retry = 0;
	
	while(W1DQ_Read() && (retry < 100))
	{
		retry++;
		delay_us(1);
	}

	retry = 0;
	while( !W1DQ_Read() && retry < 100)
	{
		retry++;
		delay_us(1);
	}

	delay_us(40);
	if(W1DQ_Read())
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
uint8_t DHT11_ReadByte(void)
{
	uint8_t i, dat;

	dat = 0;
	for(i=0; i<8; i++)
	{
		dat <<=1;
		dat |= DHT11_ReadBit();
	}

	return dat;
}
int DHT11_SampleData(float *temperature, float *humidity)
{
	uint8_t humi_H8bit;
	uint8_t humi_L8bit;
	uint8_t temp_H8bit;
	uint8_t temp_L8bit;
	uint8_t check_sum;

	if(!temperature || !humidity)
	return -1;

	DHT11_StartSignal();

	if(0 != DHT11_RespondSignal())
	return -2;

	humi_H8bit = DHT11_ReadByte();
	humi_L8bit = DHT11_ReadByte();
	temp_H8bit = DHT11_ReadByte();
	temp_L8bit = DHT11_ReadByte();
	check_sum  = DHT11_ReadByte();

	if((humi_H8bit + humi_L8bit + temp_H8bit + temp_L8bit) != check_sum)
	return -3;

	*humidity = (humi_H8bit*1000 + humi_L8bit)/1000;
	*temperature = (temp_H8bit*1000 + temp_L8bit)/1000;
	return 0;
}
