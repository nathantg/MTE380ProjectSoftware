/**
  ******************************************************************************
  * @file           : switches.c
  * @brief          : functions for motor control
  ******************************************************************************
  */

 #include "switches.h"
 #include "stm32f4xx_hal_tim.h"

 void SWITCHES_initialization(swtiches_config_t *switchesConfig, 
                              uint16_t limitSwitchPin, GPIO_TypeDef *limitSwitchPinPort, 
                              uint16_t tiltSwitchPin, GPIO_TypeDef *tiltSwitchPinPort) {
    switchesConfig->limitSwtichPin = limitSwitchPin;
    switchesConfig->limitSwitchPinPort = limitSwitchPinPort;
    switchesConfig->tiltswtichPin = tiltSwitchPin;
    switchesConfig->tiltswtichPinPort = tiltSwitchPinPort;
}

uint8_t SWITCHES_get_limit_switch(swtiches_config_t *switchesConfig) {
    return HAL_GPIO_ReadPin(switchesConfig->limitSwitchPinPort, switchesConfig->limitSwtichPin);
}

uint8_t SWITCHES_get_tilt_switch(swtiches_config_t *switchesConfig) {
    return HAL_GPIO_ReadPin(switchesConfig->tiltswtichPinPort, switchesConfig->tiltswtichPin);
}