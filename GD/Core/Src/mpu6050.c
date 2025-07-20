/*
 * mpu6050.c
 *
 *  Created on: May 1, 2025
 *      Author: DELL
 */

#include "mpu6050.h"
#include "stm32f1xx_hal.h"

// Write to MPU6050 register
void MPU6050_WriteRegister(I2C_HandleTypeDef *hi2c, uint8_t reg_addr, uint8_t *data, uint8_t len)
{
    HAL_I2C_Mem_Write(hi2c, MPU6050_ADDR, reg_addr, I2C_MEMADD_SIZE_8BIT, data, len, HAL_MAX_DELAY);
}

// Read from MPU6050 register
void MPU6050_ReadRegister(I2C_HandleTypeDef *hi2c, uint8_t reg_addr, uint8_t *data, uint8_t len)
{
    HAL_I2C_Mem_Read(hi2c, MPU6050_ADDR, reg_addr, I2C_MEMADD_SIZE_8BIT, data, len, HAL_MAX_DELAY);
}
// Initialize MPU6050
void MPU6050_Init(I2C_HandleTypeDef *hi2c)
{
    uint8_t data;

    // Wake up MPU6050
    data = 0x00;
    MPU6050_WriteRegister(hi2c, PWR_MGMT_1_REG, &data, 1);

    // Set sample rate to 1kHz
    data = 0x07;
    MPU6050_WriteRegister(hi2c, SMPLRT_DIV_REG, &data, 1);

    // Configure accelerometer (+/- 2g)
    data = 0x00;
    MPU6050_WriteRegister(hi2c, ACCEL_CONFIG_REG, &data, 1);

    // Configure gyroscope (+/- 250 deg/s)
    data = 0x00;
    MPU6050_WriteRegister(hi2c, GYRO_CONFIG_REG, &data, 1);
}

// Read acceleration data
void MPU6050_ReadAcceleration(I2C_HandleTypeDef *hi2c, Struct_MPU6050 *mpu6050)
{
    uint8_t buffer[6];
    uint8_t buffer2[6];

    MPU6050_ReadRegister(hi2c, ACCEL_XOUT_H_REG, buffer, 6);

    mpu6050->acc_x_raw = (int16_t)(buffer[0] << 8 | buffer[1]);
    mpu6050->acc_y_raw = (int16_t)(buffer[2] << 8 | buffer[3]);
    mpu6050->acc_z_raw = (int16_t)(buffer[4] << 8 | buffer[5]);
    MPU6050_ReadRegister(hi2c, GYRO_XOUT_H_REG, buffer2, 6);
    mpu6050->gyro_x_raw = (int16_t)(buffer2[0] << 8 | buffer2[1]);
    mpu6050->gyro_y_raw = (int16_t)(buffer2[2] << 8 | buffer2[3]);
    mpu6050->gyro_z_raw = (int16_t)(buffer2[4] << 8 | buffer2[6]);


}
void MPU6050_CalculateAngles(Struct_MPU6050 *mpu6050) {
    float ax = mpu6050->acc_x_raw;
    float ay = mpu6050->acc_y_raw;
    float az = mpu6050->acc_z_raw;

    // Calculate Roll
    mpu6050->roll = atan2(ay, sqrt(ax * ax + az * az)) * 180.0 / M_PI;

    // Calculate Pitch
    mpu6050->pitch = atan2(-ax, sqrt(ay * ay + az * az)) * 180.0 / M_PI;

    // Calculate Yaw (simplified)
    mpu6050->yaw = atan2(ax, az) * 180.0 / M_PI;
}
