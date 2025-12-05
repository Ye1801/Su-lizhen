#include "max30102_uart.h"
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
void max30102_uart3_clear(void)	
{
	memset(uart3_buf,0,(unsigned int)strlen((const char *)uart3_buf));	
	uart3_count = 0;
	uart3_start = 0;
	uart3_finish = 0;
}
/*
**********************************************************************************************************
max30102接收数据处理
**********************************************************************************************************
*/
uint8_t max30102_uart_receive_msg(struct max30102_data_t *data)
{
  uint8_t ret_val= FALSE;
	uint16_t count = 0;
	
	int heart=0;
  int spo2=0;
	
	HAL_UART_Transmit(&huart3, "AT+HEART\r\n",10, 1000);	
	
	while((uart3_start == 0)&&(count<100))	
	{
		count++;
		HAL_Delay(1);
	}
	if(count < 100)	
	{
		HAL_Delay(20);

		if(strstr((const char*)uart3_buf, "+HEART=NULL")) {
			data->heart_flag=0;
		} else {
			sscanf((char*)uart3_buf,"+HEART=%d",&heart);
			data->heart_flag=1;
		  data->heart =heart;
		}
	}
  max30102_uart3_clear();
	HAL_Delay(20);
	
	
	
	HAL_UART_Transmit(&huart3, "AT+SPO2\r\n",9, 1000);	
	while((uart3_start == 0)&&(count<100))	
	{
		count++;
		HAL_Delay(1);
	}
	if(count < 100)	
	{
		HAL_Delay(20);
		if(strstr((const char*)uart3_buf, "+SPO2=NULL")) {
			data->spo2_flag=0;
		} else {
		  sscanf((char*)uart3_buf,"+SPO2=%d",&spo2);
			data->spo2_flag=1;
		  data->spo2 =spo2;
		  ret_val = TRUE;
		}
	}
  max30102_uart3_clear();
  return ret_val;
}
/*
**********************************************************************************************************
串口初始化,设置max30102的波特率为9600
**********************************************************************************************************
*/
void max30102_uart3_init(void)
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
max30102串口初始化配置
*************************************
*/
void max30102_uart_init(void)
{
	max30102_uart3_init();
	HAL_UART_Receive_IT(&huart3, &uart3_data, 1);
}

