/**
  ******************************************************************************
  * @file           : ramp_traversing.h
  * @brief          : Header for ramp_traversing.c file.
  *                   This file contains the functions prototypes for the ramp traversing
  *                   algorithm
  ******************************************************************************
*/

#ifndef __RAMP_TRAVERSING_H
#define __RAMP_TRAVERSING_H

#include "main.h"
#include "motor_functions.h"
#include "switches.h"
#include "MB1040.h"

void ramp_traversal(motor_instance_t *motorInstance, swtiches_config_t *switchConfig, ADC_HandleTypeDef *adc);

#endif /* __RAMP_TRAVERSING_H */