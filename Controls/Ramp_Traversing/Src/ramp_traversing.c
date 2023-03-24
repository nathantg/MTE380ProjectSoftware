/**
  ******************************************************************************
  * @file           : ramp_traversing.c
  * @brief          : functions for ramp traversing algorithm
  ******************************************************************************
*/

#include "ramp_traversing.h"

void ramp_traversal(motor_instance_t *motorInstance, swtiches_config_t *switchConfig, ADC_HandleTypeDef *adc) {
    MOTOR_stop_both(motorInstance);
  
    while(HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == 1)
    {}
    MOTOR_move_speed_forward(10000, motorInstance);
    HAL_Delay(60000);
    MOTOR_stop_both(motorInstance);
}