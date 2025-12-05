#include "dc01.h"
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
void dc01_uart3_clear(void)	
{
	memset(uart3_buf,0,(unsigned int)strlen((const char *)uart3_buf));	
	uart3_count = 0;
	uart3_start = 0;
	uart3_finish = 0;
}
/*
**********************************************************************************************************
co2接收数据处理
**********************************************************************************************************
*/
uint8_t dc01_receive_msg(uint16_t *rec_msg)
{
  uint8_t ret_val= FALSE;
	uint8_t check_value=0;
	
	if(uart3_start == 1) {
    do{
			uart3_finish++;
			HAL_Delay(1);
		}while(uart3_finish < 5);	                          //等待指令接收完成
	} else {
    ret_val= FALSE;
		return ret_val;
  }
	HAL_Delay(10);
	check_value = uart3_buf[0]+uart3_buf[1]+uart3_buf[2];

	if((uart3_buf[0]==0xa5)&&((check_value&0x7f)==uart3_buf[3])) {
		*rec_msg=((uart3_buf[1]<<7)|uart3_buf[2]);
//		printf("dc01:%d\r\n",*rec_msg);
		ret_val= TRUE;
	} else {
    ret_val= FALSE;
  }
  dc01_uart3_clear();
  return ret_val;
}
/*
**********************************************************************************************************
串口初始化,设置co2的波特率为9600
**********************************************************************************************************
*/
void dc01_uart3_init(void)
{
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 9600;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
}
/*
*************************************
co2串口初始化配置
*************************************
*/
void dc01_init(void)
{
	dc01_uart3_init();
	HAL_UART_Receive_IT(&huart3, &uart3_data, 1);
}













