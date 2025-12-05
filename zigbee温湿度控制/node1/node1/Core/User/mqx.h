#ifndef __MQX_H
#define __MQX_H

#include "main.h"
#include "adc.h"

void mqx_init(void);
uint16_t mqx_get_data(uint8_t channel);

#endif

