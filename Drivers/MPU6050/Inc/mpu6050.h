/*
 * mpu6050.h
 *
 *  Created on: Nov 13, 2019
 *      Author: Bulanov Konstantin
 */

#ifndef INC_GY521_H_
#define INC_GY521_H_

#include <stdint.h>
#include "stm32f4xx_hal.h"

// MPU6050 structure
typedef struct
{
    int16_t Accel_X_RAW;
    int16_t Accel_Y_RAW;
    int16_t Accel_Z_RAW;
    double Ax;
    double Ay;
    double Az;

    int16_t Gyro_X_RAW;
    int16_t Gyro_Y_RAW;
    int16_t Gyro_Z_RAW;
    double Gx;
    double Gy;
    double Gz;

    float Temperature;

    double KalmanAngleX;
    double KalmanAngleY;
} MPU6050_t;

// Kalman structure
typedef struct
{
    double Q_angle;
    double Q_bias;
    double R_measure;
    double angle;
    double bias;
    double P[2][2];
} Kalman_t;

/**
  * @brief Initializes I2C communication with MPU6050
  * @param I2Cx pointer to I2C handler used to communicate with MPU6050
  */
uint8_t MPU6050_Init(I2C_HandleTypeDef *I2Cx);

/**
  * @brief Read data from accelerometer
  * @param I2Cx pointer to I2C handler used to communicate with MPU6050
  * @param DataStruct pointer to gyro instance struct to store data from MPU6050
  */
void MPU6050_Read_Accel(I2C_HandleTypeDef *I2Cx, MPU6050_t *DataStruct);

/**
  * @brief Read data from gyroscope
  * @param I2Cx pointer to I2C handler used to communicate with MPU6050
  * @param DataStruct pointer to gyro instance struct to store data from MPU6050
  */
void MPU6050_Read_Gyro(I2C_HandleTypeDef *I2Cx, MPU6050_t *DataStruct);

/**
  * @brief Read data from temperature sensor
  * @param I2Cx pointer to I2C handler used to communicate with MPU6050
  * @param DataStruct pointer to gyro instance struct to store data from MPU6050
  */
void MPU6050_Read_Temp(I2C_HandleTypeDef *I2Cx, MPU6050_t *DataStruct);

/**
  * @brief Read all data from MPU6050
  * @param I2Cx pointer to I2C handler used to communicate with MPU6050
  * @param DataStruct pointer to gyro instance struct to store data from MPU6050
  */
void MPU6050_Read_All(I2C_HandleTypeDef *I2Cx, MPU6050_t *DataStruct);

double Kalman_getAngle(Kalman_t *Kalman, double newAngle, double newRate, double dt);

#endif /* INC_GY521_H_ */