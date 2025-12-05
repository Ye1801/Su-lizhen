#ifndef __LED_H__
#define __LED_H__

#include "main.h"


#define LED1_PIN  (GPIO1_Pin)
#define LED1_PORT (GPIO1_GPIO_Port)

#define LED2_PIN  (GPIO2_Pin)
#define LED2_PORT (GPIO2_GPIO_Port)

#define LED3_PIN  (GPIO3_Pin)
#define LED3_PORT (GPIO3_GPIO_Port)

#define LED4_PIN  (GPIO4_Pin)
#define LED4_PORT (GPIO4_GPIO_Port)

#define LED5_PIN  (GPIO5_Pin)
#define LED5_PORT (GPIO5_GPIO_Port)

#define LED6_PIN  (GPIO6_Pin)
#define LED6_PORT (GPIO6_GPIO_Port)


void led1_init(void);
void led2_init(void);
void led3_init(void);
void led4_init(void);
void led5_init(void);
void led6_init(void);

void led1_set(uint8_t level);
void led2_set(uint8_t level);
void led3_set(uint8_t level);
void led4_set(uint8_t level);
void led5_set(uint8_t level);
void led6_set(uint8_t level);

void led1_board_toggle(void);
void led2_board_toggle(void);
void led3_board_toggle(void);
void led4_board_toggle(void);
void led5_board_toggle(void);
void led6_board_toggle(void);

#endif

