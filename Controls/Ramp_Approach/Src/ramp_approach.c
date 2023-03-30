/**
  ******************************************************************************
  * @file           : ramp_approach.c
  * @brief          : functions for ramp approach algorithm
  ******************************************************************************
*/

#include "ramp_approach.h"

static void turn_left_90_degrees(motor_instance_t *motorInstance) {
  MOTOR_turn_left(30000, motorInstance);
  HAL_Delay(2000); // Change delay for 90 degree turn
  MOTOR_stop_both(motorInstance);
  HAL_Delay(500);
}

static void turn_right_90_degrees(motor_instance_t *motorInstance) {
  MOTOR_turn_right(30000, motorInstance);
  HAL_Delay(5500); // Change delay for 90 degree turn
  MOTOR_stop_both(motorInstance);
  HAL_Delay(500);
}

static void wall_align(UART_HandleTypeDef *huart, motor_instance_t *motorInstance, switches_instance_t *switchInstance, MPU6050_t *gyro) {
  while(1) {
    MOTOR_move_speed_forward(10000, motorInstance);

    while(!((SWITCHES_get_right_limit_switch(switchInstance) || SWITCHES_get_left_limit_switch(switchInstance)))) {
      #ifdef LOGGING
      logging(huart, 0, switchInstance, motorInstance, NULL);
      #endif 
    }
    HAL_Delay(200);

    MOTOR_stop_both(motorInstance);

    if((SWITCHES_get_right_limit_switch(switchInstance) && SWITCHES_get_left_limit_switch(switchInstance))) {
      break;
    } 
    else if(SWITCHES_get_right_limit_switch(switchInstance) && !SWITCHES_get_left_limit_switch(switchInstance)) {
      MOTOR_move_speed_backward(10000, motorInstance);
      HAL_Delay(1000);
      MOTOR_turn_right(10000, motorInstance);
      HAL_Delay(500);
    }
    else if(!SWITCHES_get_right_limit_switch(switchInstance) && SWITCHES_get_left_limit_switch(switchInstance)) {
      MOTOR_move_speed_backward(10000, motorInstance);
      HAL_Delay(1000);
      MOTOR_turn_left(10000, motorInstance);
      HAL_Delay(500);
    }

    MOTOR_stop_both(motorInstance);
    HAL_Delay(500);
  }
}

void ramp_approach(UART_HandleTypeDef *huart,motor_instance_t *motorInstance, switches_instance_t *switchInstance, ADC_HandleTypeDef *adc, MPU6050_t *gyro, I2C_HandleTypeDef *i2c) {
  turn_right_90_degrees(motorInstance);

  MOTOR_move_speed_forward(10000, motorInstance);

  while(!SWITCHES_get_right_limit_switch(switchInstance) && !SWITCHES_get_left_limit_switch(switchInstance)) {
    #ifdef LOGGING
    logging(huart, 0, switchInstance, motorInstance, NULL);
    #endif 
  }

  MOTOR_stop_both(motorInstance);

  wall_align(huart, motorInstance, switchInstance, gyro);

  MOTOR_move_speed_backward(10000, motorInstance);
  HAL_Delay(500);

  MOTOR_stop_both(motorInstance);
  HAL_Delay(500);

  turn_left_90_degrees(motorInstance);

  MOTOR_move_speed_forward(10000, motorInstance);
}
