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

typedef struct {
  uint16_t directionPin;
  GPIO_TypeDef *directionPinPort;
  uint16_t trigPin;
  GPIO_TypeDef *trigPinPort;
  uint16_t echoPin;
  GPIO_TypeDef *echoPinPort;

} ultrasonic_conig_t;

void ULTRASONIC_init_config(ultrasonic_conig_t *ultrasonic, 
                             uint16_t trigPin, GPIO_TypeDef *trigPinPort,
                             uint16_t echoPin, GPIO_TypeDef *echoPinPort);

void ULTRASONIC_get_distance(float *distance, ultrasonic_conig_t *ultrasonic);


#endif /* __ULTRASONIC_H */
