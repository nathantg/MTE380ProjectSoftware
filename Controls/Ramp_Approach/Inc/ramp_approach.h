/**
  ******************************************************************************
  * @file           : ramp_approach.h
  * @brief          : Header for ramp_approach.c file.
  *                   This file contains the functions prototypes for the rampa approach
  *                   algorithm
  ******************************************************************************
*/

#ifndef __RAMP_APPROACH_H
#define __RAMP_APPROACH_H

#include "main.h"
#include "motor_functions.h"
#include "switches.h"
#include "MB1040.h"
#include "mpu6050.h"
#include "logging.h"

void ramp_approach(UART_HandleTypeDef *huart,motor_instance_t *motorInstance, switches_instance_t *switchInstance, ADC_HandleTypeDef *adc, MPU6050_t *gyro, I2C_HandleTypeDef *i2c);

#endif