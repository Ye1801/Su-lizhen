#ifndef __WATER_H
#define __WATER_H

#include "main.h"
#include "adc.h"

void water_init(void);
uint8_t water_get(uint8_t channel);

#endif

