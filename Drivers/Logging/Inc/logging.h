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

/**
 * @brief Initialize limit and tilt switch configuration
 * @param limitSwitchValue variable with limit switch value
 * @param tiltSwitchValue variable with tilt switch value
 * @param distance variable with distance value
 * @param motorInstance pointer to motor instance struct
 * @retval None
 */
void logging(UART_HandleTypeDef *huart, float distance, uint8_t limitSwitchValue, uint8_t tiltSwitchValue, motor_instance_t *motorInstance);

#endif /* __LOGGING_H */