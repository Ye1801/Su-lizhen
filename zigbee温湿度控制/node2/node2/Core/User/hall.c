#include "hall.h"

void hall1_init(void) {
}

void hall2_init(void) {
}

void hall3_init(void) {
}

void hall4_init(void) {
}

void hall5_init(void) {
}

uint8_t hall1_get() {
	uint8_t value = HAL_GPIO_ReadPin(HALL1_PORT, HALL1_PIN);
	if(value==1) {
		value=0;
	} else {
		value=1;
	}
  return value;
}

uint8_t hall2_get() {
	uint8_t value = HAL_GPIO_ReadPin(HALL2_PORT, HALL2_PIN);
	if(value==1) {
		value=0;
	} else {
		value=1;
	}
  return value;
}

uint8_t hall3_get() {
	uint8_t value = HAL_GPIO_ReadPin(HALL3_PORT, HALL3_PIN);
	if(value==1) {
		value=0;
	} else {
		value=1;
	}
  return value;
}

uint8_t hall4_get() {
	uint8_t value = HAL_GPIO_ReadPin(HALL4_PORT, HALL4_PIN);
	if(value==1) {
		value=0;
	} else {
		value=1;
	}
  return value;
}

uint8_t hall5_get() {
	uint8_t value = HAL_GPIO_ReadPin(HALL5_PORT, HALL5_PIN);
	if(value==1) {
		value=0;
	} else {
		value=1;
	}
  return value;
}

