#ifndef __FIRE_SENSOR_H
#define __FIRE_SENSOR_H 
    
#include "main.h"
#include "gpio.h"


#define FIRE1_PIN  (GPIO_IN1_Pin)
#define FIRE1_PORT (GPIO_IN1_GPIO_Port)

#define FIRE2_PIN  (GPIO_IN2_Pin)
#define FIRE2_PORT (GPIO_IN2_GPIO_Port)

#define FIRE3_PIN  (GPIO_IN3_Pin)
#define FIRE3_PORT (GPIO_IN3_GPIO_Port)

#define FIRE4_PIN  (GPIO_IN4_Pin)
#define FIRE4_PORT (GPIO_IN4_GPIO_Port)

void fire1_init(void);
void fire2_init(void);
void fire3_init(void);
void fire4_init(void);

uint8_t fire1_get_data(void);
uint8_t fire2_get_data(void);
uint8_t fire3_get_data(void);
uint8_t fire4_get_data(void);

#endif

