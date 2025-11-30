/****************************************功能说明****************************************
3.通道可选 0 1 2 3   PA4 PA4 PA6 PA7
****************************************功能说明****************************************/
#include "adc_sensor.h"

#define ADC_value_max 8

/*
*************************************
连续ADC采集初始化
*************************************
*/
void adc_sensor_init(void)
{
  HAL_ADCEx_Calibration_Start(&hadc1);
}
/*
*************************************
获取多组连续采集数据
*************************************
*/
uint16_t and_sensor_get_data(void)
{
	HAL_ADC_Start(&hadc1);  
	HAL_ADC_PollForConversion(&hadc1, 50);   

	if(HAL_IS_BIT_SET(HAL_ADC_GetState(&hadc1), HAL_ADC_STATE_REG_EOC))
	{
		return(HAL_ADC_GetValue(&hadc1));
	}
	return 0;
}
/*
*************************************
获取指定通道采集数据，输出电压
*************************************
*/
uint16_t adc_sensor_get(uint8_t channel)
{
	uint16_t ADC_value[ADC_value_max] = {0};

  for(uint8_t i=0;i<ADC_value_max;i++)
  {
    ADC_value[i] = and_sensor_get_data();
  }
	
	int value = ADC_value[channel];  
	float normalizedValue = (float)value / 4096; 
	uint16_t percentage = normalizedValue*33000;
  return percentage;
}

