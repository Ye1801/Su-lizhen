#ifndef __BEEP_H
#define __BEEP_H 
    
#include "main.h"
#include "gpio.h"


#define BEEP1_PIN  (GPIO1_Pin)
#define BEEP1_PORT (GPIO1_GPIO_Port)

#define BEEP2_PIN  (GPIO2_Pin)
#define BEEP2_PORT (GPIO2_GPIO_Port)

#define BEEP3_PIN  (GPIO3_Pin)
#define BEEP3_PORT (GPIO3_GPIO_Port)

#define BEEP4_PIN  (GPIO4_Pin)
#define BEEP4_PORT (GPIO4_GPIO_Port)

#define BEEP5_PIN  (GPIO5_Pin)
#define BEEP5_PORT (GPIO5_GPIO_Port)

#define BEEP6_PIN  (GPIO6_Pin)
#define BEEP6_PORT (GPIO6_GPIO_Port)

void beep1_init(void);
void beep2_init(void);
void beep3_init(void);
void beep4_init(void);
void beep5_init(void);
void beep6_init(void);


void beep1_set(uint8_t level);
void beep2_set(uint8_t level);
void beep3_set(uint8_t level);
void beep4_set(uint8_t level);
void beep5_set(uint8_t level);
void beep6_set(uint8_t level);

	
#endif

