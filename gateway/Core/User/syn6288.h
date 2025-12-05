#ifndef _SYN6288_H
#define _SYN6288_H

#include "main.h"

/*
*************************************
???
*************************************
*/
#define TRUE        (0)
#define FALSE       (1)

uint8_t syn6288_frame_info(uint8_t Music, uint8_t *HZdata);
void syn6288_init(void);

#endif

