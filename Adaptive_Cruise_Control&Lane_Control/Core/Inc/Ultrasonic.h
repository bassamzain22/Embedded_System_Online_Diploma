/*
 * Ultrasonic.h
 *
 *  Created on: May 31, 2025
 *      Author: Bassam zain
 */

#ifndef INC_ULTRASONIC_H_
#define INC_ULTRASONIC_H_

#include "main.h"


// Sensor positions
#define FRONT_SENSOR 0
#define LEFT_SENSOR 1
#define RIGHT_SENSOR 2
#define SENSOR_TIMEOUT 10000
#define MAX_DISTANCE 500


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
// New functions
uint16_t get_frontdis();
uint16_t get_leftdis();
uint16_t get_rightdis();
#endif /* INC_ULTRASONIC_H_ */
