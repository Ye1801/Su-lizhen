#ifndef __VIBRATION_SENSOR_H
#define __VIBRATION_SENSOR_H 
    
#include "main.h"
#include "gpio.h"


#define VIBRATION1_PIN  (GPIO_IN1_Pin)
#define VIBRATION1_PORT (GPIO_IN1_GPIO_Port)

#define VIBRATION2_PIN  (GPIO_IN2_Pin)
#define VIBRATION2_PORT (GPIO_IN2_GPIO_Port)

#define VIBRATION3_PIN  (GPIO_IN3_Pin)
#define VIBRATION3_PORT (GPIO_IN3_GPIO_Port)

#define VIBRATION4_PIN  (GPIO_IN4_Pin)
#define VIBRATION4_PORT (GPIO_IN4_GPIO_Port)

void vibration1_init(void);
void vibration2_init(void);
void vibration3_init(void);
void vibration4_init(void);

uint8_t vibration1_get_data(void);
uint8_t vibration2_get_data(void);
uint8_t vibration3_get_data(void);
uint8_t vibration4_get_data(void);

uint8_t vibration1_set_clear(void);
uint8_t vibration2_set_clear(void);
uint8_t vibration3_set_clear(void);
uint8_t vibration4_set_clear(void);
	
#endif
