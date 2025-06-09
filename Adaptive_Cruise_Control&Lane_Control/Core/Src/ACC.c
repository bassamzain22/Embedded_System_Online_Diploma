/*
 * acc.c - Adaptive Cruise Control System Implementation
 * Auther: AMIR
*/

#include "acc.h"
#include "main.h"

// Global ACC control structure
static ACC_Control_t acc_control;
static uint32_t lane_change_start_time = 0;

/**
 * @brief Initialize the Adaptive Cruise Control system
 */
void ACC_Init(void) {
    // Initialize control structure
    acc_control.state = ACC_DISABLED;
    acc_control.target_speed = ACC_DEFAULT_SPEED;
    acc_control.current_speed = 0;
    acc_control.following_distance = ACC_SAFE_DISTANCE;
    acc_control.front_distance = 500;
    acc_control.left_distance = 500;
    acc_control.right_distance = 500;
    acc_control.last_update_time = HAL_GetTick();
    acc_control.emergency_brake_flag = 0;
    acc_control.lane_change_request = 0;
    acc_control.obstacle_detected = 0;

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
    acc_control.lane_change_request = 0;

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
 * @brief Request lane change
 * @param direction: 1 for left, 2 for right
 */
void ACC_RequestLaneChange(uint8_t direction) {
    if (acc_control.state == ACC_ENABLED || acc_control.state == ACC_FOLLOWING) {
        if (direction == 1 || direction == 2) {
            acc_control.lane_change_request = direction;
        }
    }
}

/**
 * @brief Main ACC update function - call this regularly
 */
void ACC_Update(void) {
    uint32_t current_time = HAL_GetTick();

    // Check if it's time to update sensors
    if (current_time - acc_control.last_update_time >= ACC_UPDATE_INTERVAL) {
        acc_control.last_update_time = current_time;

        // Process sensor readings
        ACC_ProcessSensors();

        // Handle different ACC states
        switch (acc_control.state) {
            case ACC_DISABLED:
                // Do nothing
                break;

            case ACC_ENABLED:
            case ACC_FOLLOWING:
                ACC_SpeedControl();
                ACC_ObstacleAvoidance();
                ACC_LaneChangeControl();
                break;

            case ACC_EMERGENCY_BRAKE:
                ACC_EmergencyBrake();
                break;

            case ACC_LANE_CHANGE_LEFT:
            case ACC_LANE_CHANGE_RIGHT:
                ACC_LaneChangeControl();
                break;

            case ACC_OBSTACLE_AVOIDANCE:
                ACC_ObstacleAvoidance();
                break;
        }
    }
    Turn_Left(ACC_RightDistance() , ACC_LeftDistance(), acc_control.current_speed);
    Turn_Right(ACC_RightDistance() , ACC_LeftDistance(), acc_control.current_speed);
}

/**
 * @brief Process ultrasonic sensor readings
 */
void ACC_ProcessSensors(void) {
    // Read front sensor
    acc_control.front_distance = measureDistance(
        triggerPorts[FRONT_SENSOR], triggerPins[FRONT_SENSOR],
        echoPorts[FRONT_SENSOR], echoPins[FRONT_SENSOR]
    );

    // Read left sensor
    acc_control.left_distance = measureDistance(
        triggerPorts[LEFT_SENSOR], triggerPins[LEFT_SENSOR],
        echoPorts[LEFT_SENSOR], echoPins[LEFT_SENSOR]
    );

    // Read right sensor
    acc_control.right_distance = measureDistance(
        triggerPorts[RIGHT_SENSOR], triggerPins[RIGHT_SENSOR],
        echoPorts[RIGHT_SENSOR], echoPins[RIGHT_SENSOR]
    );

    // Check for obstacles
    acc_control.obstacle_detected = (acc_control.front_distance < acc_control.following_distance);
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
 * @brief Handle obstacle avoidance
 */
void ACC_ObstacleAvoidance(void) {
    // Check if obstacle is too close and blocking
    if (acc_control.front_distance <= ACC_MIN_DISTANCE &&
        acc_control.current_speed > 0) {

        // Try lane change if possible
        if (ACC_IsSafeToChangeLane(1)) {  // Try left first
            acc_control.lane_change_request = 1;
            acc_control.state = ACC_LANE_CHANGE_LEFT;
        } else if (ACC_IsSafeToChangeLane(2)) {  // Then try right
            acc_control.lane_change_request = 2;
            acc_control.state = ACC_LANE_CHANGE_RIGHT;
        } else {
            // No safe lane change - emergency brake
            acc_control.state = ACC_EMERGENCY_BRAKE;
        }
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
 * @brief Handle lane change maneuvers
 */
void ACC_LaneChangeControl(void) {
    uint32_t current_time = HAL_GetTick();

    // Initialize lane change
    if (acc_control.lane_change_request > 0 && lane_change_start_time == 0) {
        if (ACC_IsSafeToChangeLane(acc_control.lane_change_request)) {
            lane_change_start_time = current_time;

            // Execute turn based on direction
            if (acc_control.lane_change_request == 1) {
                // Turn left
                Turn_Left(acc_control.right_distance, acc_control.left_distance, acc_control.current_speed);
            } else {
                // Turn right
                Turn_Right(acc_control.right_distance, acc_control.left_distance, acc_control.current_speed);
            }
        } else {
            // Lane change not safe, abort
            ACC_ResetLaneChange();
        }
    }

    // Check lane change timeout
    if (lane_change_start_time > 0 && (current_time - lane_change_start_time) > ACC_LANE_CHANGE_TIMEOUT) {
        // Lane change complete or timed out
        ACC_ResetLaneChange();
        acc_control.state = ACC_ENABLED;
        Move_Forward();  // Resume forward motion
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

/**
 * @brief Check if lane change is safe
 * @param direction: 1 for left, 2 for right
 * @return 1 if safe, 0 if not safe
 */
uint8_t ACC_IsSafeToChangeLane(uint8_t direction) {
    if (direction == 1) {
        // Check left lane
        return (acc_control.left_distance >= ACC_LANE_CHANGE_DISTANCE);
    } else if (direction == 2) {
        // Check right lane
        return (acc_control.right_distance >= ACC_LANE_CHANGE_DISTANCE);
    }
    return 0;
}

/**
 * @brief Reset lane change state
 */
void ACC_ResetLaneChange(void) {
    acc_control.lane_change_request = 0;
    lane_change_start_time = 0;
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
uint32_t ACC_RightDistance(void){
	return acc_control.right_distance;
}
uint32_t ACC_LeftDistance(void){
	return acc_control.left_distance;
}
