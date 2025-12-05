#include "uart_handle.h"
#include "stdio.h"
#include "usart.h"

#include <stdarg.h>

/*
**********************************************************************************************************
变量定义
**********************************************************************************************************
*/

uint8_t  uart1_data;					    //串口接收缓存数组
uint8_t  uart1_buf[UART1_REC_MAX];				  //串口接收缓存数组
uint16_t uart1_start = 0;         //串口接收开始标志位
uint16_t uart1_count = 0;         //串口接收数据计数器
uint16_t uart1_finish = 0;        //串口接收结束标志位

uint8_t  uart2_data;					    //串口接收缓存数组
uint8_t  uart2_buf[UART2_REC_MAX];				  //串口接收缓存数组
uint16_t uart2_start = 0;         //串口接收开始标志位
uint16_t uart2_count = 0;         //串口接收数据计数器
uint16_t uart2_finish = 0;        //串口接收结束标志位

uint8_t  uart3_data;					    //串口接收缓存数组
uint8_t  uart3_buf[UART3_REC_MAX];				  //串口接收缓存数组
uint16_t uart3_start = 0;         //串口接收开始标志位
uint16_t uart3_count = 0;         //串口接收数据计数器
uint16_t uart3_finish = 0;        //串口接收结束标志位
/*
*************************************
串口重定向,可以使用printf函数
使用的是串口3,波特率115200bps
*************************************
*/
int fputc(int ch, FILE *f)
{
	HAL_UART_Transmit(&huart1, (uint8_t*) &ch, 1, 0xffff);
	return ch;
}
/*
**********************************************************************************************************
串口接收回调
**********************************************************************************************************
*/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if (huart->Instance == USART1) {
		if(uart1_count>=UART1_REC_MAX) {
			uart1_count=0;
		}
    uart1_buf[uart1_count++] = uart1_data;
    HAL_UART_Receive_IT(&huart1, &uart1_data, 1);		
		uart1_start = 1;																//串口接收标志位置1
		uart1_finish = 0;																//串口接收数据完成标志位清零
  } else if (huart->Instance == USART2) {
		if(uart2_count>=UART2_REC_MAX) {
			uart2_count=0;
		}
    uart2_buf[uart2_count++] = uart2_data;
    HAL_UART_Receive_IT(&huart2, &uart2_data, 1);		
		uart2_start = 1;																//串口接收标志位置1
		uart2_finish = 0;																//串口接收数据完成标志位清零
  }  else if (huart->Instance == USART3) {
		if(uart3_count>=UART3_REC_MAX) {
			uart3_count=0;
		}
    uart3_buf[uart3_count++] = uart3_data;
    HAL_UART_Receive_IT(&huart3, &uart3_data, 1);		
		uart3_start = 1;																//串口接收标志位置1
		uart3_finish = 0;																//串口接收数据完成标志位清零
  }
}

