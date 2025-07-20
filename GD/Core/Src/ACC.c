/*
 * acc.c - Adaptive Cruise Control System Implementation
 * Auther: AMIR
*/

#include "acc.h"
#include "main.h"

// Global ACC control structure
static ACC_Control_t acc_control;

/**
 * @brief Initialize the Adaptive Cruise Control system
 */
void ACC_Init(void) {
    // Initialize control structure
    acc_control.state = ACC_DISABLED;
    acc_control.target_speed = ACC_DEFAULT_SPEED;
    acc_control.current_speed = 0;
    acc_control.following_distance = ACC_SAFE_DISTANCE;
    acc_control.front_distance = 500;  // Initialize with large distance
    acc_control.last_update_time = HAL_GetTick();
    acc_control.emergency_brake_flag = 0;

    // Initialize motor system
    Motors_Init();

    // Stop motors initially
    Stop_Motors();
}

/**
 * @brief Enable ACC with specified target speed
 * @param target_speed: Desired cruise speed (20-90%)
 */
void ACC_Enable(uint32_t target_speed) {
    if (target_speed < ACC_MIN_SPEED) target_speed = ACC_MIN_SPEED;
    if (target_speed > ACC_MAX_SPEED) target_speed = ACC_MAX_SPEED;

    acc_control.target_speed = target_speed;
    acc_control.current_speed = ACC_MIN_SPEED;  // Start with minimum speed
    acc_control.state = ACC_ENABLED;
    acc_control.emergency_brake_flag = 0;

    // Start moving forward
    Move_Forward();
    Set_Speed(acc_control.current_speed);
}

/**
 * @brief Disable ACC system
 */
void ACC_Disable(void) {
    acc_control.state = ACC_DISABLED;
    acc_control.current_speed = 0;
    acc_control.emergency_brake_flag = 0;

    Stop_Motors();
}

/**
 * @brief Set new target speed
 * @param speed: New target speed (20-90%)
 */
void ACC_SetTargetSpeed(uint32_t speed) {
    if (speed < ACC_MIN_SPEED) speed = ACC_MIN_SPEED;
    if (speed > ACC_MAX_SPEED) speed = ACC_MAX_SPEED;

    acc_control.target_speed = speed;
}

/**
 * @brief Set following distance
 * @param distance: Desired following distance in cm
 */
void ACC_SetFollowingDistance(uint32_t distance) {
    if (distance < ACC_MIN_DISTANCE) distance = ACC_MIN_DISTANCE;
    acc_control.following_distance = distance;
}

/**
 * @brief Main ACC update function - call this regularly
 * @param front_distance: Current front distance measurement in cm
 */
void ACC_Update(uint32_t front_distance) {
    uint32_t current_time = HAL_GetTick();
    acc_control.front_distance = front_distance;

    // Check if it's time to update
    if (current_time - acc_control.last_update_time >= ACC_UPDATE_INTERVAL) {
        acc_control.last_update_time = current_time;

        // Handle different ACC states
        switch (acc_control.state) {
            case ACC_DISABLED:
                // Do nothing
                break;

            case ACC_ENABLED:
            case ACC_FOLLOWING:
                ACC_SpeedControl();
                break;

            case ACC_EMERGENCY_BRAKE:
                ACC_EmergencyBrake();
                break;
        }
    }
}

/**
 * @brief Main speed control logic
 */
void ACC_SpeedControl(void) {
    // Emergency braking check
    if (acc_control.front_distance <= ACC_EMERGENCY_DISTANCE) {
        acc_control.state = ACC_EMERGENCY_BRAKE;
        return;
    }

    // Determine target speed based on front distance
    uint32_t adaptive_speed = acc_control.target_speed;

    if (acc_control.front_distance < acc_control.following_distance) {
        // Vehicle ahead detected - enter following mode
        acc_control.state = ACC_FOLLOWING;

        // Calculate adaptive speed based on distance
        if (acc_control.front_distance < ACC_MIN_DISTANCE) {
            adaptive_speed = ACC_MIN_SPEED;
        } else {
            // Proportional speed reduction
            float speed_ratio = (float)(acc_control.front_distance - ACC_MIN_DISTANCE) /
                               (float)(acc_control.following_distance - ACC_MIN_DISTANCE);
            adaptive_speed = ACC_MIN_SPEED + (uint32_t)(speed_ratio * (acc_control.target_speed - ACC_MIN_SPEED));
        }
    } else {
        // Clear path - resume target speed
        acc_control.state = ACC_ENABLED;
        adaptive_speed = acc_control.target_speed;
    }

    // Smooth speed adjustment
    if (adaptive_speed > acc_control.current_speed) {
        ACC_SmoothAcceleration(adaptive_speed);
    } else if (adaptive_speed < acc_control.current_speed) {
        ACC_SmoothDeceleration(adaptive_speed);
    }
}

/**
 * @brief Emergency braking function
 */
void ACC_EmergencyBrake(void) {
    // Rapid deceleration
    if (acc_control.current_speed > 0) {
        if (acc_control.current_speed >= ACC_EMERGENCY_DECEL) {
            acc_control.current_speed -= ACC_EMERGENCY_DECEL;
        } else {
            acc_control.current_speed = 0;
        }

        Set_Speed(acc_control.current_speed);
        acc_control.emergency_brake_flag = 1;
    } else {
        // Complete stop
        Stop_Motors();
    }

    // Check if we can resume
    if (acc_control.front_distance > ACC_SAFE_DISTANCE) {
        acc_control.state = ACC_ENABLED;
        acc_control.emergency_brake_flag = 0;
        Move_Forward();
    }


}

/**
 * @brief Smooth acceleration to target speed
 * @param target_speed: Target speed to reach
 */
void ACC_SmoothAcceleration(uint32_t target_speed) {
    if (acc_control.current_speed < target_speed) {
        uint32_t speed_diff = target_speed - acc_control.current_speed;
        uint32_t increment = (speed_diff > ACC_SPEED_INCREMENT) ? ACC_SPEED_INCREMENT : speed_diff;

        acc_control.current_speed += increment;
        Set_Speed(acc_control.current_speed);
    }
}

/**
 * @brief Smooth deceleration to target speed
 * @param target_speed: Target speed to reach
 */
void ACC_SmoothDeceleration(uint32_t target_speed) {
    if (acc_control.current_speed > target_speed) {
        uint32_t speed_diff = acc_control.current_speed - target_speed;
        uint32_t decrement = (speed_diff > ACC_SPEED_DECREMENT) ? ACC_SPEED_DECREMENT : speed_diff;

        acc_control.current_speed -= decrement;
        Set_Speed(acc_control.current_speed);
    }
}

// Getter functions
ACC_State_t ACC_GetState(void) {
    return acc_control.state;
}

uint32_t ACC_GetCurrentSpeed(void) {
    return acc_control.current_speed;
}

uint32_t ACC_GetFrontDistance(void) {
    return acc_control.front_distance;
}
