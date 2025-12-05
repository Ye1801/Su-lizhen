#include "jdy_24m.h"
#include "stdio.h"
#include "string.h"
#include "usart.h"
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

/*
*************************************
变量定义
*************************************
*/


/*
**********************************************************************************************************
串口初始化,设置jdy_24m的波特率为115200
**********************************************************************************************************
*/
void jdy_24m_uart3_init(void)
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
清空接收串口数组程序
*************************************
*/
void jdy_24m_uart2_clear(void)	//清空接收串口1数组程序
{
	memset(uart3_buf,0,(unsigned int)strlen((const char *)uart3_buf));	//清零串口数组
	uart3_count = 0;
	uart3_start = 0;
	uart3_finish = 0;
}
/*
*************************************
jdy_24m发送数据
*************************************
*/
uint8_t jdy_24m_send_msg(uint8_t* send_msg,uint8_t msg_len)
{
	uint8_t ret_val= FALSE;
	
	HAL_UART_Transmit(&huart3, (unsigned char *)send_msg,msg_len, 1000);	
	
	return ret_val;
}
/*
*************************************
jdy_24m接收数据
*************************************
*/
uint8_t jdy_24m_receive_msg(uint8_t *rec_msg,uint8_t *rec_len)	//接收处理函数
{
	uint8_t ret_val = FALSE;
	uint16_t count = 0;		
  
	while((uart3_start == 0)&&(count<100))	                    //等待命令发送完成
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
		*rec_len = uart3_buf[2]+3;
		memcpy(rec_msg,uart3_buf,uart3_buf[2]+5);
		
		
		ret_val = TRUE;
	}
  jdy_24m_uart2_clear();
	return ret_val;
}
/*
*************************************
jdy_24m初始化
*************************************
*/
void jdy_24m_init(void)
{
	jdy_24m_uart3_init();
  HAL_UART_Receive_IT(&huart3, &uart3_data, 1);
}

