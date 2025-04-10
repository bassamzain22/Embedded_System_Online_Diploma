/*
 * stm32f103x8_timer.c
 *
 *  Created on: Mar 25, 2025
 *      Author: Bassam Zain
 */


#include "stm32f103x8_timer.h"

/*
 * Static callback function pointers for each timer.
 * These callbacks are invoked from the timer interrupt handlers.
 */
static void (*TIM1_Callback)(void) = 0;
static void (*TIM2_Callback)(void) = 0;
static void (*TIM3_Callback)(void) = 0;
static void (*TIM4_Callback)(void) = 0;

void TIM_Init(TIM_Select_t tim, TIM_Config_t* config)
{
    switch(tim)
    {
        case TIM1_SELECT:
            RCC_TIM1_CLK_EN();
            TIM1->PSC = config->TIM_Prescaler;
            TIM1->ARR = config->TIM_Period;
            /* Clear DIR bit (bit 4) for up-counting mode */
            TIM1->CR1 &= ~(1 << 4);
            /* Generate an update event to load the prescaler value immediately */
            TIM1->EGR |= 1;
            break;

        case TIM2_SELECT:
            RCC_TIM2_CLK_EN();
            TIM2->PSC = config->TIM_Prescaler;
            TIM2->ARR = config->TIM_Period;
            TIM2->CR1 &= ~(1 << 4);
            TIM2->EGR |= 1;
            break;

        case TIM3_SELECT:
            RCC_TIM3_CLK_EN();
            TIM3->PSC = config->TIM_Prescaler;
            TIM3->ARR = config->TIM_Period;
            TIM3->CR1 &= ~(1 << 4);
            TIM3->EGR |= 1;
            break;

        case TIM4_SELECT:
            RCC_TIM4_CLK_EN();
            TIM4->PSC = config->TIM_Prescaler;
            TIM4->ARR = config->TIM_Period;
            TIM4->CR1 &= ~(1 << 4);
            TIM4->EGR |= 1;
            break;
    }
}

void TIM_Start(TIM_Select_t tim)
{
    switch(tim)
    {
        case TIM1_SELECT:
            TIM1->CR1 |= 1;  // Set CEN bit to start timer
            break;
        case TIM2_SELECT:
            TIM2->CR1 |= 1;
            break;
        case TIM3_SELECT:
            TIM3->CR1 |= 1;
            break;
        case TIM4_SELECT:
            TIM4->CR1 |= 1;
            break;
    }
}

void TIM_Stop(TIM_Select_t tim)
{
    switch(tim)
    {
        case TIM1_SELECT:
            TIM1->CR1 &= ~1;  // Clear CEN bit to stop timer
            break;
        case TIM2_SELECT:
            TIM2->CR1 &= ~1;
            break;
        case TIM3_SELECT:
            TIM3->CR1 &= ~1;
            break;
        case TIM4_SELECT:
            TIM4->CR1 &= ~1;
            break;
    }
}

void TIM_SetCallback(TIM_Select_t tim, void (*callback)(void))
{
    switch(tim)
    {
        case TIM1_SELECT:
            TIM1_Callback = callback;
            /* Enable update interrupt (UIE) */
            TIM1->DIER |= 1;
            break;
        case TIM2_SELECT:
            TIM2_Callback = callback;
            TIM2->DIER |= 1;
            break;
        case TIM3_SELECT:
            TIM3_Callback = callback;
            TIM3->DIER |= 1;
            break;
        case TIM4_SELECT:
            TIM4_Callback = callback;
            TIM4->DIER |= 1;
            break;
    }
}

/*
 * Below are the interrupt handler functions.
 * Make sure these handlers are correctly linked in your startup code.
 */

void TIM1_UP_IRQHandler(void)
{
    /* Check update interrupt flag */
    if (TIM1->SR & 1)
    {
        TIM1->SR &= ~1;  // Clear the update flag
        if (TIM1_Callback)
        {
            TIM1_Callback();
        }
    }
}

void TIM2_IRQHandler(void)
{
    if (TIM2->SR & 1)
    {
        TIM2->SR &= ~1;
        if (TIM2_Callback)
        {
            TIM2_Callback();
        }
    }
}

void TIM3_IRQHandler(void)
{
    if (TIM3->SR & 1)
    {
        TIM3->SR &= ~1;
        if (TIM3_Callback)
        {
            TIM3_Callback();
        }
    }
}

void TIM4_IRQHandler(void)
{
    if (TIM4->SR & 1)
    {
        TIM4->SR &= ~1;
        if (TIM4_Callback)
        {
            TIM4_Callback();
        }
    }
}
