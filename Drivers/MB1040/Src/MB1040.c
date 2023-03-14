/**
  ******************************************************************************
  * @file           : ultrasonic.c
  * @brief          : functions for ultrasonic sensor
  ******************************************************************************
  */

 #include "MB1040.h"
 #include "main.h"

void MB1040_get_distance(ADC_HandleTypeDef *adc, float *distance) {
  HAL_ADC_Start(adc);

  uint16_t raw = HAL_ADC_GetValue(adc);

  *distance = (float)raw / RES * 3.3;
}