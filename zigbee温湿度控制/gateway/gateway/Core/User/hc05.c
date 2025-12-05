#include "hc05.h"
#include "stdio.h"
#include "string.h"
#include "uart_handle.h"

/*
*************************************
宏定义
*************************************
*/
    
/*
*************************************
变量声明
*************************************
*/
extern UART_HandleTypeDef huart2;
/*
*************************************
变量定义
*************************************
*/

/*
**********************************************************************************************************
串口初始化,设置hc-05的波特率为9600
**********************************************************************************************************
*/
void hc05_uart2_init(void)
{
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 9600;
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
清空接收串口数组程序
*************************************
*/
void hc05_uart2_clear(void)	//清空接收串口1数组程序
{
	memset(uart2_buf,0,(unsigned int)strlen((const char *)uart2_buf));	//清零串口数组
	uart2_count = 0;
	uart2_start = 0;
	uart2_finish = 0;
}
/*
*************************************
hc05发送数据
*************************************
*/
uint8_t hc05_send_msg(uint8_t* send_msg)
{
	uint8_t ret_val= FALSE;
	
	HAL_UART_Transmit(&huart2, (unsigned char *)send_msg,strlen((const char *)send_msg), 1000);	
	
	return ret_val;
}
/*
*************************************
hc05接收数据
*************************************
*/
uint8_t hc05_receive_msg(uint8_t *rec_msg,uint8_t *rec_len)	//接收处理函数
{
	uint8_t ret_val = FALSE;
	uint16_t count = 0;		
  int msg_len=0;
	
	while((uart2_start == 0)&&(count<100))	                    //等待命令发送完成
	{
		count++;
		HAL_Delay(1);
	}
	if(count >= 100)	                                          //超时
	{
		ret_val = FALSE;	                                          //未接收到响应
	}
	else
	{
		HAL_Delay(60);
		msg_len = strlen((char*)uart2_buf);
		memcpy(rec_msg,uart2_buf,msg_len);
		*rec_len = msg_len;
		ret_val = TRUE;
	}
  hc05_uart2_clear();
	return ret_val;
}
/*
*************************************
hc05初始化
*************************************
*/
void hc05_init(void)
{
  hc05_uart2_init();
	HAL_UART_Receive_IT(&huart2, &uart2_data, 1);
}

