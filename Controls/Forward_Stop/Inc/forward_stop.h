/**
  ******************************************************************************
  * @file           : forward_stop.h
  * @brief          : Header for forward_stop.h.
  *                   This file contains the prototypes for the motor control 
  *                   functions
  ******************************************************************************
*/

#ifndef __FORWARD_STOP_H
#define __FORWARD_STOP_H

#include "main.h"
#include "motor_functions.h"
#include "switches.h"
#include "MB1040.h"

void forward_stop(motor_instance_t *motorInstance, swtiches_config_t *switchConfig, ADC_HandleTypeDef *adc);

#endif