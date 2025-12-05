#ifndef __SOIL_H
#define __SOIL_H

#include "main.h"
#include "adc.h"

void soil_init(void);
uint8_t soil_get(uint8_t channel);

#endif

