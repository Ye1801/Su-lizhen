#ifndef __ADC_SENSOR_H
#define __ADC_SENSOR_H

#include "main.h"
#include "adc.h"

void adc_sensor_init(void);
uint16_t adc_sensor_get(uint8_t channel);

#endif

