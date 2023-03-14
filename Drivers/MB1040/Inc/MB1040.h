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

void MB1040_get_distance(ADC_HandleTypeDef *adc, float *distance);


#endif /* __ULTRASONIC_H */
