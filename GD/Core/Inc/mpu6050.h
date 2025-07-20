/*
 * mpu6050.h
 *
 *  Created on: May 1, 2025
 *      Author: DELL
 */

#ifndef INC_MPU6050_H_
#define INC_MPU6050_H_

#include "stm32f1xx_hal.h"  // Or your MCU-specific HAL header
#include <math.h>
#define MPU6050_ADDR  (0x68 << 1)  // I2C address for MPU6050 with R/W bit cleared

// MPU6050 Register Definitions
#define SMPLRT_DIV_REG    0x19
#define GYRO_CONFIG_REG   0x1B
#define ACCEL_CONFIG_REG  0x1C
#define ACCEL_XOUT_H_REG  0x3B
#define TEMP_OUT_H_REG    0x41  f
#define GYRO_XOUT_H_REG   0x43
#define PWR_MGMT_1_REG    0x6B
#define WHO_AM_I_REG      0x75

// Structure to Store Raw Acceleration Data
typedef struct {
    int16_t acc_x_raw;
    int16_t acc_y_raw;
    int16_t acc_z_raw;
    int16_t gyro_x_raw, gyro_y_raw, gyro_z_raw;
    float roll;  // Roll angle
    float pitch; // Pitch angle
    float yaw;   // Yaw angle
} Struct_MPU6050;

// Function Prototypes
void MPU6050_Init(I2C_HandleTypeDef *hi2c);
void MPU6050_ReadAcceleration(I2C_HandleTypeDef *hi2c, Struct_MPU6050* data);
void MPU6050_WriteRegister(I2C_HandleTypeDef *hi2c, uint8_t reg_addr, uint8_t *data, uint8_t len);
void MPU6050_ReadRegister(I2C_HandleTypeDef *hi2c, uint8_t reg_addr, uint8_t *data, uint8_t len);
void MPU6050_CalculateAngles(Struct_MPU6050 *mpu6050);
void MPU6050_ReadRegisternew(I2C_HandleTypeDef *hi2c, uint8_t reg_addr, uint8_t *data, uint8_t len);

#endif /* INC_MPU6050_H_ */

