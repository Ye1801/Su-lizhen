#ifndef __STM32_FLASH_H__
#define __STM32_FLASH_H__

#include "main.h"  

#include "main.h"
#include "string.h"

#define       STM32_FLASH_SIZE 64   //所选STM32的FLASH容量大小(单位为K)；本产品选用的型号为：STM32F103C8T6；FALSH大小为64K

     #if      STM32_FLASH_SIZE < 256
		 #define  STM32_SECTOR_SIZE 1024  //一页为1K
		 #else
		 #define  STM32_SECTOR_SIZE 2048   //一页为2K
		 #endif
		 
#define STM32_FLASH_BASE 0x08000000 //STM32 FLASH起始地址

//写入的FLASH地址，这里为从倒数第一个扇区地址(0x807f800)开始写
//STM32_FLASH_BASE + STM32_SECTOR_SIZE*255 = 0x08000000 + (2048*255) = 0x0807f800
//#define FLASH_SAVE_ADDR  STM32_FLASH_BASE+STM32_SECTOR_SIZE*255

#define FLASH_SAVE_ADDR  0x08007000
		 

void FLASH_WriteData(uint32_t FLASH_Addr, uint16_t *FLASH_Data, uint16_t Size);
uint16_t FLASH_ReadHalfWord(uint32_t faddr);
void FLASH_ReadData(uint32_t ReadAddr,uint8_t *pBuffer,uint16_t NumToRead);

#endif

