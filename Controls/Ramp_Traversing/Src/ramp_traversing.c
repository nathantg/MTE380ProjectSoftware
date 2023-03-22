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
    MOTOR_move_speed_forward(45000, motorInstance);
    HAL_Delay(60000);
    MOTOR_stop_both(motorInstance);

    // while(HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == 1)
    // {}
    // MOTOR_mov_speed_forward(42000, motorInstance);
    // HAL_Delay(2000);
    // MOTOR_stop_both(motorInstance);

    // while(HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == 1)
    // {}
    // MOTOR_move_speed_forward(60000, motorInstance);
    // HAL_Delay(2000);
    // MOTOR_stop_both(motorInstance);
}


// void ramp_approach(motor_instance_t *motorInstance, swtiches_config_t *switchConfig, ADC_HandleTypeDef *adc) {
//     MOTOR_stop_both(motorInstance);

//     uint32_t speed = 60000, move1_time_max = 1000, move1_expected_distance = 50;
//     uint32_t move2_travel_time_max = 5000, move2_rotate_expected_distance = 50, move2_distance_stop;
//     uint32_t current_distance;
//     while(HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == 1)
//     {}
//     MOTOR_move_speed_forward(speed, motorInstance);
//     HAL_Delay(forward_delay); /* Value will be determined through trial and error */
//     MOTOR_stop_both(motorInstance);
//     HAL_Delay(500);

//     MOTOR_turn_right(60000, motorInstance);
//     MB1040_get_distance(adc, &current_distance);
//     while((current_distance > 10) || (SWITCHES_get_limit_switch(switchConfig) != 1)) {
//         MB1040_get_distance(adc, &current_distance);
//     }

//     MOTOR_move_speed_forward(42000, motorInstance);
//     HAL_Delay(2000);
//     MOTOR_stop_both(motorInstance);

//     while(HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == 1)
//     {}
//     MOTOR_move_speed_forward(60000, motorInstance);
//     HAL_Delay(2000);
//     MOTOR_stop_both(motorInstance);
// }
