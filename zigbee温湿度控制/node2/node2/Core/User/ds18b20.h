#ifndef _DS18B20_H_
#define _DS18B20_H_

#include "main.h"


#define DS18B20_Pin  (GPIO3_Pin)
#define DS18B20_Port (GPIO3_GPIO_Port)


#define DS18B20_DQ_OUT_HIGH HAL_GPIO_WritePin(DS18B20_Port,DS18B20_Pin,GPIO_PIN_SET)
#define DS18B20_DQ_OUT_LOW 	HAL_GPIO_WritePin(DS18B20_Port,DS18B20_Pin,GPIO_PIN_RESET)
#define DS18B20_DQ_IN	      HAL_GPIO_ReadPin(DS18B20_Port,DS18B20_Pin)

uint8_t ds18b20_init(void);
int16_t ds18b20_get_data(void);

#endif
