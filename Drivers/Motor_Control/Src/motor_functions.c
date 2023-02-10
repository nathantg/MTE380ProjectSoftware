/**
  ******************************************************************************
  * @file           : motor_functions.c
  * @brief          : functions for motor control
  ******************************************************************************
  */

 #include "motor_functions.h"
 #include "stm32f4xx_hal_tim.h"

void MOTOR_move_speed_forward(float speed, motor_instance_t motors) {
  float pwmFrequency = speed / (STEP_ANGLE * motors.wheelRadius);

  uint32_t autoReloadRegister = FCLK / (pwmFrequency * (PSC + 1)) - 1;

  MOTOR_stop_both(motors);

  motors.rightMotor.direction = FORWARD;
  motors.leftMotor.direction = FORWARD;

  HAL_GPIO_WritePin(motors.rightMotor.directionPinPort, motors.rightMotor.directionPin, 1);
  HAL_GPIO_WritePin(motors.rightMotor.directionPinPort, motors.rightMotor.directionPin, 0);

  __HAL_TIM_SET_AUTORELOAD(motors.timer, autoReloadRegister);

  motors.speed = speed;
}

void MOTOR_move_speed_backward(float speed, motor_instance_t motors) {
  float pwmFrequency = speed / (STEP_ANGLE * motors.wheelRadius);

  uint32_t autoReloadRegister = FCLK / (pwmFrequency * (PSC + 1)) - 1;

  MOTOR_stop_both(motors);

  motors.rightMotor.direction = BACKWARD;
  motors.leftMotor.direction = BACKWARD;

  HAL_GPIO_WritePin(motors.rightMotor.directionPinPort, motors.rightMotor.directionPin, 0);
  HAL_GPIO_WritePin(motors.rightMotor.directionPinPort, motors.rightMotor.directionPin, 1);

  __HAL_TIM_SET_AUTORELOAD(motors.timer, autoReloadRegister);

  motors.speed = speed;
}

void MOTOR_stop_both(motor_instance_t motors) {
  uint32_t autoReloadRegister = 0;
  __HAL_TIM_SET_AUTORELOAD(motors.timer, autoReloadRegister);

  motors.speed = 0;
  motors.rightMotor.direction = NO_DIRECTION;
  motors.leftMotor.direction = NO_DIRECTION;
}

void MOTOR_turn_right(float angle, float speed, motor_instance_t motors) {
  

}

void MOTOR_turn_left(float angle, float speed, motor_instance_t motors) {
    
}



