#include "zigbee.h"
#include "usart.h"
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

/*
*************************************
变量定义
*************************************
*/
/*
**********************************************************************************************************
串口初始化,设置zigbee的波特率为9600
**********************************************************************************************************
*/
void zigbee_uart3_init(void)
{
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
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
void zigbee_uart3_clear(void)	//清空接收串口1数组程序
{
	memset(uart3_buf,0,(unsigned int)strlen((const char *)uart3_buf));	//清零串口数组
	uart3_count = 0;
	uart3_start = 0;
	uart3_finish = 0;
}
/*
*************************************
zigbee发送数据
*************************************
*/
uint8_t zigbee_send_msg(uint8_t* send_msg,uint8_t msg_len)
{
	uint8_t ret_val= FALSE;
	
	HAL_UART_Transmit(&huart3, (unsigned char *)send_msg,msg_len, 1000);	
	
	return ret_val;
}
/*
*************************************
zigbee接收数据  0x5f|0xf5|id_h_|id_l|temp_h|temp_l|humi_h|humi_l|lux_h|lux_l|smoke_h|smoke_l|rain_h|rain_l|0xf5|0x5f
              0     1     2     3   4       5      6      7      8     9     10      11      12     13    14   15
*************************************
*/
uint8_t zigbee_receive_msg(uint8_t *rec_msg,uint8_t *rec_len)	//接收处理函数
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
		HAL_Delay(50);
		if((uart3_buf[0]==0x5f)&&(uart3_buf[1]==0xf5)&&(uart3_buf[14]==0xf5)&&(uart3_buf[15]==0x5f)) {
			*rec_len = 16;
		  memcpy(rec_msg,uart3_buf,16);
		  ret_val = TRUE;
		} else {
			ret_val = FALSE;
		}

	}
  zigbee_uart3_clear();
	return ret_val;
}
/*
*************************************
bc20初始化
*************************************
*/
void zigbee_init(void)
{
	zigbee_uart3_init();
	HAL_UART_Receive_IT(&huart3, &uart3_data, 1);
}

