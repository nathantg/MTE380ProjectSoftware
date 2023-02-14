/**
  ******************************************************************************
  * @file           : ultrasonic.c
  * @brief          : functions for ultrasonic sensor
  ******************************************************************************
  */

 #include "ultrasonic.h"

 void ULTRASONIC_init_config(ultrasonic_conig_t *ultrasonic, uint16_t directionPin, GPIO_TypeDef *directionPinPort, 
                                                            uint16_t trigPin, GPIO_TypeDef *trigPinPort,
                                                            uint16_t echoPin, GPIO_TypeDef *echoPinPort) {
  ultrasonic->directionPinPort = directionPinPort;
  ultrasonic->directionPin = directionPin;
  ultrasonic->trigPin = trigPin;
  ultrasonic->trigPinPort = trigPinPort;
  ultrasonic->echoPin = echoPin;
  ultrasonic->echoPinPort = echoPinPort;
 }

 void ULTRASONIC_get_distance(uint32_t *distance, ultrasonic_conig_t *ultrasonic) {
  HAL_GPIO_WritePin(ultrasonic->trigPinPort, ultrasonic->trigPin, 1);
  HAL_Delay(1); // this delay is too long. Change later
  uint32_t t1 = HAL_GetTick();
  while(HAL_GPIO_ReadPin(ultrasonic->echoPinPort, ultrasonic->echoPin) == 0) {}
  uint32_t t2 = HAL_GetTick();
  uint32_t pulseWidth = t2 - t1;

  *distance = pulseWidth / 58; // distance in cm
 }