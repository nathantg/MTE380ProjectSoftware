/**
  ******************************************************************************
  * @file           : forward_stop.c
  * @brief          : functions for forward then stop controls
  ******************************************************************************
*/

#include "forward_stop.h"

void forward_stop(motor_instance_t *motorInstance, swtiches_config_t *switchConfig, ADC_HandleTypeDef *adc) {
    // move motors forward
    MOTOR_move_speed_forward(20000, motorInstance);

    // when ultrasonic detects distance of 10 in or limit swtich is engaged
    float distance = 10000;

    // while loop exits when distance of at least 10 in is reached or limit switch is engaged
    while((distance > 10) || (SWITCHES_get_limit_switch(switchConfig) != 1)) {
        MB1040_get_distance(adc, &distance);
    }

    // stop motors 
    MOTOR_stop_both(motorInstance);
}

