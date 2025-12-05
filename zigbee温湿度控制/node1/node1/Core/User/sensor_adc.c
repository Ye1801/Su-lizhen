#include "sensor_adc.h"

#define ADC_value_max 4 


void sensor_adc_init(void)
{
  HAL_ADCEx_Calibration_Start(&hadc1);
}

uint16_t sensor_adc_get(void)
{
	HAL_ADC_Start(&hadc1);  
	HAL_ADC_PollForConversion(&hadc1, 50);   

	if(HAL_IS_BIT_SET(HAL_ADC_GetState(&hadc1), HAL_ADC_STATE_REG_EOC))
	{
		return(HAL_ADC_GetValue(&hadc1));
	}
	return 0;
}

uint16_t sensor_adc_channel(uint8_t channel)
{
	uint16_t ADC_value[ADC_value_max] = {0};

  for(uint8_t i=0;i<ADC_value_max;i++)
  {
    ADC_value[i] = sensor_adc_get();
  }
  return ADC_value[channel];
}

