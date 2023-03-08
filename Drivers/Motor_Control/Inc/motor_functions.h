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

#define FCLK 84 // MHz
#define PSC 0x0010 // prescaler 
#define STEP_ANGLE 1.8F

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
  * @param speed commanded speed of motors
  * @param wheelRadius radius of wheel for motor to drive
  */
typedef struct {
  TIM_HandleTypeDef *timer;
  motor_config_t rightMotor;
  motor_config_t leftMotor;
  float speed;
  float wheelRadius;
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
 * @param wheelRadius radius of wheel to calculate linear speeds 
 * @retval None
 */
void MOTOR_initialize_motor_instance(motor_instance_t *motorInstance, TIM_HandleTypeDef *timer, motor_config_t rightMotor, motor_config_t leftMotor, float wheelRadius);

/**
  * @brief Move forwad at given speed
  * @param speed commanded speed to move motors forward
  * @param motors struct instance of motors
  * @retval None
  */
void MOTOR_move_speed_forward(float speed, motor_instance_t *motors, uint32_t autoReloadRegister);

/**
  * @brief Move backward at given speed
  * @param speed commanded speed to move motors backward
  * @param motors struct instance of motors
  * @retval None
  */
void MOTOR_move_speed_backward(float speed, motor_instance_t *motors, uint32_t autoReloadRegister);

/**
  * @brief Stop both motors
  * @param motors struct instance of motors
  * @retval None
  */
void MOTOR_stop_both(motor_instance_t *motors);

/**
  * @brief Turn right
  * @param angle commanded angle to turn right
  * @param motors struct instance of motors
  * @retval None
  */
void MOTOR_turn_right(float angle, float speed, motor_instance_t *motors, uint32_t autoReloadRegister);

/**
  * @brief Turn left
  * @param angle commanded angle to turn left
  * @param motors struct instance of motors
  * @retval None
  */
void MOTOR_turn_left(float angle, float speed, motor_instance_t *motors, uint32_t autoReloadRegister);


 #endif /* __MOTOR_CONTROL_H */