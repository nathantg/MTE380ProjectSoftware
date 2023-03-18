/**
  ******************************************************************************
  * @file           : motor_functions.h
  * @brief          : Header for motor_functions.c file.
  *                   This file contains the prototypes for the motor control 
  *                   functions
  ******************************************************************************
*/

#ifndef __MOTOR_CONTROL_H
#define __MOTOR_CONTROL_H

#include <stdio.h>
#include <stdlib.h>
#include "main.h"

typedef enum {
  RIGHT_BACKWARD = 0,
  RIGHT_FORWARD = 1,
  LEFT_BACKWARD = 1,
  LEFT_FORWARD = 0,
  NO_DIRECTION = 2,
} motor_direction_t;

/**
  * @brief Struct to hold configuration of a single motor
  * @param directionPin microcontroller pin for motor driver DIR pin
  * @param direction commanded direction for motor
  * @retval None
  */
typedef struct {
  uint16_t directionPin;
  GPIO_TypeDef *directionPinPort;
  motor_direction_t direction;
} motor_config_t;

/**
  * @brief Struct to hold current status of motors
  * @param timer PWM timer handle
  * @param rightMotor configuration for right motor
  * @param leftMotor configuration for left motor
  * @param autoReloadRegister value for the ARR to change the PWM frequency
  */
typedef struct {
  TIM_HandleTypeDef *timer;
  motor_config_t rightMotor;
  motor_config_t leftMotor;
  uint32_t autoReloadRegister;
} motor_instance_t;

/**
 * @brief Initialize single motor configuration
 * @param motorConfig pointer to motor configuration instance
 * @param directionPinPort pointer to GPIO port for microcontroller pin assigned for DIR pin of motor driver
 * @param directionPin microcontroller pin assigned for DIR pin of motor driver
 * @retval None
 */
void MOTOR_initialize_motor_config(motor_config_t *motorConfig, GPIO_TypeDef *directionPinPort, uint16_t directionPin);

/**
 * @brief Initialize motor instance
 * @param timer pointer to PWM timer handle
 * @param rightMotor motor configuration for right motor
 * @param leftMotor motor configuration for left motor
 * @retval None
 */
void MOTOR_initialize_motor_instance(motor_instance_t *motorInstance, TIM_HandleTypeDef *timer, motor_config_t rightMotor, motor_config_t leftMotor);
 
/**
  * @brief Move forwad at given speed
  * @param autoReloadRegister value for the ARR to change the PWM frequency
  * @param motors struct instance of motors
  * @retval None
  */
void MOTOR_move_speed_forward(uint32_t autoReloadRegister, motor_instance_t *motors);

/**
  * @brief Move forwad at given speed
  * @param autoReloadRegister value for the ARR to change the PWM frequency
  * @param motors struct instance of motors
  * @retval None
  */
void MOTOR_move_speed_forward_accel(uint32_t autoReloadRegister, motor_instance_t *motors);

/**
  * @brief Move backward at given speed
  * @param autoReloadRegister value for the ARR to change the PWM frequency
  * @param motors struct instance of motors
  * @retval None
  */
void MOTOR_move_speed_backward(uint32_t autoReloadRegister, motor_instance_t *motors);

/**
  * @brief Stop both motors
  * @param motors struct instance of motors
  * @retval None
  */
void MOTOR_stop_both(motor_instance_t *motors);

/**
  * @brief Turn right
  * @param autoReloadRegister value for the ARR to change the PWM frequency
  * @param motors struct instance of motors
  * @retval None
  */
void MOTOR_turn_right(uint32_t autoReloadRegister, motor_instance_t *motors);

/**
  * @brief Turn left
  * @param autoReloadRegister value for the ARR to change the PWM frequency
  * @param motors struct instance of motors
  * @retval None
  */
void MOTOR_turn_left(uint32_t autoReloadRegister, motor_instance_t *motors);


 #endif /* __MOTOR_CONTROL_H */