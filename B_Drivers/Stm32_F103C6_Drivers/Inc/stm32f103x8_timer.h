/*
 * stm32f103x8_timer.h
 *
 *  Created on: Mar 25, 2025
 *      Author: Bassam Z
 */

#ifndef INC_STM32F103X8_TIMER_H_
#define INC_STM32F103X8_TIMER_H_

#include "stm32f103x6.h"

/* Timer selection */
typedef enum {
    TIM1_SELECT,
    TIM2_SELECT,
    TIM3_SELECT,
    TIM4_SELECT,
} TIM_Select_t;

/* Timer configuration structure */
typedef struct {
    uint16_t TIM_Prescaler;   // Prescaler value
    uint16_t TIM_Period;      // Auto-reload value (Period)
    // You can add more fields (e.g., counter mode, clock division) if needed
} TIM_Config_t;

/*
 * @brief  Initialize the selected timer with the given configuration.
 * @param  tim: Timer selection (TIM1_SELECT, TIM2_SELECT, etc.)
 * @param  config: Pointer to a TIM_Config_t structure that contains the configuration.
 */
void TIM_Init(TIM_Select_t tim, TIM_Config_t* config);

/*
 * @brief  Start the selected timer.
 * @param  tim: Timer selection.
 */
void TIM_Start(TIM_Select_t tim);

/*
 * @brief  Stop the selected timer.
 * @param  tim: Timer selection.
 */
void TIM_Stop(TIM_Select_t tim);

/*
 * @brief  Set a callback function for the update interrupt of the selected timer.
 *         The callback is invoked every time an update interrupt occurs.
 * @param  tim: Timer selection.
 * @param  callback: Pointer to the callback function.
 */
void TIM_SetCallback(TIM_Select_t tim, void (*callback)(void));



#endif /* INC_STM32F103X8_TIMER_H_ */
