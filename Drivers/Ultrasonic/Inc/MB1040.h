/**
  ******************************************************************************
  * @file           : ultrasonic.h
  * @brief          : Header for ultrasonic.c file.
  *                   This file contains the driver for the ultrasonic sensor
  ******************************************************************************
  */

#ifndef __ULTRASONIC_H
#define __ULTRASONIC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

#define RES 4096
#define SENSITIVITY 0.0098f // 9.8mV/in

/**
  * @brief Get distance reading from MB1040 
  * @param adc handle for adc used for MB1040 
  * @param distance variable used to store distance 
  */
void MB1040_get_distance(ADC_HandleTypeDef *adc, float *distance);


#endif /* __ULTRASONIC_H */