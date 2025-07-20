/*
 * acc.h - Adaptive Cruise Control System
 * Auther: AMIR
*/

#ifndef INC_ACC_H_
#define INC_ACC_H_

#include "stm32f1xx_hal.h"
#include "motor.h"

// ACC System States
typedef enum {
    ACC_DISABLED = 0,
    ACC_ENABLED,
    ACC_FOLLOWING,
    ACC_EMERGENCY_BRAKE
} ACC_State_t;

// ACC Control Structure
typedef struct {
    ACC_State_t state;
    uint32_t target_speed;          // Desired cruise speed (0-100%)
    uint32_t current_speed;         // Current vehicle speed (0-100%)
    uint32_t following_distance;    // Desired following distance (cm)
    uint32_t front_distance;        // Distance to front obstacle (cm)
    uint32_t last_update_time;      // Last sensor update timestamp
    uint8_t emergency_brake_flag;   // Emergency braking active
} ACC_Control_t;

// ACC Configuration Constants
#define ACC_DEFAULT_SPEED           60      // Default cruise speed (60%)
#define ACC_MIN_SPEED              20      // Minimum cruise speed (20%)
#define ACC_MAX_SPEED              90      // Maximum cruise speed (90%)

#define ACC_SAFE_DISTANCE          50      // Safe following distance (cm)
#define ACC_MIN_DISTANCE           15      // Minimum safe distance (cm)
#define ACC_EMERGENCY_DISTANCE     8       // Emergency brake distance (cm)

#define ACC_SPEED_INCREMENT        10       // Speed adjustment step (5%)
#define ACC_SPEED_DECREMENT        10       // Speed reduction step (8%)
#define ACC_EMERGENCY_DECEL        15      // Emergency deceleration step (15%)

#define ACC_UPDATE_INTERVAL        1    // Sensor update interval (ms)

// Function Prototypes
void ACC_Init(void);
void ACC_Enable(uint32_t target_speed);
void ACC_Disable(void);
void ACC_SetTargetSpeed(uint32_t speed);
void ACC_SetFollowingDistance(uint32_t distance);
void ACC_Update(uint32_t front_distance);
ACC_State_t ACC_GetState(void);
uint32_t ACC_GetCurrentSpeed(void);
uint32_t ACC_GetFrontDistance(void);
void ACC_EmergencyBrake(void);
void ACC_SpeedControl(void);

// Helper Functions
void ACC_SmoothAcceleration(uint32_t target_speed);
void ACC_SmoothDeceleration(uint32_t target_speed);

#endif /* INC_ACC_H_ */
