/*
 * Ultrasonic_driver.c
 *
 *  Created on: Apr 21, 2025
 *      Author: Bassam Zain
 */


#include "Ultrasonic_driver.h"


//Trigger Front Ultrasonic
#define FRONT_TRIG_PORT				 GPIOB
#define FRONT_TRIG_PIN 				 pin11

//Echo Front Ultrasonic
#define FRONT_ECHO_PORT 			 GPIOA
#define FRONT_ECHO_PIN               pin1


//Trigger Left Ultrasonic
#define LEFT_TRIG_PORT               GPIOB
#define LEFT_TRIG_PIN                pin12


//Echo Left Ultrasonic
#define LEFT_ECHO_PORT               GPIOA
#define LEFT_ECHO_PIN                pin2

//Trigger Right Ultrasonic
#define RIGHT_TRIG_PORT              GPIOB
#define RIGHT_TRIG_PIN               pin13
//Echo Right Ultrasonic
#define RIGHT_ECHO_PORT              GPIOA
#define RIGHT_ECHO_PIN               pin3


// start and end time for front ultrasonic
volatile uint32_t Front_echo_start_time = 0;
volatile uint32_t Front_echo_end_time = 0;
volatile uint8_t  Front_echo_received = 0;

// start and end time for left ultrasonic
volatile uint32_t Left_echo_start_time = 0;
volatile uint32_t Left_echo_end_time = 0;
volatile uint8_t  Left_echo_received = 0;

// start and end time for right ultrasonic
volatile uint32_t Right_echo_start_time = 0;
volatile uint32_t Right_echo_end_time = 0;
volatile uint8_t  Right_echo_received = 0;

static volatile uint8_t current_sensor = SENSOR_FRONT;

// Interrupt handlers
static void Front_EchoISR(void) {
    if (READ_PIN(FRONT_ECHO_PORT, FRONT_ECHO_PIN) == HIGH) {
        Front_echo_start_time = TIME_CALCULATION(ULTRASONIC_CLK, TIMER_START);
    } else {
        Front_echo_end_time = TIME_CALCULATION(ULTRASONIC_CLK, TIMER_STOP);
        Front_echo_received = 1;
    }
}

static void Left_EchoISR(void) {
	if (READ_PIN(FRONT_ECHO_PORT, FRONT_ECHO_PIN) == HIGH) {
	        Left_echo_start_time = TIME_CALCULATION(ULTRASONIC_CLK, TIMER_START);
	    } else {
	        Left_echo_end_time = TIME_CALCULATION(ULTRASONIC_CLK, TIMER_STOP);
	        Left_echo_received = 1;
	    }
}

static void Right_EchoISR(void) {
	if (READ_PIN(FRONT_ECHO_PORT, FRONT_ECHO_PIN) == HIGH) {
	        Right_echo_start_time = TIME_CALCULATION(ULTRASONIC_CLK, TIMER_START);
	    } else {
	        Right_echo_end_time = TIME_CALCULATION(ULTRASONIC_CLK, TIMER_STOP);
	        Right_echo_received = 1;
	    }
}

void Ultrasonic_Init(void) {
    // Enable clocks
    GPIOA_CLOCK_ENABLE;
    GPIOB_CLOCK_ENABLE;
    AFIO_CLOCK_ENABLE;

    // Configure Front trigger
    pinmode(FRONT_TRIG_PORT, FRONT_TRIG_PIN, GPIO_MODE_OUTPUT_push_pull_Speed2);
    pinwrite(FRONT_TRIG_PORT, FRONT_TRIG_PIN, LOW);

    // Configure Left trigger
    pinmode(LEFT_TRIG_PORT, LEFT_TRIG_PIN, GPIO_MODE_OUTPUT_push_pull_Speed2);
    pinwrite(LEFT_TRIG_PORT, LEFT_TRIG_PIN, LOW);

    // Configure Right trigger
    pinmode(RIGHT_TRIG_PORT, RIGHT_TRIG_PIN, GPIO_MODE_OUTPUT_push_pull_Speed2);
    pinwrite(RIGHT_TRIG_PORT, RIGHT_TRIG_PIN, LOW);

    // Configure Front Echo
    pinmode(FRONT_ECHO_PORT , FRONT_ECHO_PIN  , GPIO_MODE_INPUT_FLO);

    //Configure Left Echo
    pinmode(LEFT_ECHO_PORT  , LEFT_ECHO_PIN   , GPIO_MODE_INPUT_FLO);

    //Configure Right Echo
    pinmode(RIGHT_ECHO_PORT , RIGHT_ECHO_PIN  , GPIO_MODE_INPUT_FLO);

    // EXTI Front
    EXIT(FRONT_ECHO_PORT, FRONT_ECHO_PIN , EXTI_Trigger_RisingAndFalling, Front_EchoISR);

    //EXTI Left
    EXIT(LEFT_ECHO_PORT , LEFT_ECHO_PIN  , EXTI_Trigger_RisingAndFalling, Left_EchoISR);

    //EXTI Right
    EXIT(RIGHT_ECHO_PORT, RIGHT_ECHO_PIN , EXTI_Trigger_RisingAndFalling, Right_EchoISR);
}
uint32_t Get_Distance_Front(void) {

		pinwrite(FRONT_TRIG_PORT, FRONT_TRIG_PIN, HIGH);
	    delay(10, U_us, ULTRASONIC_CLK);  // 10µs trigger pulse
	    pinwrite(FRONT_TRIG_PORT, FRONT_TRIG_PIN,LOW);

	    // Wait for echo with timeout
	    uint32_t timeout = 30000;  // 30ms timeout
	    uint32_t start_time = TIME_CALCULATION(ULTRASONIC_CLK, TIMER_START);

	    while (!Front_echo_received) {
	        if ((TIME_CALCULATION(ULTRASONIC_CLK, TIMER_STOP) - start_time) > timeout) {
	            return -1;  // Error value
	        }
	    }

	    // Calculate distance
	    uint32_t pulse_duration = Front_echo_end_time - Front_echo_start_time;
	    uint32_t distance = (pulse_duration * 170) / 10000;  // cm

	    Front_echo_received = 0;
	    return distance;
}

// Get distance from left sensor
uint32_t Get_Distance_Left(void) {
			// Send trigger pulse
			pinwrite(LEFT_TRIG_PORT, LEFT_TRIG_PIN, HIGH);
		    delay(10, U_us, ULTRASONIC_CLK);  // 10µs trigger pulse
		    pinwrite(LEFT_TRIG_PORT, LEFT_TRIG_PIN ,LOW);

		    // Wait for echo with timeout
		    uint32_t timeout = 30000;  // 30ms timeout
		    uint32_t start_time = TIME_CALCULATION(ULTRASONIC_CLK, TIMER_START);

		    while (!Left_echo_received) {
		        if ((TIME_CALCULATION(ULTRASONIC_CLK, TIMER_STOP) - start_time) > timeout) {
		            return -1;  // Error value
		        }
		    }

		    // Calculate distance
		    uint32_t pulse_duration = Left_echo_end_time - Left_echo_start_time;
		    uint32_t distance = (pulse_duration * 170) / 10000;  // cm

		    Left_echo_received = 0;
		    return distance;
}

// Get distance from right sensor
uint32_t Get_Distance_Right(void) {
	         // Send trigger pulse
			pinwrite(RIGHT_TRIG_PORT, RIGHT_TRIG_PIN, HIGH);
		    delay(10, U_us, ULTRASONIC_CLK);  // 10µs trigger pulse
		    pinwrite(RIGHT_TRIG_PORT, RIGHT_TRIG_PIN,LOW);

		    // Wait for echo with timeout
		    uint32_t timeout = 30000;  // 30ms timeout
		    uint32_t start_time = TIME_CALCULATION(ULTRASONIC_CLK, TIMER_START);

		    while (!Right_echo_received) {
		        if ((TIME_CALCULATION(ULTRASONIC_CLK, TIMER_STOP) - start_time) > timeout) {
		            return -1;  // Error value
		        }
		    }

		    // Calculate distance
		    uint32_t pulse_duration = Right_echo_end_time - Right_echo_start_time;
		    uint32_t distance = (pulse_duration * 170) / 10000;  // cm

		    Right_echo_received = 0;
		    return distance;
}
