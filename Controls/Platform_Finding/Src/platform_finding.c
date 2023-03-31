/**
  ******************************************************************************
  * @file           : platform_finding.c
  * @brief          : functions for platform finding algorithm
  ******************************************************************************
*/

#include "platform_finding.h"

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

static void u_turn_left(motor_instance_t *motorInstance) {
  MOTOR_move_speed_backward(10000, motorInstance);
  HAL_Delay(500); // Change delay 
  MOTOR_stop_both(motorInstance);
  HAL_Delay(500);
  turn_left_90_degrees(motorInstance);
  HAL_Delay(500);
  MOTOR_move_speed_forward(10000, motorInstance);
  HAL_Delay(500); // Change delay 
  MOTOR_stop_both(motorInstance);
  HAL_Delay(500);
  turn_left_90_degrees(motorInstance);
  HAL_Delay(500);
}

static void u_turn_right(motor_instance_t *motorInstance) {
  MOTOR_move_speed_backward(10000, motorInstance);
  HAL_Delay(500); // Change delay 
  MOTOR_stop_both(motorInstance);
  HAL_Delay(500);
  turn_right_90_degrees(motorInstance);
  HAL_Delay(500);
  MOTOR_move_speed_forward(10000, motorInstance);
  HAL_Delay(500); // Change delay 
  MOTOR_stop_both(motorInstance);
  HAL_Delay(500);
  turn_right_90_degrees(motorInstance);
  HAL_Delay(500);
}

void wall_align(UART_HandleTypeDef *huart, motor_instance_t *motorInstance, switches_instance_t *switchInstance, MPU6050_t *gyro) {
  while(1) {
    MOTOR_move_speed_forward(10000, motorInstance);

    while(!SWITCHES_get_right_limit_switch(switchInstance) && !SWITCHES_get_left_limit_switch(switchInstance)) {
      #ifdef LOGGING
      logging(huart, 0, switchInstance, motorInstance, NULL);
      #endif 
    }
    HAL_Delay(100);

    MOTOR_stop_both(motorInstance);

    if((SWITCHES_get_right_limit_switch(switchInstance) && SWITCHES_get_left_limit_switch(switchInstance))) {
      break;
    } 
    else if(SWITCHES_get_right_limit_switch(switchInstance) && !SWITCHES_get_left_limit_switch(switchInstance)) {
      MOTOR_move_speed_backward(10000, motorInstance);
      HAL_Delay(1000);
      MOTOR_turn_left(10000, motorInstance);
      HAL_Delay(100);
    }
    else if(!SWITCHES_get_right_limit_switch(switchInstance) && SWITCHES_get_left_limit_switch(switchInstance)) {
      MOTOR_move_speed_backward(10000, motorInstance);
      HAL_Delay(1000);
      MOTOR_turn_right(10000, motorInstance);
      HAL_Delay(100);
    }

    MOTOR_stop_both(motorInstance);
    HAL_Delay(500);
  }
}

void platform_finding_brute_force(UART_HandleTypeDef *huart, motor_instance_t *motorInstance, switches_instance_t *switchInstance, ADC_HandleTypeDef *adc, MPU6050_t *gyro, I2C_HandleTypeDef *i2c) {
  uint8_t uTurnRight = 1;
  while(1) {
    // move towards boundary
    MOTOR_move_speed_forward(10000, motorInstance);

    MPU6050_Read_All(i2c, gyro);

    uint8_t noObstacle = (!SWITCHES_get_right_limit_switch(switchInstance) || !SWITCHES_get_left_limit_switch(switchInstance)) && ((gyro->KalmanAngleX > PLATFORM_PITCH_THRESHOLD) || (gyro->KalmanAngleY > PLATFORM_ROLL_THRESHOLD));
    while(noObstacle) {
      #ifdef LOGGING
      logging(huart, 0, switchInstance, motorInstance, NULL);
      #endif 

      noObstacle = (!SWITCHES_get_right_limit_switch(switchInstance) || !SWITCHES_get_left_limit_switch(switchInstance)) && ((gyro->KalmanAngleX > PLATFORM_PITCH_THRESHOLD) || (gyro->KalmanAngleY > PLATFORM_ROLL_THRESHOLD));
    }

    MOTOR_stop_both(motorInstance);
    HAL_Delay(1000);

    // check if boundary or platform
    MPU6050_Read_All(i2c, gyro);

    if((gyro->KalmanAngleX > PLATFORM_PITCH_THRESHOLD) || (gyro->KalmanAngleY > PLATFORM_ROLL_THRESHOLD)) {
      while(1) {
      HAL_GPIO_TogglePin(LD2_GPIO_Port,LD2_Pin);
      HAL_Delay(500);
      } 
    }

    wall_align(huart, motorInstance,switchInstance, gyro);

    if(uTurnRight) {
      u_turn_right(motorInstance);
      uTurnRight = 0;
    }
    else {
      u_turn_left(motorInstance);
      uTurnRight = 1;
    }
  }
}

void platform_finding_circle_scan(motor_instance_t *motorInstance, switches_instance_t *switchInstance, ADC_HandleTypeDef *adc, MPU6050_t *gyro, I2C_HandleTypeDef *i2c) {
  // Scan in corner after ramp

  // Scan in centre

  // Scan in opposite corner

  // Scan in adjacent corner

}

void platform_finding_side_scan(UART_HandleTypeDef *huart, motor_instance_t *motorInstance, switches_instance_t *switchInstance, ADC_HandleTypeDef *adc, MPU6050_t *gyro, I2C_HandleTypeDef *i2c) {
  // Move to scan start position
  // wall_align(huart, motorInstance, switchInstance, gyro);

  // MOTOR_move_speed_backward(10000, motorInstance);
  // HAL_Delay(1000);
  // MOTOR_stop_both(motorInstance);

  float distance;
  float minDistance = 1000;

  // turn_left_90_degrees(motorInstance);

  MOTOR_move_speed_forward(10000, motorInstance);

  // Find the minimum recorded distance
  while((!SWITCHES_get_right_limit_switch(switchInstance) && !SWITCHES_get_left_limit_switch(switchInstance))) {
    MB1040_get_distance(adc, &distance); 
    #ifdef LOGGING
    logging(huart, distance, switchInstance, motorInstance, gyro);
    #endif 

    minDistance = distance < minDistance ? distance : minDistance;
  }

  MOTOR_stop_both(motorInstance);

  // if((gyro->KalmanAngleX > PLATFORM_PITCH_THRESHOLD) || (gyro->KalmanAngleY > PLATFORM_ROLL_THRESHOLD)) {
  //   while(1) {
  //     HAL_GPIO_TogglePin(LD2_GPIO_Port,LD2_Pin);
  //     HAL_Delay(500);
  //   } 
  // }

  HAL_Delay(1000);

  MOTOR_move_speed_backward(10000, motorInstance);

  MB1040_get_distance(adc, &distance); 

  while(distance > minDistance + minDistance * 0.05) { // Back up until point where min distance was measured (with 10% tolerance)
    MB1040_get_distance(adc, &distance); 
    #ifdef LOGGING
    logging(huart, distance, switchInstance, motorInstance, gyro);
    #endif 
  }
  //HAL_Delay(750);
  MOTOR_stop_both(motorInstance);

  HAL_Delay(1000);

  turn_right_90_degrees(motorInstance);
  HAL_Delay(500);

  SWITCHES_get_right_limit_switch(switchInstance);
  SWITCHES_get_left_limit_switch(switchInstance);
  MOTOR_move_speed_forward(10000, motorInstance);

  HAL_Delay(1000);

  uint8_t platformFound = 0;
  while(!platformFound) {
    MPU6050_Read_All(i2c, gyro);
    #ifdef LOGGING
    logging(huart, 0, switchInstance, motorInstance, gyro);
    #endif

    if(gyro->KalmanAngleX > PLATFORM_PITCH_THRESHOLD || gyro->KalmanAngleY > PLATFORM_ROLL_THRESHOLD) {
      platformFound = 1;
    }
  }

  MOTOR_stop_both(motorInstance);
  HAL_Delay(10000);

  if(platformFound) {
    while(1) {
      HAL_GPIO_TogglePin(LD2_GPIO_Port,LD2_Pin);
      HAL_Delay(500);
    } 
  }
  // else {
  //   // move to corner
  //   MOTOR_move_speed_forward(10000, motorInstance);

  //   while(!SWITCHES_get_right_limit_switch(switchInstance) && !SWITCHES_get_left_limit_switch(switchInstance)) {
  //     MPU6050_Read_All(i2c, gyro);
  //     #ifdef LOGGING
  //     logging(huart, 0, switchInstance, motorInstance, gyro);
  //     #endif

  //     // also look for platform

  //   }

  //   wall_align(huart, motorInstance, switchInstance, gyro);
  // }
}