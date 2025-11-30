#ifndef _DEVICE_HX711_H
#define _DEVICE_HX711_H
#include "stdint.h"


#define SCK_Pin  (GPIO_OUT1_Pin)
#define SCK_GPIO_Port (GPIO_OUT1_GPIO_Port)

#define DT_Pin  (GPIO_OUT2_Pin)
#define DT_GPIO_Port (GPIO_OUT2_GPIO_Port)

#define BUFFERSIZE 255  

void hx711_init(void);

uint32_t ReadCount(void);
uint32_t WeightReal(void);
void weighing_peeling(void);

#endif

