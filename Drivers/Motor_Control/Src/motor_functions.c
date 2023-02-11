/**
  ******************************************************************************
  * @file           : motor_functions.c
  * @brief          : functions for motor control
  ******************************************************************************
  */

 #include "motor_functions.h"
 #include "stm32f4xx_hal_tim.h"

// Assuming 1 is forward and 0 is backward for the DIR pins

void MOTOR_move_speed_forward(float speed, motor_instance_t motors) {
  float pwmFrequency = speed / (STEP_ANGLE * motors.wheelRadius);

  uint32_t autoReloadRegister = FCLK / (pwmFrequency * (PSC + 1)) - 1;

  HAL_GPIO_WritePin(motors.rightMotor.directionPinPort, motors.rightMotor.directionPin, 1);
  HAL_GPIO_WritePin(motors.rightMotor.directionPinPort, motors.rightMotor.directionPin, 0);
  
  motors.rightMotor.direction = FORWARD;
  motors.leftMotor.direction = FORWARD;

  __HAL_TIM_SET_AUTORELOAD(motors.timer, autoReloadRegister);

  motors.speed = speed;
}

void MOTOR_move_speed_backward(float speed, motor_instance_t motors) {
  float pwmFrequency = speed / (STEP_ANGLE * motors.wheelRadius);

  uint32_t autoReloadRegister = FCLK / (pwmFrequency * (PSC + 1)) - 1;

  HAL_GPIO_WritePin(motors.rightMotor.directionPinPort, motors.rightMotor.directionPin, 0);
  HAL_GPIO_WritePin(motors.rightMotor.directionPinPort, motors.rightMotor.directionPin, 1);

  motors.rightMotor.direction = BACKWARD;
  motors.leftMotor.direction = BACKWARD;

  __HAL_TIM_SET_AUTORELOAD(motors.timer, autoReloadRegister);

  motors.speed = speed;
}

void MOTOR_stop_both(motor_instance_t motors) {
  uint32_t autoReloadRegister = 0;
  __HAL_TIM_SET_AUTORELOAD(motors.timer, autoReloadRegister);

  motors.rightMotor.direction = NO_DIRECTION;
  motors.leftMotor.direction = NO_DIRECTION;

  motors.speed = 0;
}

void MOTOR_turn_right(float angle, float speed, motor_instance_t motors) {
  float pwmFrequency = speed / (STEP_ANGLE * motors.wheelRadius);

  uint32_t autoReloadRegister = FCLK / (pwmFrequency * (PSC + 1)) - 1;

  HAL_GPIO_WritePin(motors.rightMotor.directionPinPort, motors.rightMotor.directionPin, 0);
  HAL_GPIO_WritePin(motors.rightMotor.directionPinPort, motors.rightMotor.directionPin, 0);

  motors.rightMotor.direction = BACKWARD;
  motors.leftMotor.direction = FORWARD;

  __HAL_TIM_SET_AUTORELOAD(motors.timer, autoReloadRegister);

  motors.speed = speed;

}

void MOTOR_turn_left(float angle, float speed, motor_instance_t motors) {
  float pwmFrequency = speed / (STEP_ANGLE * motors.wheelRadius);

  uint32_t autoReloadRegister = FCLK / (pwmFrequency * (PSC + 1)) - 1;

  HAL_GPIO_WritePin(motors.rightMotor.directionPinPort, motors.rightMotor.directionPin, 1);
  HAL_GPIO_WritePin(motors.rightMotor.directionPinPort, motors.rightMotor.directionPin, 1);

  motors.rightMotor.direction = FORWARD;
  motors.leftMotor.direction = BACKWARD;

  __HAL_TIM_SET_AUTORELOAD(motors.timer, autoReloadRegister);

  motors.speed = speed;
}



