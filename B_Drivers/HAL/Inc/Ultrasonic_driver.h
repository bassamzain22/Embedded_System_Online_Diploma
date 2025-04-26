/*
 * Ultrasonic_driver.h
 *
 *  Created on: Apr 21, 2025
 *      Author: Bassam Zain
 */

#ifndef INC_ULTRASONIC_DRIVER_H_
#define INC_ULTRASONIC_DRIVER_H_
// Includes
#include "stm32f103x6.h"
#include "stm32_F103C6_gpio_driver.h"
#include "STM32_TIMERS_DRIVER.h"
#include "stm32f103c6_ISR_DRIVER.h"


#define ULTRASONIC_CLK 8000000 // 8 MHz
#define DISTANCE_THRESHOLD 40  // cm
#define LED_DURATION 5000      // 5 seconds in milliseconds
#define MEASUREMENT_INTERVAL 200 // 200 ms between measurements
#define TIMEOUT_US 30000       // 30 ms timeout


#define SENSOR_FRONT 0
#define SENSOR_LEFT 1
#define SENSOR_RIGHT 2
#define SENSOR_COUNT 3


void Ultrasonic_Init(void);
uint32_t Get_Distance_Front(void);
uint32_t Get_Distance_Left(void);
uint32_t Get_Distance_Right(void);

#endif /* INC_ULTRASONIC_DRIVER_H_ */
