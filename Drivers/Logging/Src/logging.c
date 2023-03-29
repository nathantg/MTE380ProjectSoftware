/**
  ******************************************************************************
  * @file           : logging.c
  * @brief          : functions for logging
  ******************************************************************************
  */

 #include "logging.h"
 #include <stdio.h>
 #include <string.h>

void logging(UART_HandleTypeDef *huart, float distance, switches_instance_t *switchesInstance, motor_instance_t *motorInstance, MPU6050_t *gyroInstance) {
    uint8_t buf[100];

    distance *= 100;
    sprintf((char*)buf, 
            "Distance: %u.%u in, Pitch: %u.%u, Roll: %u.%u, RightLimit: %d, LeftLimit: %d\r\n",
            ((unsigned int)distance / 100),
            ((unsigned int)distance % 100), 
            ((unsigned int)gyroInstance->KalmanAngleX / 100),
            ((unsigned int)gyroInstance->KalmanAngleX % 100),  
            ((unsigned int)gyroInstance->KalmanAngleY / 100),
            ((unsigned int)gyroInstance->KalmanAngleY % 100),
            switchesInstance->rightLimitSwitch->switchStatus,
            switchesInstance->leftLimitSwitch->switchStatus);

    HAL_UART_Transmit(huart, buf, strlen((char*)buf), HAL_MAX_DELAY);
 }