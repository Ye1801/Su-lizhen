#include "syn6288.h"
#include "usart.h"
#include <stdio.h>
#include <string.h>
#include "uart_handle.h"
/*
*************************************
???
*************************************
*/

/*
*************************************
????
*************************************
*/


/*
**********************************************************************************************************
??????????
**********************************************************************************************************
*/
void syn6288_uart3_clear(void)	
{
	memset(uart3_buf,0,(unsigned int)strlen((const char *)uart3_buf));	
	uart3_count = 0;
	uart3_start = 0;
	uart3_finish = 0;
}
/*
**********************************************************************************************************
//Music:选择背景音乐。0:无背景音乐，1~15：选择背景音乐
**********************************************************************************************************
*/
uint8_t syn6288_frame_info(uint8_t Music, uint8_t *HZdata)
{
	uint8_t ret_val= FALSE;
	/****************需要发送的文本**********************************/
  unsigned  char  Frame_Info[128];
  unsigned  char  HZ_Length;
  unsigned  char  ecc  = 0;  			//定义校验字节
  unsigned  int i = 0;
  HZ_Length = strlen((char*)HZdata); 			//需要发送文本的长度

  /*****************帧固定配置信息**************************************/
  Frame_Info[0] = 0xFD ; 			//构造帧头FD
  Frame_Info[1] = 0x00 ; 			//构造数据区长度的高字节
  Frame_Info[2] = HZ_Length + 3; 		//构造数据区长度的低字节
  Frame_Info[3] = 0x01 ; 			//构造命令字：合成播放命令
  Frame_Info[4] = 0x01 | Music << 4 ; //构造命令参数：背景音乐设定

  /*******************校验码计算***************************************/
  for(i = 0; i < 5; i++)   				//依次发送构造好的5个帧头字节
  {
    ecc = ecc ^ (Frame_Info[i]);		//对发送的字节进行异或校验
  }

  for(i = 0; i < HZ_Length; i++)   		//依次发送待合成的文本数据
  {
    ecc = ecc ^ (HZdata[i]); 				//对发送的字节进行异或校验
  }
  /*******************发送帧信息***************************************/
  memcpy(&Frame_Info[5], HZdata, HZ_Length);
  Frame_Info[5 + HZ_Length] = ecc;
	
	HAL_UART_Transmit(&huart3, (unsigned char *)Frame_Info,(5 + HZ_Length + 1), 1000);	
	
  syn6288_uart3_clear();
  return ret_val;
}
/*
**********************************************************************************************************
?????,??su03t?????9600
**********************************************************************************************************
*/
void syn6288_uart3_init(void)
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
su03t???????
*************************************
*/
void syn6288_init(void)
{
	syn6288_uart3_init();
	HAL_UART_Receive_IT(&huart3, &uart3_data, 1);
}

