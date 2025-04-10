/*
 * stm32_F103C6_pin_mapping.h
 *
 *      Author: AMiR
 */

#ifndef INC_STM32_F103C6_PIN_MAPPING_H_
#define INC_STM32_F103C6_PIN_MAPPING_H_

//-----------------------------
// Includes
//-----------------------------
#include "stm32f103x6.h"
#include "stm32_F103C6_EXTI_driver.h"

//===========================================================================
// Pin Mapping Configuration
//===========================================================================

//-----------------------------
// Motor Control Pin Mapping (H-Bridge)
//-----------------------------

// Front Left Motor (Motor 1)
#define MOTOR_FL_PORT_FWD           GPIOA
#define MOTOR_FL_PIN_FWD            GPIO_PIN_0  // PA0
#define MOTOR_FL_PORT_BWD           GPIOA
#define MOTOR_FL_PIN_BWD            GPIO_PIN_1  // PA1
#define MOTOR_FL_PWM_PORT           GPIOA
#define MOTOR_FL_PWM_PIN            GPIO_PIN_8  // PA8 (TIM1_CH1)

// Front Right Motor (Motor 2)
#define MOTOR_FR_PORT_FWD           GPIOA
#define MOTOR_FR_PIN_FWD            GPIO_PIN_2  // PA2
#define MOTOR_FR_PORT_BWD           GPIOA
#define MOTOR_FR_PIN_BWD            GPIO_PIN_3  // PA3
#define MOTOR_FR_PWM_PORT           GPIOA
#define MOTOR_FR_PWM_PIN            GPIO_PIN_9  // PA9 (TIM1_CH2)

// Rear Left Motor (Motor 3)
#define MOTOR_RL_PORT_FWD           GPIOB
#define MOTOR_RL_PIN_FWD            GPIO_PIN_0  // PB0
#define MOTOR_RL_PORT_BWD           GPIOB
#define MOTOR_RL_PIN_BWD            GPIO_PIN_1  // PB1
#define MOTOR_RL_PWM_PORT           GPIOA
#define MOTOR_RL_PWM_PIN            GPIO_PIN_10 // PA10 (TIM1_CH3)

// Rear Right Motor (Motor 4)
#define MOTOR_RR_PORT_FWD           GPIOB
#define MOTOR_RR_PIN_FWD            GPIO_PIN_10 // PB10
#define MOTOR_RR_PORT_BWD           GPIOB
#define MOTOR_RR_PIN_BWD            GPIO_PIN_11 // PB11
#define MOTOR_RR_PWM_PORT           GPIOA
#define MOTOR_RR_PWM_PIN            GPIO_PIN_11 // PA11 (TIM1_CH4)

//-----------------------------
// Ultrasonic Sensors (HC-SR04) Pin Mapping
//-----------------------------

// Front Ultrasonic
#define ULTRASONIC_FRONT_TRIG_PORT  GPIOB
#define ULTRASONIC_FRONT_TRIG_PIN   GPIO_PIN_12 // PB12
#define ULTRASONIC_FRONT_ECHO_PORT  GPIOB
#define ULTRASONIC_FRONT_ECHO_PIN   GPIO_PIN_13 // PB13 (EXTI13)
#define ULTRASONIC_FRONT_EXTI       EXTI13PB13  // Predefined EXTI mapping

// Rear Ultrasonic
#define ULTRASONIC_REAR_TRIG_PORT   GPIOB
#define ULTRASONIC_REAR_TRIG_PIN    GPIO_PIN_14 // PB14
#define ULTRASONIC_REAR_ECHO_PORT   GPIOB
#define ULTRASONIC_REAR_ECHO_PIN    GPIO_PIN_15 // PB15 (EXTI15)
#define ULTRASONIC_REAR_EXTI        EXTI15PB15  // Predefined EXTI mapping

// Left Ultrasonic
#define ULTRASONIC_LEFT_TRIG_PORT   GPIOB
#define ULTRASONIC_LEFT_TRIG_PIN    GPIO_PIN_5  // PB5
#define ULTRASONIC_LEFT_ECHO_PORT   GPIOC
#define ULTRASONIC_LEFT_ECHO_PIN    GPIO_PIN_14 // PC14 (EXTI14)
#define ULTRASONIC_LEFT_EXTI        EXTI14PC14  // Predefined EXTI mapping

// Right Ultrasonic
#define ULTRASONIC_RIGHT_TRIG_PORT  GPIOC
#define ULTRASONIC_RIGHT_TRIG_PIN   GPIO_PIN_15 // PC15
#define ULTRASONIC_RIGHT_ECHO_PORT  GPIOA
#define ULTRASONIC_RIGHT_ECHO_PIN   GPIO_PIN_12 // PA12 (EXTI12)
#define ULTRASONIC_RIGHT_EXTI       EXTI12PA12  

//-----------------------------
// Speed Sensors Pin Mapping
//-----------------------------

// Left Speed Sensor 
#define SPEED_SENSOR_LEFT_PORT      GPIOA
#define SPEED_SENSOR_LEFT_PIN       GPIO_PIN_4  
#define SPEED_SENSOR_LEFT_EXTI      EXTI4PA4    

// Right Speed Sensor
#define SPEED_SENSOR_RIGHT_PORT     GPIOB
#define SPEED_SENSOR_RIGHT_PIN      GPIO_PIN_3  // PB3 (EXTI3)
#define SPEED_SENSOR_RIGHT_EXTI     EXTI3PB3    
//-----------------------------
// LED Indicators
//-----------------------------
#define LED_STATUS_PORT             GPIOC
#define LED_STATUS_PIN              GPIO_PIN_13 // PC13 (Built-in LED)

//===========================================================================
// Timer Configuration for PWM
//===========================================================================

// TIM1 - Advanced Timer for Motor PWM
#define MOTOR_PWM_TIMER             TIM1
#define MOTOR_PWM_TIMER_CHANNEL1    1  // For Front Left Motor
#define MOTOR_PWM_TIMER_CHANNEL2    2  // For Front Right Motor
#define MOTOR_PWM_TIMER_CHANNEL3    3  // For Rear Left Motor
#define MOTOR_PWM_TIMER_CHANNEL4    4  // For Rear Right Motor

// TIM2 - For Ultrasonic Echo Measurement
#define ULTRASONIC_TIMER            TIM2

//===========================================================================
// Configuration Structures
//===========================================================================

// Motor Configuration Structure
typedef struct {
    GPIO_TypedDef* DirectionPort;
    uint16_t DirectionPin_Forward;
    uint16_t DirectionPin_Backward;
    GPIO_TypedDef* PWMPort;
    uint16_t PWMPin;
    uint8_t Direction;  // Using MOTOR_DIRECTION_* defines
    uint8_t Speed;      // 0-100 percentage
    uint8_t Enabled;    // 0 or 1
} Motor_Config_t;

// Add these missing direction defines
#define MOTOR_DIRECTION_STOP      0
#define MOTOR_DIRECTION_FORWARD   1
#define MOTOR_DIRECTION_BACKWARD  2

// Motor Configuration Structure
#define MOTOR_CONFIG_ARRAY { \
    { \
        .DirectionPort = MOTOR_FL_PORT_FWD, \
        .DirectionPin_Forward = MOTOR_FL_PIN_FWD, \
        .DirectionPin_Backward = MOTOR_FL_PIN_BWD, \
        .PWMPort = MOTOR_FL_PWM_PORT, \
        .PWMPin = MOTOR_FL_PWM_PIN, \
        .Direction = MOTOR_DIRECTION_STOP, \
        .Speed = 0, \
        .Enabled = 0 \
    }, \
    { \
        .DirectionPort = MOTOR_FR_PORT_FWD, \
        .DirectionPin_Forward = MOTOR_FR_PIN_FWD, \
        .DirectionPin_Backward = MOTOR_FR_PIN_BWD, \
        .PWMPort = MOTOR_FR_PWM_PORT, \
        .PWMPin = MOTOR_FR_PWM_PIN, \
        .Direction = MOTOR_DIRECTION_STOP, \
        .Speed = 0, \
        .Enabled = 0 \
    }, \
    { \
        .DirectionPort = MOTOR_RL_PORT_FWD, \
        .DirectionPin_Forward = MOTOR_RL_PIN_FWD, \
        .DirectionPin_Backward = MOTOR_RL_PIN_BWD, \
        .PWMPort = MOTOR_RL_PWM_PORT, \
        .PWMPin = MOTOR_RL_PWM_PIN, \
        .Direction = MOTOR_DIRECTION_STOP, \
        .Speed = 0, \
        .Enabled = 0 \
    }, \
    { \
        .DirectionPort = MOTOR_RR_PORT_FWD, \
        .DirectionPin_Forward = MOTOR_RR_PIN_FWD, \
        .DirectionPin_Backward = MOTOR_RR_PIN_BWD, \
        .PWMPort = MOTOR_RR_PWM_PORT, \
        .PWMPin = MOTOR_RR_PWM_PIN, \
        .Direction = MOTOR_DIRECTION_STOP, \
        .Speed = 0, \
        .Enabled = 0 \
    } \
}

// Ultrasonic Configuration Structure
typedef struct {
    GPIO_TypedDef* TrigPort;
    uint16_t TrigPin;
    GPIO_TypedDef* EchoPort;
    uint16_t EchoPin;
    EXTI_AFIO_MAPPING_t EXTI_Mapping;  // Added for EXTI integration
} ULTRASONIC_Config_t;

#define ULTRASONIC_CONFIG_ARRAY { \
    { \
        .TrigPort = ULTRASONIC_FRONT_TRIG_PORT, \
        .TrigPin = ULTRASONIC_FRONT_TRIG_PIN, \
        .EchoPort = ULTRASONIC_FRONT_ECHO_PORT, \
        .EchoPin = ULTRASONIC_FRONT_ECHO_PIN, \
        .EXTI_Mapping = ULTRASONIC_FRONT_EXTI \
    }, \
    { \
        .TrigPort = ULTRASONIC_REAR_TRIG_PORT, \
        .TrigPin = ULTRASONIC_REAR_TRIG_PIN, \
        .EchoPort = ULTRASONIC_REAR_ECHO_PORT, \
        .EchoPin = ULTRASONIC_REAR_ECHO_PIN, \
        .EXTI_Mapping = ULTRASONIC_REAR_EXTI \
    }, \
    { \
        .TrigPort = ULTRASONIC_LEFT_TRIG_PORT, \
        .TrigPin = ULTRASONIC_LEFT_TRIG_PIN, \
        .EchoPort = ULTRASONIC_LEFT_ECHO_PORT, \
        .EchoPin = ULTRASONIC_LEFT_ECHO_PIN, \
        .EXTI_Mapping = ULTRASONIC_LEFT_EXTI \
    }, \
    { \
        .TrigPort = ULTRASONIC_RIGHT_TRIG_PORT, \
        .TrigPin = ULTRASONIC_RIGHT_TRIG_PIN, \
        .EchoPort = ULTRASONIC_RIGHT_ECHO_PORT, \
        .EchoPin = ULTRASONIC_RIGHT_ECHO_PIN, \
        .EXTI_Mapping = ULTRASONIC_RIGHT_EXTI \
    } \
}

// Speed Sensor Configuration Structure
typedef struct {
    GPIO_TypedDef* Port;
    uint16_t Pin;
    EXTI_AFIO_MAPPING_t EXTI_Mapping;  // Added for EXTI integration
} SPEED_SENSOR_Config_t;

#define SPEED_SENSOR_CONFIG_ARRAY { \
    { \
        .Port = SPEED_SENSOR_LEFT_PORT, \
        .Pin = SPEED_SENSOR_LEFT_PIN, \
        .EXTI_Mapping = SPEED_SENSOR_LEFT_EXTI \
    }, \
    { \
        .Port = SPEED_SENSOR_RIGHT_PORT, \
        .Pin = SPEED_SENSOR_RIGHT_PIN, \
        .EXTI_Mapping = SPEED_SENSOR_RIGHT_EXTI \
    } \
}

//===========================================================================
// Constants for System Configuration
//===========================================================================

// PWM Configuration
#define PWM_FREQUENCY               20000   // 20 kHz
#define PWM_TIMER_PRESCALER         72      // For 1 MHz timer clock (72MHz/72)
#define PWM_PERIOD                  1000    // For 1 kHz PWM (1MHz/1000)

// Ultrasonic Configuration
#define ULTRASONIC_TIMEOUT_US       30000   // 30ms timeout
#define ULTRASONIC_TRIGGER_TIME_US  10      // 10us trigger pulse

// Control Update Rate
#define CONTROL_UPDATE_RATE_MS      50      // 50ms (20Hz) control loop update rate

// Safety Parameters
#define SAFETY_DISTANCE_MIN_MM      300     // Minimum safe distance in mm
#define EMERGENCY_BRAKE_DISTANCE_MM 150     // Emergency brake distance in mm


// Sensor ID Enumerations
typedef enum {
    ULTRASONIC_FRONT = 0,
    ULTRASONIC_REAR,
    ULTRASONIC_LEFT,
    ULTRASONIC_RIGHT,
    ULTRASONIC_COUNT
} Ultrasonic_ID_t;

typedef enum {
    SPEED_SENSOR_LEFT = 0,
    SPEED_SENSOR_RIGHT,
    SPEED_SENSOR_COUNT
} Speed_Sensor_ID_t;

typedef enum {
    MOTOR_FRONT_LEFT = 0,
    MOTOR_FRONT_RIGHT,
    MOTOR_REAR_LEFT,
    MOTOR_REAR_RIGHT,
    MOTOR_COUNT
} Motor_ID_t;

#endif /* INC_STM32_F103C6_PIN_MAPPING_H_ */ 