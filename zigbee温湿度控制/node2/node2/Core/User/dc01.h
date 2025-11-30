#ifndef _DC01_H
#define _DC01_H

#include "main.h"

/*
*************************************
???
*************************************
*/
#define TRUE        (0)
#define FALSE       (1)

uint8_t dc01_receive_msg(uint16_t *rec_msg);
void dc01_init(void);

#endif

