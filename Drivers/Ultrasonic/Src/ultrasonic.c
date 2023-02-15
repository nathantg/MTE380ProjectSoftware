/**
  ******************************************************************************
  * @file           : ultrasonic.c
  * @brief          : functions for ultrasonic sensor
  ******************************************************************************
  */

 #include "ultrasonic.h"
 #include "main.h"

 void ULTRASONIC_init_config(ultrasonic_conig_t *ultrasonic, 
                             uint16_t trigPin, GPIO_TypeDef *trigPinPort,
                             uint16_t echoPin, GPIO_TypeDef *echoPinPort) {
  ultrasonic->trigPin = trigPin;
  ultrasonic->trigPinPort = trigPinPort;
  ultrasonic->echoPin = echoPin;
  ultrasonic->echoPinPort = echoPinPort;
 }

 void ULTRASONIC_get_distance(float *distance, ultrasonic_conig_t *ultrasonic) {
  HAL_GPIO_WritePin(ultrasonic->trigPinPort, ultrasonic->trigPin, 1);
  HAL_Delay(0.5); // this delay is too long. Change later
  HAL_GPIO_WritePin(ultrasonic->trigPinPort, ultrasonic->trigPin, 0);

  while(HAL_GPIO_ReadPin(ultrasonic->echoPinPort, ultrasonic->echoPin) == 0) {} // wait for echo pin to respond

  uint32_t t1 = HAL_GetTick();
  while(HAL_GPIO_ReadPin(ultrasonic->echoPinPort, ultrasonic->echoPin) == 1) {} // while echo is on
  uint32_t t2 = HAL_GetTick();

  uint32_t pulseWidth = t2 - t1;
  pulseWidth = pulseWidth / 1000; // convert ms to us

  *distance = (float) pulseWidth / (float) 58; // distance in cm
 }
