/**
  ******************************************************************************
  * @file           : forward_stop.c
  * @brief          : functions for forward then stop controls
  ******************************************************************************
*/

#include "flat_terrain.h"

void flat_terrain(motor_instance_t *motorInstance) {
  while(HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == 1) {}

  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, 1);

  // move motors forward
  MOTOR_move_speed_forward(20000, motorInstance);

  HAL_Delay(2000);

  // stop motors 
  MOTOR_stop_both(motorInstance);

  HAL_Delay(1000);

  // turn right
  MOTOR_turn_right(20000, motorInstance);

  HAL_Delay(2000);

  MOTOR_stop_both(motorInstance);

  HAL_Delay(1000);

  // turn left
  MOTOR_turn_left(20000, motorInstance);

  HAL_Delay(2000);

  MOTOR_stop_both(motorInstance);

  HAL_Delay(1000);

  // move motors backwards
  MOTOR_move_speed_backward(20000, motorInstance);

  HAL_Delay(2000);

  MOTOR_stop_both(motorInstance);

  HAL_Delay(1000);

  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, 0);
}

