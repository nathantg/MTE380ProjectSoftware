/**
  ******************************************************************************
  * @file           : motor_functions.c
  * @brief          : functions for motor control
  ******************************************************************************
  */

 #include "motor_functions.h"
 #include "stm32f4xx_hal_tim.h"

 void MOTOR_initialize_motor_config(motor_config_t *motorConfig, GPIO_TypeDef *directionPinPort, uint16_t directionPin) {
  motorConfig->directionPinPort = directionPinPort;
  motorConfig->directionPin = directionPin;
  motorConfig->direction = NO_DIRECTION;
}

void MOTOR_initialize_motor_instance(motor_instance_t *motorInstance, TIM_HandleTypeDef *timer, motor_config_t rightMotor, motor_config_t leftMotor) {
  motorInstance->timer = timer;
  motorInstance->rightMotor = rightMotor;
  motorInstance->leftMotor = leftMotor;
  motorInstance->autoReloadRegister = 0;
}

void MOTOR_move_speed_forward(uint32_t autoReloadRegister, motor_instance_t *motors) {
  HAL_GPIO_WritePin(motors->rightMotor.directionPinPort, motors->rightMotor.directionPin, RIGHT_FORWARD);
  HAL_GPIO_WritePin(motors->leftMotor.directionPinPort, motors->leftMotor.directionPin, LEFT_FORWARD);
  
  motors->rightMotor.direction = RIGHT_FORWARD;
  motors->leftMotor.direction = LEFT_FORWARD;

  __HAL_TIM_SET_AUTORELOAD(motors->timer, autoReloadRegister);

  motors->autoReloadRegister = autoReloadRegister;
}

void MOTOR_move_speed_backward(uint32_t autoReloadRegister, motor_instance_t *motors) {
  HAL_GPIO_WritePin(motors->rightMotor.directionPinPort, motors->rightMotor.directionPin, RIGHT_BACKWARD);
  HAL_GPIO_WritePin(motors->leftMotor.directionPinPort, motors->leftMotor.directionPin, LEFT_BACKWARD);
  
  motors->rightMotor.direction = RIGHT_BACKWARD;
  motors->leftMotor.direction = LEFT_BACKWARD;

  __HAL_TIM_SET_AUTORELOAD(motors->timer, autoReloadRegister);

  motors->autoReloadRegister = autoReloadRegister;
}

void MOTOR_stop_both(motor_instance_t *motors) {
  uint32_t autoReloadRegister = 0;
  __HAL_TIM_SET_AUTORELOAD(motors->timer, autoReloadRegister);

  motors->rightMotor.direction = NO_DIRECTION;
  motors->leftMotor.direction = NO_DIRECTION;

  motors->autoReloadRegister = 0;
}

void MOTOR_turn_right(uint32_t autoReloadRegister, motor_instance_t *motors) {
  HAL_GPIO_WritePin(motors->rightMotor.directionPinPort, motors->rightMotor.directionPin, RIGHT_BACKWARD);
  HAL_GPIO_WritePin(motors->leftMotor.directionPinPort, motors->leftMotor.directionPin, LEFT_FORWARD);

  motors->rightMotor.direction = RIGHT_BACKWARD;
  motors->leftMotor.direction = LEFT_FORWARD;

  __HAL_TIM_SET_AUTORELOAD(motors->timer, autoReloadRegister);

  motors->autoReloadRegister = autoReloadRegister;
}

void MOTOR_turn_left(uint32_t autoReloadRegister, motor_instance_t *motors) {
  HAL_GPIO_WritePin(motors->rightMotor.directionPinPort, motors->rightMotor.directionPin, RIGHT_FORWARD);
  HAL_GPIO_WritePin(motors->leftMotor.directionPinPort, motors->leftMotor.directionPin, LEFT_BACKWARD);

  motors->rightMotor.direction = RIGHT_FORWARD;
  motors->leftMotor.direction = LEFT_BACKWARD;

  __HAL_TIM_SET_AUTORELOAD(motors->timer, autoReloadRegister);

  motors->autoReloadRegister = autoReloadRegister;
}
