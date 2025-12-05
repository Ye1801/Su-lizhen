#include "ds18b20.h"

/****************************************功能说明****************************************

1.任意的GPIO均可,代码自动配置输入或输出
		
****************************************功能说明****************************************/

/**************************************************************************************
* 函数名称：ds18b20_delay_us
* 功能描述：延时函数
* 入口参数：时间,单位是微秒
* 出口参数：无
* 返 回 值：无
* 说    明：无
***************************************************************************************/
void ds18b20_delay_us(uint32_t time) {
  uint32_t i=8*time;
  while(i--);
}
/**************************************************************************************
* 函数名称：ds18b20_io_in
* 功能描述：gpio设为输入
* 入口参数：无
* 出口参数：无
* 返 回 值：无
* 说    明：无
***************************************************************************************/
void ds18b20_io_in(void){
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.Pin = DS18B20_Pin;
    GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
    HAL_GPIO_Init(DS18B20_Port,&GPIO_InitStructure);
}
/**************************************************************************************
* 函数名称：ds18b20_io_out
* 功能描述：gpio设为输出
* 入口参数：无
* 出口参数：无
* 返 回 值：无
* 说    明：无
***************************************************************************************/
void ds18b20_io_out(void){
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.Pin = DS18B20_Pin;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(DS18B20_Port,&GPIO_InitStructure);
}
/**************************************************************************************
* 函数名称：ds18b20_rst
* 功能描述：ds18b20复位
* 入口参数：无
* 出口参数：无
* 返 回 值：无
* 说    明：无
***************************************************************************************/
void ds18b20_rst(void){
    ds18b20_io_out();
    DS18B20_DQ_OUT_LOW;
    ds18b20_delay_us(750);
    DS18B20_DQ_OUT_HIGH;
    ds18b20_delay_us(15);
}
/**************************************************************************************
* 函数名称：ds18b20_check
* 功能描述：检查ds18b20是否存在
* 入口参数：无
* 出口参数：0-设备存在,1-设备不存在或异常
* 返 回 值：无
* 说    明：无
***************************************************************************************/
uint8_t ds18b20_check(void){
  
	uint8_t retry = 0;
  
	ds18b20_io_in();
  while(DS18B20_DQ_IN && retry < 200) {
    retry++;
    ds18b20_delay_us(1);
  }

  if(retry >= 200) {
    return 1;
	} else {
    retry = 0;
	}

  while(!DS18B20_DQ_IN && retry < 240) {
    retry++;
    ds18b20_delay_us(1);
  }

  if(retry >= 240) {
    return 1;
	}
  return 0;
}
/**************************************************************************************
* 函数名称：ds18b20_read_bit
* 功能描述：读取一个bit数据
* 入口参数：无
* 出口参数：读取数据的一个bit位
* 返 回 值：无
* 说    明：无
***************************************************************************************/
uint8_t ds18b20_read_bit(void){
    
  uint8_t data =0;
	
  ds18b20_io_out();
  DS18B20_DQ_OUT_LOW;
  ds18b20_delay_us(2);
  DS18B20_DQ_OUT_HIGH;
  ds18b20_io_in();
  ds18b20_delay_us(12);

  if(DS18B20_DQ_IN) {
    data = 1;
	} else {
    data = 0;
	}
  ds18b20_delay_us(50);
  return data;
}
/**************************************************************************************
* 函数名称：ds18b20_read_byte
* 功能描述：读取一个字节数据
* 入口参数：无
* 出口参数：无
* 返 回 值：无
* 说    明：无
***************************************************************************************/
uint8_t ds18b20_read_byte(void){
  uint8_t i=0;
  uint8_t j=0;
  uint8_t data=0;
	
  for(i=1;i<=8;i++) {
    j = ds18b20_read_bit();
    data = (j<<7)|(data>>1);
  }
  return data;
}
/**************************************************************************************
* 函数名称：ds18b20_write_byte
* 功能描述：写入一个字节数据
* 入口参数：无
* 出口参数：写入1字节数据
* 返 回 值：无
* 说    明：无
***************************************************************************************/
void ds18b20_write_byte(uint8_t data){
	
  uint8_t j =0;
  uint8_t testb =0;

  ds18b20_io_out();
  for(j=1;j<=8;j++){
    testb=data&0x01;
    data=data>>1;
    if(testb) {
      DS18B20_DQ_OUT_LOW;
      ds18b20_delay_us(2);
      DS18B20_DQ_OUT_HIGH;
      ds18b20_delay_us(60);
    } else {
      DS18B20_DQ_OUT_LOW;
      ds18b20_delay_us(60);
      DS18B20_DQ_OUT_HIGH;
      ds18b20_delay_us(2);
    }
  }
}
/**************************************************************************************
* 函数名称：ds18b20_start
* 功能描述：ds18b20读取数据起始
* 入口参数：无
* 出口参数：无
* 返 回 值：无
* 说    明：无
***************************************************************************************/
void ds18b20_start(void){
    ds18b20_rst();
    ds18b20_check();
    ds18b20_write_byte(0xcc);
    ds18b20_write_byte(0x44);
}
/**************************************************************************************
* 函数名称：ds18b20_init
* 功能描述：ds18b20初始化
* 入口参数：无
* 出口参数：0-设备存在,1-设备不存在或异常
* 返 回 值：无
* 说    明：需要配置GPIO
***************************************************************************************/
uint8_t ds18b20_init(void){
	
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.Pin = DS18B20_Pin;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull = GPIO_PULLUP;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(DS18B20_Port,&GPIO_InitStructure);

    ds18b20_rst();
    return ds18b20_check();
}
/**************************************************************************************
* 函数名称：ds18b20_get_data
* 功能描述：读取到温湿度数据
* 入口参数：无
* 出口参数：无
* 返 回 值：无
* 说    明：读取到的数据为实际温度的10倍,例如读取数据是123,这实际的温度为12.3摄氏度
***************************************************************************************/
int16_t ds18b20_get_data(void){
  
	uint8_t temp =0;
  uint8_t TL= 0;
  uint8_t TH= 0;
  int16_t temperature =0;

  ds18b20_start();
  ds18b20_rst();
  ds18b20_check();
  ds18b20_write_byte(0xcc);
  ds18b20_write_byte(0xbe);
  TL = ds18b20_read_byte();
  TH = ds18b20_read_byte();

  if(TH>7) {
    TH = ~TH;
    TL = ~TL;
    temp = 0;
  } else {
    temp = 1;
  }
  temperature = TH;
  temperature <<= 8;
  temperature += TL;
  temperature = (float)temperature*0.625;
  if(temp) {
    return temperature;
  } else {
    return -temperature;
  }
}

