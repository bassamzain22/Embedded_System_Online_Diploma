/*
 * Ultrasonic.h
 *
 *  Created on: May 31, 2025
 *      Author: Bassam zain
 */

#ifndef INC_MYLIBRARY_H_
#define INC_MYLIBRARY_H_

#include "main.h"


extern TIM_HandleTypeDef htim2;

#define TriggerDuration 2

extern uint16_t distance, triggerTime, sensor;
extern GPIO_TypeDef *triggerPorts[3];
extern uint16_t triggerPins[3];
extern GPIO_TypeDef *echoPorts[3];
extern uint16_t echoPins[3];

void SysTickEnable();
void SysTickDisable();
uint16_t measureDistance(GPIO_TypeDef *triggerPort, uint16_t triggerPin, GPIO_TypeDef *echoPort, uint16_t echoPin);

#endif /* INC_MYLIBRARY_H_ */
