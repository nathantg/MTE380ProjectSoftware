/**
  ******************************************************************************
  * @file           : platform_finding.h
  * @brief          : Header for platform_finding.c file.
  *                   This file contains the functions prototypes for the platform finding
  *                   algorithm
  ******************************************************************************
*/

#ifndef __PLATFORM_FINDING_H
#define __PLATFORM_FINDING_H

#include "main.h"
#include "motor_functions.h"
#include "switches.h"
#include "MB1040.h"
#include "mpu6050.h"
#include "logging.h"

#define PILLAR_DISTANCE_THRESHOLD 10.0f // Distance threshold is 70 inces
#define PLATFORM_PITCH_THRESHOLD 0.16f
#define PLATFORM_ROLL_THRESHOLD 0.1f

/**
  * @brief Brute force platform finding algorithm
  * @param motorInstance pointer to motor instance struct for motor control
  * @param switchInstance pointer to switch instance struct for use of limit and tilt switches
  * @param adc pointer to adc handler used for ultrasonic sensor
  * @param gyro pointer to gyro sensor strcut for use of MPU6050 sensor
  * @param i2c pointer to i2c handler used for MPU6050 sensor
  * @retval None
  */
void platform_finding_brute_force(UART_HandleTypeDef *huart, motor_instance_t *motorInstance, switches_instance_t *switchInstance, ADC_HandleTypeDef *adc, MPU6050_t *gyro, I2C_HandleTypeDef *i2c);

/**
  * @brief Side scanning platform finding algorithm
  * @param motorInstance pointer to motor instance struct for motor control
  * @param switchInstance pointer to switch instance struct for use of limit and tilt switches
  * @param adc pointer to adc handler used for ultrasonic sensor
  * @param gyro pointer to gyro sensor strcut for use of MPU6050 sensor
  * @param i2c pointer to i2c handler used for MPU6050 sensor
  * @retval None
  */
void platform_finding_side_scan(UART_HandleTypeDef *huart,motor_instance_t *motorInstance, switches_instance_t *switchInstance, ADC_HandleTypeDef *adc, MPU6050_t *gyro, I2C_HandleTypeDef *i2c);

/**
  * @brief Circle scan platform finding algorithm
  * @param motorInstance pointer to motor instance struct for motor control
  * @param switchInstance pointer to switch instance struct for use of limit and tilt switches
  * @param adc pointer to adc handler used for ultrasonic sensor
  * @param gyro pointer to gyro sensor strcut for use of MPU6050 sensor
  * @param i2c pointer to i2c handler used for MPU6050 sensor
  * @retval None
  */
void platform_finding_circle_scan(motor_instance_t *motorInstance, switches_instance_t *switchInstance, ADC_HandleTypeDef *adc, MPU6050_t *gyro, I2C_HandleTypeDef *i2c);

#endif /* __PLATFORM_FINDING_H */