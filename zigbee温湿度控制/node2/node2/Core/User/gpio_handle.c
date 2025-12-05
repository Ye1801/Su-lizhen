#include "gpio_handle.h"

/*
*************************************
变量或函数声明
*************************************
*/

/*
**********************************************************************************************************
变量定义
**********************************************************************************************************
*/
uint8_t gpio1_state =1;
uint8_t gpio2_state =1;
uint8_t gpio3_state =1;
uint8_t gpio4_state =1;
uint8_t gpio5_state =1;
uint8_t gpio6_state =1;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
  
	if(GPIO_Pin == GPIO1_Pin) {
    if(HAL_GPIO_ReadPin(GPIO1_GPIO_Port,GPIO1_Pin)==0) {
      gpio1_state =0;
    }
    __HAL_GPIO_EXTI_CLEAR_IT(GPIO1_Pin);
  } else if(GPIO_Pin == GPIO2_Pin) {
		  if(HAL_GPIO_ReadPin(GPIO1_GPIO_Port,GPIO2_Pin)==0) {
        gpio2_state =0;
    }
    __HAL_GPIO_EXTI_CLEAR_IT(GPIO2_Pin);
	} else if(GPIO_Pin == GPIO3_Pin) {
	    if(HAL_GPIO_ReadPin(GPIO1_GPIO_Port,GPIO3_Pin)==0) {
        gpio3_state =0;
    }
    __HAL_GPIO_EXTI_CLEAR_IT(GPIO3_Pin);
	} else if(GPIO_Pin == GPIO4_Pin) {
		  if(HAL_GPIO_ReadPin(GPIO1_GPIO_Port,GPIO4_Pin)==0) {
        gpio4_state =0;
      }
    __HAL_GPIO_EXTI_CLEAR_IT(GPIO4_Pin);
	} else if(GPIO_Pin == GPIO5_Pin) {
		  if(HAL_GPIO_ReadPin(GPIO1_GPIO_Port,GPIO5_Pin)==0) {
        gpio5_state =0;
      }
    __HAL_GPIO_EXTI_CLEAR_IT(GPIO5_Pin);
	} else if(GPIO_Pin == GPIO6_Pin) {
		  if(HAL_GPIO_ReadPin(GPIO1_GPIO_Port,GPIO6_Pin)==0) {
        gpio6_state =0;
      }
    __HAL_GPIO_EXTI_CLEAR_IT(GPIO6_Pin);
	}
}
