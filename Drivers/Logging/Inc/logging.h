/**
  ******************************************************************************
  * @file           : logging.h
  * @brief          : Header for switches.c file.
  *                   This file contains the prototypes for the logging 
  *                   functions
  ******************************************************************************
*/

#ifndef __LOGGING_H
#define __LOGGING_H

#include "main.h"
#include "motor_functions.h"
#include "switches.h"
#include "MB1040.h"
#include "mpu6050.h"

/**
 * @brief Initialize limit and tilt switch configuration
 * @param huart pointer to UART handle
 * @param distance variable with distance value
 * @param switchesInstance pointer to switches instance struct
 * @param motorInstance pointer to motor instance struct
 * @param gyroInstance pointer to gyro instance struct
 * @retval None
 */
void logging(UART_HandleTypeDef *huart, float distance, switches_instance_t *switchesInstance, motor_instance_t *motorInstance, MPU6050_t *gyroInstance);

#endif /* __LOGGING_H */