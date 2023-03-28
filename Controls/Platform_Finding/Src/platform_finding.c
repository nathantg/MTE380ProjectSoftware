/**
  ******************************************************************************
  * @file           : platform_finding.c
  * @brief          : functions for platform finding algorithm
  ******************************************************************************
*/

#include "platform_finding.h"

void platform_finding_brute_force(motor_instance_t *motorInstance, switches_instance_t *switchInstance, ADC_HandleTypeDef *adc, MPU6050_t *gyro, I2C_HandleTypeDef *i2c) {
  while(1) {
    // left u-turn
    turn_left_90_degrees(motorInstance);
    u_turn_straight(motorInstance);
    turn_left_90_degrees(motorInstance);

    // Straight to other side 
    MOTOR_move_speed_forward(10000, motorInstance);
    HAL_Delay(10000); // Change delay for straight between u-turns
    MOTOR_stop_both(motorInstance);

    // right u-turn
    turn_right_90_degrees(motorInstance);
    u_turn_straight(motorInstance);
    turn_right_90_degrees(motorInstance);

    // Straight to other side 
    MOTOR_move_speed_forward(10000, motorInstance);
    HAL_Delay(10000); // Change delay for straight between u-turns
    MOTOR_stop_both(motorInstance);
  }
}

void platform_finding_circle_scan(motor_instance_t *motorInstance, switches_instance_t *switchInstance, ADC_HandleTypeDef *adc, MPU6050_t *gyro, I2C_HandleTypeDef *i2c) {
  // Scan in corner after ramp

  // Scan in centre

  // Scan in opposite corner

  // Scan in adjacent corner

}

void platform_finding_side_scan(motor_instance_t *motorInstance, switches_instance_t *switchInstance, ADC_HandleTypeDef *adc, MPU6050_t *gyro, I2C_HandleTypeDef *i2c) {
  // Move to boundary after course
  MOTOR_move_speed_forward(10000, motorInstance);
  while(!SWITCHES_get_right_limit_switch(switchInstance) || !SWITCHES_get_left_limit_switch(switchInstance)) {} // Wait for both limit switches to engage (or maybe change to one)
  MOTOR_stop_both(motorInstance);

  // Turn left 90 degrees
  turn_left_90_degrees(motorInstance);

  // Move forward and scan for red pillar
  uint8_t pillarFound = 0;
  MOTOR_move_speed_forward(1000, motorInstance);

  while((!SWITCHES_get_right_limit_switch(switchInstance) || !SWITCHES_get_left_limit_switch(switchInstance)) && !pillarFound) { // Wait for both limit switches to engage (or maybe change to one)
    float distance;
    MB1040_get_distance(adc, &distance);

    if(distance < PILLAR_MAX_DISTANCE) {
      pillarFound = 1;
    }
  }
  
  uint8_t platformFound = 0;
  if(pillarFound) {
    turn_left_90_degrees(motorInstance);
    MOTOR_move_speed_forward(10000, motorInstance);

    while(!platformFound) {
      MPU6050_Read_All(i2c, gyro);

      if((gyro->KalmanAngleX > PLATFORM_ROLL_THRESHOLD) || (gyro->KalmanAngleY > PLATFORM_PITCH_THRESHOLD) || SWITCHES_get_right_limit_switch(switchInstance) || SWITCHES_get_left_limit_switch(switchInstance)) {
        platformFound = 1;
        MOTOR_stop_both(motorInstance);
        HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, 1);
      }
    }
  }

  MOTOR_stop_both(motorInstance);
}

void u_turn_straight(motor_instance_t *motorInstance) {
  MOTOR_move_speed_forward(30000, motorInstance);
  HAL_Delay(500); // Change delay for straight part of u-turn
  MOTOR_stop_both(motorInstance);
  HAL_Delay(500);
}
void turn_left_90_degrees(motor_instance_t *motorInstance) {
  MOTOR_turn_left(30000, motorInstance);
  HAL_Delay(2000); // Change delay for 90 degree turn
  MOTOR_stop_both(motorInstance);
  HAL_Delay(500);
}

void turn_right_90_degrees(motor_instance_t *motorInstance) {
  MOTOR_turn_right(30000, motorInstance);
  HAL_Delay(2000); // Change delay for 90 degree turn
  MOTOR_stop_both(motorInstance);
  HAL_Delay(500);
}