#ifndef __LORA_H
#define __LORA_H

#include "main.h"


#define TRUE        (0)
#define FALSE       (1)

void lora_init(void);
uint8_t lora_receive_msg(uint8_t *rec_msg,uint8_t *rec_len);
uint8_t lora_send_msg(uint8_t* send_msg,uint8_t msg_len);

#endif

