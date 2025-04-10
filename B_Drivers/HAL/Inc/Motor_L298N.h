/*
 * Motor_L298N.h
 *
 *  Created on:
 *      Author: Bassam Zain
 */

#ifndef INC_MOTOR_L298N_H_
#define INC_MOTOR_L298N_H_
#ifndef MOTOR_H
#define MOTOR_H

#include "stm32f103x6.h"
#include "stm32_F103C6_gpio_driver.h"
#include "stm32f103x8_timer.h"

typedef struct {
    GPIO_TypedDef* GPIOx;
    uint16_t IN1_Pin;
    uint16_t IN2_Pin;
    TIM_Select_t TIMx;
    uint32_t PWM_Frequency;
    uint16_t PWM_Channel;
} Motor_Config_t;

typedef struct {
    Motor_Config_t left_forward;
    Motor_Config_t right_forward;
    Motor_Config_t left_backward;
    Motor_Config_t right_backward;
} MotorSystem_Config_t;

// Initialization
void MotorSystem_Init(MotorSystem_Config_t* config);

// Direction Control
void Move_Left(MotorSystem_Config_t* config, uint8_t speed);
void Move_Right(MotorSystem_Config_t* config, uint8_t speed);
void Move_Forward(MotorSystem_Config_t* config, uint8_t speed);
void Move_Backward(MotorSystem_Config_t* config, uint8_t speed);
void Stop_All(MotorSystem_Config_t* config);
void Delay_us(uint32_t milliseconds);
void Delay_ms(uint32_t milliseconds);
#endif
#endif /* INC_MOTOR_L298N_H_ */
