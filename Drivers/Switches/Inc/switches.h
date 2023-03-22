/**
  ******************************************************************************
  * @file           : switches.h
  * @brief          : Header for switches.c file.
  *                   This file contains the prototypes for the functions for 
  *                   the limit and tilt switches
  ******************************************************************************
*/

#ifndef __SWITCHES_H
#define __SWITCHES_H

#include "main.h"

typedef struct {
  uint16_t swtichPin;
  GPIO_TypeDef *switchPinPort;
} swtiches_config_t;

typedef struct {
  swtiches_config_t *rightLimitSwitch;
  swtiches_config_t *leftLimitSwitch;
  swtiches_config_t *upTiltSwitch;
  swtiches_config_t *downTiltSwitch;
} switches_instance_t;

/**
 * @brief Initialize a single switch configuration
 * @param switchConfig pointer to switch configuration to initialize
 * @param switchPinPort pointer to GPIO port for microcontroller pin assigned for swtich
 * @retval None
 */
void SWITCHES_initialize_switch_config(swtiches_config_t *switchConfig, uint16_t switchPin, GPIO_TypeDef *switchPort);

/**
 * @brief Initialize instance of limit and tilt switches
 * @param switchesInstance pointer to swtiches instance to initialize
 * @param rightLimitSwtich pointer to switches configuration instance
 * @param leftLimitSwitch pointer to GPIO port for microcontroller pin assigned for limit swtich
 * @param upTiltSwitch microcontroller pin assigned for limit swtich
 * @param downTiltSwtich pointer to GPIO port for microcontroller pin assigned for tilt switch
 * @retval None
 */
void SWITCHES_initiallize_switch_instance(switches_instance_t *switchesInstance, swtiches_config_t *rightLimitSwtich, swtiches_config_t *leftLimitSwitch, swtiches_config_t *upTiltSwitch, swtiches_config_t *downTiltSwtich);

/**
 * @brief Get current state of right limit swtich
 * @param switchesInstance pointer to switches instance
 * @retval 1 if limit switch is engaged 0 if not
 */
uint8_t SWITCHES_get_right_limit_switch(switches_instance_t *switchesInstance);

/**
 * @brief Get current state of left limit swtich
 * @param switchesInstance pointer to switches instance
 * @retval 1 if limit switch is engaged 0 if not
 */
uint8_t SWITCHES_get_left_limit_switch(switches_instance_t *switchesInstance);

/**
 * @brief Get current state of up tilt swtich
 * @param switchesInstance pointer to switches instance
 * @retval 1 if tilt switch is engaged 0 if not
 */
uint8_t SWITCHES_get_up_tilt_switch(switches_instance_t *switchesInstance);

/**
 * @brief Get current state of down tilt swtich
 * @param switchesInstance pointer to switches instance
 * @retval 1 if tilt switch is engaged 0 if not
 */
uint8_t SWITCHES_get_down_tilt_switch(switches_instance_t *switchesInstance);

#endif /* __SWITCHES_H */
