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
   FORWARD,
   BACKWARD,
} motor_direction_t;

/**
  * @brief Struct to hold current status of motors
  * @param direction direction of motor
  * @param speed current speed of motor
  * @retval None
  */
typedef struct {
   motor_direction_t direction;
   float speed;
} motor_instance_t;
 
/**
  * @brief Move forwad at given speed
  * @param speed commanded speed to move motors forward
  * @param rightMotor struct instance for right motor
  * @param leftMotor struct instance for left motor
  * @retval None
  */
void MOTOR_move_speed_forward(float speed, motor_instance_t rightMotor, motor_instance_t leftMotor);

/**
  * @brief Move backward at given speed
  * @param speed commanded speed to move motors backward
  * @param rightMotor struct instance for right motor
  * @param leftMotor struct instance for left motor
  * @retval None
  */
void MOTOR_move_speed_backward(float speed, motor_instance_t rightMotor, motor_instance_t leftMotor);

/**
  * @brief Stop both motors
  * @param None
  * @retval None
  */
void MOTOR_stop_both();

/**
  * @brief Turn right
  * @param angle commanded angle to turn right
  * @param rightMotor struct instance for right motor
  * @param leftMotor struct instance for left motor
  * @retval None
  */
void MOTOR_turn_right(float angle, motor_instance_t rightMotor, motor_instance_t leftMotor);

/**
  * @brief Turn left
  * @param angle commanded angle to turn left
  * @param rightMotor struct instance for right motor
  * @param leftMotor struct instance for left motor
  * @retval None
  */
void MOTOR_turn_left(float angle, motor_instance_t rightMotor, motor_instance_t leftMotor);


 #endif /* __MOTOR_CONTROL_H */