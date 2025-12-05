#include "hcsr04_uart.h"
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
void hcsr04_uart1_clear(void)	
{
	memset(uart1_buf,0,(unsigned int)strlen((const char *)uart1_buf));	
	uart1_count = 0;
	uart1_start = 0;
	uart1_finish = 0;
}
/*
**********************************************************************************************************
co2接收数据处理
**********************************************************************************************************
*/
uint8_t hcsr04_receive_msg(uint16_t *rec_msg)
{
  uint8_t ret_val= FALSE;
	uint16_t count = 0;
	
	uint8_t msg_buf[1]={0};
	msg_buf[0]=0xA0;
	
	HAL_UART_Transmit(&huart1, msg_buf,1, 1000);	
	
	while((uart1_start == 0)&&(count<100))	
	{
		count++;
		HAL_Delay(1);
	}
	if(count < 100)	
	{
		HAL_Delay(5);
		uint32_t data1 = uart1_buf[0];
		uint32_t data2 = uart1_buf[1];
		uint32_t data3 = uart1_buf[2];
		
		*rec_msg = ((data1<<16)+(data2<<8)+data3)/10000;  //单位cm
		
		if(*rec_msg>400){
			*rec_msg=400;
		}
    ret_val = TRUE;
	}
  hcsr04_uart1_clear();
  return ret_val;
}
/*
**********************************************************************************************************
串口初始化,设置co2的波特率为9600
**********************************************************************************************************
*/
void hcsr04_uart1_init(void)
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
co2串口初始化配置
*************************************
*/
void hcsr04_init(void)
{
	hcsr04_uart1_init();
	HAL_UART_Receive_IT(&huart1, &uart1_data, 1);
}













