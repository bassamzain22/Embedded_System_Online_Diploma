/*
 * Motor.h
 *
 *  Created on: Apr 30, 2025
 *      Author: Bassam Zain
 */

#ifndef INC_MOTOR_H_
#define INC_MOTOR_H_


#include "stm32f1xx_hal.h"

// Motor control pins
#define IN1_PIN  		GPIO_PIN_1
#define IN1_PORT 		GPIOA

#define IN2_PIN 		GPIO_PIN_2
#define IN2_PORT 		GPIOA

#define IN3_PIN 		GPIO_PIN_3
#define IN3_PORT 		GPIOA

#define IN4_PIN 		GPIO_PIN_4
#define IN4_PORT 		GPIOA

#define EN1_PIN 		GPIO_PIN_8
#define EN1_PORT		GPIOA

#define EN2_PIN 		GPIO_PIN_10
#define EN2_PORT 		GPIOA



// PWM timer handles (you'll need to configure these in CubeMX)
extern TIM_HandleTypeDef htim1; // Replace X with your timer number for EN1


// Function prototypes
void Motors_Init(void);
void Set_Speed(uint8_t duty_cycle);
void Move_Forward(void);
void Move_Backward(void);
void Move_Left(void);
void Move_Right(void);
void Turn_Right(uint32_t Right_distance , uint32_t Left_distance , uint32_t current_speed);
void Turn_left(uint32_t Right_distance , uint32_t Left_ditance , uint32_t current_speed);
void Increase_speed(uint32_t distance , uint32_t *current_speed , uint32_t V2_speed);
void Decrease_speed(uint32_t distance , uint32_t *current_speed , uint32_t V2_speed);

void Stop_Motors(void);
void Delay_ms(uint32_t ms);



#endif /* INC_MOTOR_H_ */
