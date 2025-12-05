#include "esp32cam.h"
#include "usart.h"
#include <stdio.h>
#include <string.h>
#include "uart_handle.h"
/*
*************************************
宏定义
*************************************
*/

/*
*************************************
变量定义
*************************************
*/


/*
**********************************************************************************************************
清空接收串口数组程序
**********************************************************************************************************
*/
void esp32_uart2_clear(void)	
{
	memset(uart2_buf,0,(unsigned int)strlen((const char *)uart2_buf));	
	uart2_count = 0;
	uart2_start = 0;
	uart2_finish = 0;
}
/*
**********************************************************************************************************
su03t接收数据处理
**********************************************************************************************************
*/
uint8_t esp32_receive_msg(uint8_t *rec_msg)
{
  uint8_t ret_val= FALSE;
	
	if(uart2_start == 1) {
    do{
			uart2_finish++;
			HAL_Delay(1);
		}while(uart2_finish < 5);	                          //等待指令接收完成
	} else {
    ret_val= FALSE;
		return ret_val;
  }
	
	memcpy(rec_msg,uart2_buf,128);
	ret_val= TRUE;

  esp32_uart2_clear();
  return ret_val;
}
/*
**********************************************************************************************************
串口初始化,设置su03t的波特率为9600
**********************************************************************************************************
*/
void esp32_uart2_init(void)
{
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
}
/*
*************************************
su03t串口初始化配置
*************************************
*/
void esp32cam_init(void)
{
	esp32_uart2_init();
	HAL_UART_Receive_IT(&huart2, &uart2_data, 1);
}

