#include "pms5003.h"
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
void pms5003_uart1_clear(void)	
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
uint8_t pms5003_receive_msg(struct PMS5003 *pms)
{
  uint8_t ret_val= FALSE;
	uint16_t check_value=0;
	uint16_t checksums=0;
	
	
	if(uart1_start == 1) {
    do{
			uart1_finish++;
			HAL_Delay(1);
		}while(uart1_finish < 10);	                          //等待指令接收完成
	} else {
    ret_val= FALSE;
		return ret_val;
  }
	
	if((uart1_buf[0]==0x42)&&(uart1_buf[1]==0x4d)) {
		HAL_Delay(5);
		
		checksums = uart1_buf[0]+uart1_buf[1]+uart1_buf[2]+uart1_buf[3]+uart1_buf[4]+uart1_buf[5]+uart1_buf[6]+uart1_buf[7]+uart1_buf[8]+uart1_buf[9]
		             +uart1_buf[10]+uart1_buf[11]+uart1_buf[12]+uart1_buf[13]+uart1_buf[14]+uart1_buf[15]+uart1_buf[16]+uart1_buf[17]+uart1_buf[18]+uart1_buf[19]
		             +uart1_buf[20]+uart1_buf[21]+uart1_buf[22]+uart1_buf[23]+uart1_buf[24]+uart1_buf[25]+uart1_buf[26]+uart1_buf[27]+uart1_buf[28]+uart1_buf[29];
		
		check_value = (uart1_buf[30]<<8) +uart1_buf[31];
		
		if(checksums==check_value) {
			pms->data1 = (uart1_buf[4]<<8) +uart1_buf[5];
			pms->data2 = (uart1_buf[6]<<8) +uart1_buf[7];
			pms->data3 = (uart1_buf[8]<<8) +uart1_buf[9];
			pms->data4 = (uart1_buf[10]<<8) +uart1_buf[11];
			pms->data5 = (uart1_buf[12]<<8) +uart1_buf[13];
			pms->data6 = (uart1_buf[14]<<8) +uart1_buf[15];
			pms->data7 = (uart1_buf[16]<<8) +uart1_buf[17];
			pms->data8 = (uart1_buf[18]<<8) +uart1_buf[19];
			pms->data9 = (uart1_buf[20]<<8) +uart1_buf[21];
			pms->data10 = (uart1_buf[22]<<8) +uart1_buf[23];
			pms->data11 = (uart1_buf[24]<<8) +uart1_buf[25];
			pms->data12 = (uart1_buf[26]<<8) +uart1_buf[27];
			
			ret_val= TRUE;
		} else {
			ret_val= FALSE;
		}
	} else {
		ret_val= FALSE;
	}
	
  pms5003_uart1_clear();
  return ret_val;
}
/*
**********************************************************************************************************
串口初始化,设置co2的波特率为9600
**********************************************************************************************************
*/
void pms5003_uart1_init(void)
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
void pms5003_init(void)
{
	pms5003_uart1_init();
	HAL_UART_Receive_IT(&huart1, &uart1_data, 1);
}













