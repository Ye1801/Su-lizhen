#ifndef _CO2_H
#define _CO2_H

#include "main.h"

/*
*************************************
???
*************************************
*/
#define TRUE        (0)
#define FALSE       (1)

uint8_t co2_receive_msg(uint16_t *rec_msg);
void co2_init(void);

#endif

