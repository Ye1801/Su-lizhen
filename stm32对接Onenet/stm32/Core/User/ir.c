#include "ir.h"

uint8_t get_ir_status(void)
{
	uint8_t ir_status =0;
	
	if(HAL_GPIO_ReadPin(IR_GPIO_Port,IR_Pin)==GPIO_PIN_RESET)
	{
		ir_status=1;
	}
	return ir_status;
}