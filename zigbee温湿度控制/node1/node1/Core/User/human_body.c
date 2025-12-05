#include "human_body.h"

void human_body1_init(void) {
}

void human_body2_init(void) {
}

void human_body3_init(void) {
}

void human_body4_init(void) {
}

void human_body5_init(void) {
}

uint8_t human_body1_get() {
  return HAL_GPIO_ReadPin(HUMAN_BODY1_PORT, HUMAN_BODY1_PIN);
}

uint8_t human_body2_get() {
  return HAL_GPIO_ReadPin(HUMAN_BODY2_PORT, HUMAN_BODY2_PIN);
}

uint8_t human_body3_get() {
  return HAL_GPIO_ReadPin(HUMAN_BODY3_PORT, HUMAN_BODY3_PIN);
}

uint8_t human_body4_get() {
  return HAL_GPIO_ReadPin(HUMAN_BODY4_PORT, HUMAN_BODY4_PIN);
}

uint8_t human_body5_get() {
  return HAL_GPIO_ReadPin(HUMAN_BODY5_PORT, HUMAN_BODY5_PIN);
}

