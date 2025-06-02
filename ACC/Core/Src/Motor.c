/*
 * Motor.c
 *
 *  Created on: Apr 30, 2025
 *      Author: Bassam Zain
 */


#include "motor.h"
#include "main.h"

#define max_speed       			100       // 100% of duty cycle
#define min_speed       			0         // 0% of duty cycle

#define action_distance      		40  //cm
#define min_distance         		10  //cm
#define braking_distance     		5   //cm


#define WHEEL_CIRCUMFERENCE_HALF 	4 // 4cm (half of wheel circumference)
#define OBSTACLE_NEAR_THRESHOLD 	10 // cm
#define OBSTACLE_FAR_THRESHOLD 		15  // cm
#define BASE_TURN_DURATION_MS 		800  // Time needed to turn 4cm at 100% speed
// Initialize motor control pins and PWM
void Motors_Init(void) {
	// GPIO pins are initialized by CubeMX

	// Start PWM signals
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);

	// Initially stop motors
	Stop_Motors();
}

// Set speed for all motors (duty cycle 0-100)
void Set_Speed(uint8_t duty_cycle) {
	// Ensure duty cycle is within bounds
	if (duty_cycle > 100) {
		duty_cycle = 100;
	}

	// Calculate compare value based on timer period
	uint16_t timer_period = htim1.Instance->ARR;
	uint16_t pulse = (timer_period * duty_cycle) / 100;

	// Set PWM duty cycle for both channels
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, pulse);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, pulse);
}

// Move all motors forward
void Move_Forward(void) {
	// Left motors forward (IN1 = HIGH, IN2 = LOW)
	HAL_GPIO_WritePin(IN1_PORT, IN1_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(IN2_PORT, IN2_PIN, GPIO_PIN_RESET);

	// Right motors forward (IN3 = HIGH, IN4 = LOW)
	HAL_GPIO_WritePin(IN3_PORT, IN3_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(IN4_PORT, IN4_PIN, GPIO_PIN_RESET);
}

// Move all motors backward
void Move_Backward(void) {
	// Left motors backward (IN1 = LOW, IN2 = HIGH)
	HAL_GPIO_WritePin(IN1_PORT, IN1_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(IN2_PORT, IN2_PIN, GPIO_PIN_SET);

	// Right motors backward (IN3 = LOW, IN4 = HIGH)
	HAL_GPIO_WritePin(IN3_PORT, IN3_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(IN4_PORT, IN4_PIN, GPIO_PIN_SET);
}

// Move Right
void Move_Right(void){
	// Left motors forward (IN1 = HIGH, IN2 = LOW)
	HAL_GPIO_WritePin(IN1_PORT, IN1_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(IN2_PORT, IN2_PIN, GPIO_PIN_RESET);

	// Right motors forward (IN3 = HIGH, IN4 = LOW)
	HAL_GPIO_WritePin(IN3_PORT, IN3_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(IN4_PORT, IN4_PIN, GPIO_PIN_RESET);
}
// Move Left
void Move_Left(void){

	// Left motors forward (IN1 = HIGH, IN2 = LOW)
	HAL_GPIO_WritePin(IN1_PORT, IN1_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(IN2_PORT, IN2_PIN, GPIO_PIN_RESET);

	// Right motors forward (IN3 = HIGH, IN4 = LOW)
	HAL_GPIO_WritePin(IN3_PORT, IN3_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(IN4_PORT, IN4_PIN, GPIO_PIN_RESET);

}
// Turn Right function
// Turn Right function
void Turn_Right(uint32_t Right_distance, uint32_t Left_distance, uint32_t current_speed) {
	// Check if obstacle is near on left and path is clear on right
	if (Left_distance <= OBSTACLE_NEAR_THRESHOLD && Right_distance >= OBSTACLE_FAR_THRESHOLD) {
		// Calculate turn duration inversely proportional to speed (with minimum speed check)
		uint32_t effective_speed = (current_speed < 10) ? 10 : current_speed; // Prevent division by zero
		uint32_t turn_duration = (BASE_TURN_DURATION_MS * 100) / effective_speed;

		// Execute turn left (to go right around obstacle)
		Move_Left();
		HAL_Delay(turn_duration);

		// Stop motors briefly
		Stop_Motors();
		HAL_Delay(100);

		// Continue forward
		Move_Forward();
	}
}

// Turn Left function
void Turn_Left(uint32_t Right_distance, uint32_t Left_distance, uint32_t current_speed) {
	// Check if obstacle is near on right and path is clear on left
	if (Right_distance <= OBSTACLE_NEAR_THRESHOLD && Left_distance >= OBSTACLE_FAR_THRESHOLD) {
		// Calculate turn duration inversely proportional to speed (with minimum speed check)
		uint32_t effective_speed = (current_speed < 10) ? 10 : current_speed; // Prevent division by zero
		uint32_t turn_duration = (BASE_TURN_DURATION_MS * 100) / effective_speed;

		// Execute turn right (to go left around obstacle)
		Move_Right();
		HAL_Delay(turn_duration);

		// Stop motors briefly
		Stop_Motors();
		HAL_Delay(100);

		// Continue forward
		Move_Forward();
	}
}
void Increase_speed(uint32_t distance , uint32_t *current_speed , uint32_t V2_speed){
	if (distance > action_distance+5) {

		if(V2_speed == max_speed){
			*current_speed = V2_speed;
		}

		else if(V2_speed < max_speed){

			if(distance - action_distance > 15){
				if(V2_speed<=70) *current_speed = V2_speed + 20;
				else if (V2_speed > 70) *current_speed = max_speed;

			}

			if(distance-action_distance <= 15 && distance-action_distance > 5){
				if(V2_speed<=70) *current_speed = V2_speed + 10;
				else if (V2_speed > 70) *current_speed = max_speed;


			}

		}
		// Update PWM with new speed
		Set_Speed(*current_speed);
	}
}
void Decrease_speed(uint32_t distance , uint32_t *current_speed , uint32_t V2_speed){
	if(distance <= action_distance && distance >= min_distance )
	{
		*current_speed = V2_speed-10;
		if(*current_speed < 0 )*current_speed = V2_speed;
		// Update PWM with new speed
		Set_Speed(*current_speed);
	}
	else if (distance < min_distance){
		*current_speed = 0;
	}
}
// Stop all motors
void Stop_Motors(void) {

	// Left motors stop (IN1 = LOW, IN2 = LOW)
	HAL_GPIO_WritePin(IN1_PORT, IN1_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(IN2_PORT, IN2_PIN, GPIO_PIN_RESET);

	// Right motors stop (IN3 = LOW, IN4 = LOW)
	HAL_GPIO_WritePin(IN3_PORT, IN3_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(IN4_PORT, IN4_PIN, GPIO_PIN_RESET);
}

// Simple delay function
void Delay_ms(uint32_t ms) {
	HAL_Delay(ms);
}
