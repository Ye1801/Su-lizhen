#ifndef _JSYMK163_H
#define _JSYMK163_H

#include "main.h"

#define TRUE        (0)
#define FALSE       (1)

struct jsymk163_data_t{
	int voltage;
  int power;
	int current;
	float power_consumption;
} ;

void jsymk163_init(void);
uint8_t jsymk163_receive_msg(struct jsymk163_data_t *data);

#endif

