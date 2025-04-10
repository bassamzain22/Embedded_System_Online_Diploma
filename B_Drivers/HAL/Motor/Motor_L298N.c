/*
 * Motor_L298N.c
 *
 *  Created on:
 *      Author: Bassam Zain
 */

#include "Motor_L298N.h"

static void Motor_Init(Motor_Config_t* motor) {
    MCAL_GPIO_Enable_ClocK(motor->GPIOx);

    GPIO_PinConfig_t pinConfig ;
    pinConfig.GPIO_Mode = GPIO_Mode_Out_push_pull,
    pinConfig.GPIO_Speed = GPIO_Speed_50MHz;

    //initalization IN1
    pinConfig.GPIO_PinNumber = motor->IN1_Pin;
    MCAL_GPIO_Init(motor->GPIOx, &pinConfig);

    //initalization IN2
    pinConfig.GPIO_PinNumber = motor->IN2_Pin;
    MCAL_GPIO_Init(motor->GPIOx, &pinConfig);

    uint32_t clock_freq = 72000000;
    uint16_t period = (clock_freq / motor->PWM_Frequency) - 1;

    TIM_Config_t timerConfig;
	timerConfig.TIM_Prescaler = 0;
	timerConfig.TIM_Period = period;


    TIM_Init(motor->TIMx, &timerConfig);

    TIM_TypeDef* TIMx;
    switch(motor->TIMx) {
        case TIM1_SELECT: TIMx = TIM1; break;
        case TIM2_SELECT: TIMx = TIM2; break;
        case TIM3_SELECT: TIMx = TIM3; break;
        case TIM4_SELECT: TIMx = TIM4; break;
    }

    switch(motor->PWM_Channel) {
        case 1:
            TIMx->CCMR1 |= (6 << 4);
            TIMx->CCER |= (1 << 0);
            break;
        case 2:
            TIMx->CCMR1 |= (6 << 12);
            TIMx->CCER |= (1 << 4);
            break;
        case 3:
            TIMx->CCMR2 |= (6 << 4);
            TIMx->CCER |= (1 << 8);
            break;
        case 4:
            TIMx->CCMR2 |= (6 << 12);
            TIMx->CCER |= (1 << 12);
            break;
    }

    TIM_Start(motor->TIMx);
}

static void Motor_SetSpeed(Motor_Config_t* motor, uint8_t speedPercent) {
    if(speedPercent > 100) speedPercent = 100;

    TIM_TypeDef* TIMx;
    switch(motor->TIMx) {
        case TIM1_SELECT: TIMx = TIM1; break;
        case TIM2_SELECT: TIMx = TIM2; break;
        case TIM3_SELECT: TIMx = TIM3; break;
        case TIM4_SELECT: TIMx = TIM4; break;
    }

    uint16_t pulseWidth = (TIMx->ARR * speedPercent) / 100;

    switch(motor->PWM_Channel) {
        case 1: TIMx->CCR1 = pulseWidth; break;
        case 2: TIMx->CCR2 = pulseWidth; break;
        case 3: TIMx->CCR3 = pulseWidth; break;
        case 4: TIMx->CCR4 = pulseWidth; break;
    }
}

void MotorSystem_Init(MotorSystem_Config_t* config) {
    Motor_Init(&config->left_forward);
    Motor_Init(&config->right_forward);
    Motor_Init(&config->left_backward);
    Motor_Init(&config->right_backward);
}
void Move_Forward(MotorSystem_Config_t* config, uint8_t speed) {
    // Enable all forward motors
    Motor_SetSpeed(&config->left_forward, speed);
    Motor_SetSpeed(&config->right_forward, speed);

    // enable backward motors
    Motor_SetSpeed(&config->left_backward, speed);
    Motor_SetSpeed(&config->right_backward, speed);

    // Set forward direction
    // forward motor
    MCAL_GPIO_WritePin(config->left_forward.GPIOx, config->left_forward.IN1_Pin, GPIO_PIN_SET);
    MCAL_GPIO_WritePin(config->left_forward.GPIOx, config->left_forward.IN2_Pin, GPIO_PIN_RESET);

    MCAL_GPIO_WritePin(config->right_forward.GPIOx, config->right_forward.IN1_Pin, GPIO_PIN_SET);
    MCAL_GPIO_WritePin(config->right_forward.GPIOx, config->right_forward.IN2_Pin, GPIO_PIN_RESET);

    //backward motor
    MCAL_GPIO_WritePin(config->left_backward.GPIOx, config->left_backward.IN1_Pin, GPIO_PIN_SET);
    MCAL_GPIO_WritePin(config->left_forward.GPIOx, config->left_forward.IN2_Pin, GPIO_PIN_RESET);

    MCAL_GPIO_WritePin(config->right_forward.GPIOx, config->right_forward.IN1_Pin, GPIO_PIN_SET);
    MCAL_GPIO_WritePin(config->right_forward.GPIOx, config->right_forward.IN2_Pin, GPIO_PIN_RESET);
}
void Move_Backward(MotorSystem_Config_t* config, uint8_t speed) {
    // enable  backward motors
    Motor_SetSpeed(&config->left_backward, speed);
    Motor_SetSpeed(&config->right_backward, speed);

    // enable forward motors
    Motor_SetSpeed(&config->left_forward, speed);
    Motor_SetSpeed(&config->right_forward, speed);

    // Set backward direction
    //forward motors
    MCAL_GPIO_WritePin(config->left_forward.GPIOx, config->left_backward.IN2_Pin, GPIO_PIN_SET);
    MCAL_GPIO_WritePin(config->left_forward.GPIOx, config->left_backward.IN1_Pin, GPIO_PIN_RESET);

    MCAL_GPIO_WritePin(config->right_forward.GPIOx, config->right_backward.IN2_Pin, GPIO_PIN_SET);
    MCAL_GPIO_WritePin(config->right_forward.GPIOx, config->right_backward.IN1_Pin, GPIO_PIN_RESET);

    MCAL_GPIO_WritePin(config->left_backward.GPIOx, config->left_backward.IN2_Pin, GPIO_PIN_SET);
    MCAL_GPIO_WritePin(config->left_backward.GPIOx, config->left_backward.IN1_Pin, GPIO_PIN_RESET);

    MCAL_GPIO_WritePin(config->right_backward.GPIOx, config->right_backward.IN2_Pin, GPIO_PIN_SET);
    MCAL_GPIO_WritePin(config->right_backward.GPIOx, config->right_backward.IN1_Pin, GPIO_PIN_RESET);
}
void Move_Right(MotorSystem_Config_t* config, uint8_t speed) {
    // Enable left motors
    Motor_SetSpeed(&config->left_forward, speed);
    Motor_SetSpeed(&config->left_backward, speed);

    // Disable right motors
    Motor_SetSpeed(&config->right_forward, 0);
    Motor_SetSpeed(&config->right_backward, 0);

    // Set directions
    MCAL_GPIO_WritePin(config->left_forward.GPIOx, config->left_forward.IN1_Pin, GPIO_PIN_SET);
    MCAL_GPIO_WritePin(config->left_forward.GPIOx, config->left_forward.IN2_Pin, GPIO_PIN_RESET);

    MCAL_GPIO_WritePin(config->left_backward.GPIOx, config->left_backward.IN1_Pin, GPIO_PIN_SET);
    MCAL_GPIO_WritePin(config->left_backward.GPIOx, config->left_backward.IN2_Pin, GPIO_PIN_RESET);
}

void Move_Left(MotorSystem_Config_t* config, uint8_t speed) {
    // Enable right motors
    Motor_SetSpeed(&config->right_forward, speed);
    Motor_SetSpeed(&config->right_backward, speed);

    // Disable left motors
    Motor_SetSpeed(&config->left_forward, 0);
    Motor_SetSpeed(&config->left_backward, 0);

    // Set directions
    MCAL_GPIO_WritePin(config->right_forward.GPIOx, config->right_forward.IN1_Pin, GPIO_PIN_SET);
    MCAL_GPIO_WritePin(config->right_forward.GPIOx, config->right_forward.IN2_Pin, GPIO_PIN_RESET);

    MCAL_GPIO_WritePin(config->right_backward.GPIOx, config->right_backward.IN1_Pin, GPIO_PIN_SET);
    MCAL_GPIO_WritePin(config->right_backward.GPIOx, config->right_backward.IN2_Pin, GPIO_PIN_RESET);
}

void Stop_All(MotorSystem_Config_t* config) {
    Motor_SetSpeed(&config->left_forward, 0);
    Motor_SetSpeed(&config->right_forward, 0);
    Motor_SetSpeed(&config->left_backward, 0);
    Motor_SetSpeed(&config->right_backward, 0);
}
void Delay_us(uint32_t microseconds) {
    // Configure TIM4 for 1MHz clock (1μs per tick)
    TIM_Config_t timerConfig = {
        .TIM_Prescaler = 72 - 1,  // 72MHz/72 = 1MHz (1μs per tick)
        .TIM_Period = microseconds // Direct μs count
    };

    // Initialize and start TIM4
    TIM_Init(TIM4_SELECT, &timerConfig);
    TIM_Start(TIM4_SELECT);

    // Wait for timer to complete
    while(!(TIM4->SR & 1));  // Wait for update interrupt flag

    // Cleanup
    TIM4->SR &= ~1;  // Clear the update flag
    TIM_Stop(TIM4_SELECT);
}
void Delay_ms(uint32_t milliseconds) {
    while(milliseconds--) {
        Delay_us(1000);  // 1000μs = 1ms
    }
}
