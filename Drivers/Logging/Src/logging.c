/**
  ******************************************************************************
  * @file           : logging.c
  * @brief          : functions for logging
  ******************************************************************************
  */

 #include "logging.h"
 #include <stdio.h>
 #include <string.h>

 void logging(UART_HandleTypeDef huart, float distance, uint8_t limitSwitchValue, uint8_t tiltSwitchValue, motor_instance_t *motorInstance) {
    uint8_t buf[100];

    distance *= 100;
    sprintf((char*)buf, 
            "Distance: %u.%u in, Limit Switch %d, Tilt Switch %d, PWM ARR: %d\r\n",
            ((unsigned int)distance / 100),
            ((unsigned int)distance % 100), 
            limitSwitchValue, 
            tiltSwitchValue, 
            (int)motorInstance->autoReloadRegister);

    HAL_UART_Transmit(&huart, buf, strlen((char*)buf), HAL_MAX_DELAY);
 }