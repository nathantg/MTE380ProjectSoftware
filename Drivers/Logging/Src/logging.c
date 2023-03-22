/**
  ******************************************************************************
  * @file           : logging.c
  * @brief          : functions for logging
  ******************************************************************************
  */

 #include "logging.h"
 #include <stdio.h>
 #include <string.h>

 void logging(UART_HandleTypeDef *huart, float distance, switches_instance_t *switchesInstance, motor_instance_t *motorInstance) {
    uint8_t buf[100];

    distance *= 100;
    sprintf((char*)buf, 
            "Distance: %u.%u in, Up Tilt Switch: %d, Down Tilt Switch: %d, PWM ARR: %d\r\n",
            ((unsigned int)distance / 100),
            ((unsigned int)distance % 100), 
            switchesInstance->upTiltSwitch->switchStatus,
            switchesInstance->downTiltSwitch->switchStatus, 
            (int)motorInstance->autoReloadRegister);

    HAL_UART_Transmit(huart, buf, strlen((char*)buf), HAL_MAX_DELAY);
 }