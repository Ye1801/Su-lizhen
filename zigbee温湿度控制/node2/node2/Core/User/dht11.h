#ifndef __DHT11_H
#define __DHT11_H 
    
#include "main.h"


#define DHT11_Pin  GPIO1_Pin  
#define DHT11_Port GPIO1_GPIO_Port

uint8_t dht11_init(void);
uint8_t dht11_read_data(uint8_t *temp,uint8_t *humi);

#endif

