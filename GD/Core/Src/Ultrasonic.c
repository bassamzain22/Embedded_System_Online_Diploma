/*
 * Ultrasonic.c
 *
 *  Created on: May 31, 2025
 *      Author: Bassam Zain
 */



#include "Ultrasonic.h"


volatile uint8_t sensor_busy = 0;


uint16_t distance = 0, triggerTime = 0, sensor = 0;
GPIO_TypeDef *triggerPorts[3] = {Trigger0_GPIO_Port, Trigger1_GPIO_Port, Trigger2_GPIO_Port};
uint16_t triggerPins[3] = {Trigger0_Pin, Trigger1_Pin, Trigger2_Pin};
GPIO_TypeDef *echoPorts[3] = {Echo0_GPIO_Port, Echo1_GPIO_Port, Echo2_GPIO_Port};
uint16_t echoPins[3] = {Echo0_Pin, Echo1_Pin, Echo2_Pin};


void SysTickEnable()
{
	__disable_irq();
	SysTick->CTRL |= (SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk);
	__enable_irq();
}

void SysTickDisable()
{
	__disable_irq();
	SysTick->CTRL &= ~(SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk);
	__enable_irq();
}

uint16_t measureDistance(GPIO_TypeDef *triggerPort, uint16_t triggerPin, GPIO_TypeDef *echoPort, uint16_t echoPin)
{
	if(!HAL_GPIO_ReadPin(echoPort, echoPin))//skip sensor if ECHO pin is still busy
	{
		SysTickDisable();
		HAL_TIM_Base_Start_IT(&htim2);
		HAL_GPIO_WritePin(triggerPort, triggerPin, GPIO_PIN_SET);
		triggerTime = 0;//reset the variable
		asm ("nop");//to avoid program freezing
		while(triggerTime < TriggerDuration);
		HAL_GPIO_WritePin(triggerPort, triggerPin, GPIO_PIN_RESET);
		while(!HAL_GPIO_ReadPin(echoPort, echoPin));
		distance = 0;//reset the variable
		while(HAL_GPIO_ReadPin(echoPort, echoPin));
		HAL_TIM_Base_Stop_IT(&htim2);
		SysTickEnable();
	}else//give max distance if ECHO pin is still busy
	{
		distance = 500;
	}
	return distance;
}
uint16_t get_frontdis()
{
    return measureDistance(triggerPorts[FRONT_SENSOR], triggerPins[FRONT_SENSOR],
                         echoPorts[FRONT_SENSOR], echoPins[FRONT_SENSOR]);
}

uint16_t get_leftdis()
{
    return measureDistance(triggerPorts[LEFT_SENSOR], triggerPins[LEFT_SENSOR],
                         echoPorts[LEFT_SENSOR], echoPins[LEFT_SENSOR]);
}

uint16_t get_rightdis()
{
    return measureDistance(triggerPorts[RIGHT_SENSOR], triggerPins[RIGHT_SENSOR],
                         echoPorts[RIGHT_SENSOR], echoPins[RIGHT_SENSOR]);
}
