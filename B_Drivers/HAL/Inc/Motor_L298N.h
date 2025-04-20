/*
 * Motor_L298N.h
 *
 *  Created on:
 *      Author: Bassam Zain
 */
#ifndef motor
#define motor

#include "stm32f103x6.h"
#include "STM32_TIMERS_DRIVER.h"
#include "stm32_F103C6_gpio_driver.h"
#define clk 36000000
// Initialize motor control pins
void Motors_Init(void);
void Set_Speed(uint32_t speed);
// Basic movement functions
void Move_Forward(void);
void Move_Backward(void);
void Move_Left(void);
void Move_Right(void);
void speed_increment(uint32_t *current_speed,uint32_t V2_speed , uint32_t distance);
void speed_decrement(uint32_t *current_speed,uint32_t V2_speed , uint32_t distance);
void Turn_left(void);
void Turn_right(void);
void Motors_Stop(void);
#endif
