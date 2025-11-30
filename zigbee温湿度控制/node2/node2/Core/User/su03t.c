#include "su03t.h"
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
void su03t_uart1_flag_clear(void)	
{
	memset(uart3_buf,0,(unsigned int)strlen((const char *)uart3_buf));	
	uart3_count = 0;
	uart3_start = 0;
	uart3_finish = 0;
}
/*
**********************************************************************************************************
su03t接收数据处理
**********************************************************************************************************
*/
uint8_t su03t_receive_msg(uint8_t *rec_msg)
{
  uint8_t ret_val= FALSE;
	
	if(uart3_start == 1) {
    do{
			uart3_finish++;
			HAL_Delay(1);
		}while(uart3_finish < 5);	                          //等待指令接收完成
	} else {
    ret_val= FALSE;
		return ret_val;
  }
	
	memcpy(rec_msg,uart3_buf,128);
	ret_val= TRUE;

  su03t_uart1_flag_clear();
  return ret_val;
}
/*
**********************************************************************************************************
串口初始化,设置su03t的波特率为9600
**********************************************************************************************************
*/
void uart1_init(void)
{
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
}
/*
*************************************
su03t串口初始化配置
*************************************
*/
void su03t_init(void)
{
	uart1_init();
	HAL_UART_Receive_IT(&huart1, &uart1_data, 1);
}

