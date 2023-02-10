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
  BACKWARD = 0,
  FORWARD = 1,
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
  * @brief Move forwad at given speed
  * @param speed commanded speed to move motors forward
  * @param motors struct instance of motors
  * @retval None
  */
void MOTOR_move_speed_forward(float speed, motor_instance_t motors);

/**
  * @brief Move backward at given speed
  * @param speed commanded speed to move motors backward
  * @param motors struct instance of motors
  * @retval None
  */
void MOTOR_move_speed_backward(float speed, motor_instance_t motors);

/**
  * @brief Stop both motors
  * @param motors struct instance of motors
  * @retval None
  */
void MOTOR_stop_both(motor_instance_t motors);

/**
  * @brief Turn right
  * @param angle commanded angle to turn right
  * @param motors struct instance of motors
  * @retval None
  */
void MOTOR_turn_right(float angle, float speed, motor_instance_t motors);

/**
  * @brief Turn left
  * @param angle commanded angle to turn left
  * @param motors struct instance of motors
  * @retval None
  */
void MOTOR_turn_left(float angle, float speed, motor_instance_t motors);


 #endif /* __MOTOR_CONTROL_H */