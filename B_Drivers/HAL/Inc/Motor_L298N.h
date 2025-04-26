/*s
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
void Motors_Stop(void);
void speed_increment(uint32_t *current_speed,uint32_t V2_speed , uint32_t distance);
void speed_decrement(uint32_t *current_speed,uint32_t V2_speed , uint32_t distance);
void speed_increment_distance(uint32_t *current_speed , uint32_t distance);
void speed_decrement_distance(uint32_t *current_speed , uint32_t distance);
void Turn_left(uint32_t current_speed , uint32_t Left_distance, uint32_t Right_distance);
void Turn_right(uint32_t current_speed, uint32_t Left_distance, uint32_t Right_distance);
void Move_Stop(uint32_t *current_speed , uint32_t distance);

#endif
