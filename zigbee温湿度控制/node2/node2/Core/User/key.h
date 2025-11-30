#ifndef _KEY_H_
#define _KEY_H_

#include "main.h"

#define KEY1_PIN  (GPIO1_Pin)
#define KEY1_PORT (GPIO1_GPIO_Port)

#define KEY2_PIN  (GPIO2_Pin)
#define KEY2_PORT (GPIO2_GPIO_Port)

#define KEY3_PIN  (GPIO3_Pin)
#define KEY3_PORT (GPIO3_GPIO_Port)

#define KEY4_PIN  (GPIO4_Pin)
#define KEY4_PORT (GPIO4_GPIO_Port)

#define KEY5_PIN  (GPIO5_Pin)
#define KEY5_PORT (GPIO5_GPIO_Port)

#define KEY6_PIN  (GPIO6_Pin)
#define KEY6_PORT (GPIO6_GPIO_Port)

void key1_init(void);
void key2_init(void);
void key3_init(void);
void key4_init(void);
void key5_init(void);
void key6_init(void);

int key1_get(void);
int key2_get(void);
int key3_get(void);
int key4_get(void);
int key5_get(void);
int key6_get(void);

#endif
