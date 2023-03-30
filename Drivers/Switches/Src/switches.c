/**
  ******************************************************************************
  * @file           : switches.c
  * @brief          : functions for 
  *                   the limit and tilt switches
  ******************************************************************************
  */

 #include "switches.h"
 #include "stm32f4xx_hal_tim.h"

void SWITCHES_initialize_switch_config(swtiches_config_t *switchConfig, uint16_t switchPin, GPIO_TypeDef *switchPort) {
    switchConfig->swtichPin = switchPin;
    switchConfig->switchPinPort = switchPort;
    switchConfig->switchStatus = 0;
}

void SWITCHES_initiallize_switch_instance(switches_instance_t *switchesInstance, 
                                          swtiches_config_t *rightLimitSwtich, swtiches_config_t *leftLimitSwitch, 
                                          swtiches_config_t *upTiltSwitch, swtiches_config_t *downTiltSwtich) {
    switchesInstance->rightLimitSwitch = rightLimitSwtich;
    switchesInstance->leftLimitSwitch = leftLimitSwitch;
    switchesInstance->upTiltSwitch = upTiltSwitch;
    switchesInstance->downTiltSwitch = downTiltSwtich;
}

uint8_t SWITCHES_get_right_limit_switch(switches_instance_t *switchInstance) {
    uint8_t status = HAL_GPIO_ReadPin(switchInstance->rightLimitSwitch->switchPinPort, switchInstance->rightLimitSwitch->swtichPin);

    switchInstance->rightLimitSwitch->switchStatus = status;

    return status;
}

uint8_t SWITCHES_get_left_limit_switch(switches_instance_t *switchInstance) {
    uint8_t status = HAL_GPIO_ReadPin(switchInstance->leftLimitSwitch->switchPinPort, switchInstance->leftLimitSwitch->swtichPin);

    switchInstance->leftLimitSwitch->switchStatus = status;
    
    return status;
}

uint8_t SWITCHES_get_up_tilt_switch(switches_instance_t *switchInstance) {
    uint8_t status = HAL_GPIO_ReadPin(switchInstance->upTiltSwitch->switchPinPort, switchInstance->upTiltSwitch->swtichPin);

    switchInstance->upTiltSwitch->switchStatus = status;

    return status;
}

uint8_t SWITCHES_get_down_tilt_switch(switches_instance_t *switchInstance) {
    uint8_t status = HAL_GPIO_ReadPin(switchInstance->downTiltSwitch->switchPinPort, switchInstance->downTiltSwitch->swtichPin);

    switchInstance->downTiltSwitch->switchStatus = status;
    
    return status;
}