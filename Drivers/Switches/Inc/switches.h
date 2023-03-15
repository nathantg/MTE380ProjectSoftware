/**
  ******************************************************************************
  * @file           : switches.h
  * @brief          : Header for motor_functions.c file.
  *                   This file contains the prototypes for the motor control 
  *                   functions
  ******************************************************************************
*/

#ifndef __SWITCHES_H
#define __SWITCHES_H

#include "main.h"

typedef struct {
    uint16_t limitSwtichPin;
    GPIO_TypeDef *limitSwitchPinPort;
    uint16_t tiltswtichPin;
    GPIO_TypeDef *tiltswtichPinPort;
} swtiches_config_t;

/**
 * @brief Initialize limit and tilt switch configuration
 * @param switchesConfig pointer to switches configuration instance
 * @param limitSwitchPinPort pointer to GPIO port for microcontroller pin assigned for limit swtich
 * @param limitSwtichPin microcontroller pin assigned for limit swtich
 * @param tiltSwitchPinPort pointer to GPIO port for microcontroller pin assigned for tilt switch
 * @param tiltSwtichPin microcontroller pin assigned for tilt switch
 * @retval None
 */
void SWITCHES_initialization(swtiches_config_t *switchesConfig, uint16_t limitSwitchPin, GPIO_TypeDef limitSwitchPinPort, uint16_t tiltSwitchPin, GPIO_TypeDef tiltSwitchPinPort);

/**
 * @brief Get current state of limit swtich
 * @param switchesConfig pointer to switches configuration instance
 * @retval 1 if limit switch is engaged 0 if not
 */
uint8_t SWITCHES_get_limit_switch(swtiches_config_t *switchesConfig);

/**
 * @brief Get current state of tilt swtich
 * @param switchesConfig pointer to switches configuration instance
 * @retval 1 if tilt switch is engaged 0 if not
 */
uint8_t SWITCHES_get_tilt_switch(swtiches_config_t *switchesConfig);

#endif /* __SWITCHES_H */
