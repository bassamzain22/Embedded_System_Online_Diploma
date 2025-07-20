/*
 * IMA.h
 *
 */

#ifndef INC_IMA_H_
#define INC_IMA_H_

#include "stdint.h"
#include "NMEA.h"
#include "stdio.h"
#include "string.h"
#include "math.h"
#include "mpu6050.h"
#include "i2c-lcd.h"
#include "uartRingBuffer.h"


#define COLLISION_WARNING_THRESHOLD 50  // meters
#define COLLISION_CRITICAL_THRESHOLD 20 // meters
#define WARNING_TIMEOUT 5000  // 5 seconds before auto-braking
#define MAX_SPEED_REDUCTION 0.5  // Maximum speed reduction factor

typedef struct {
    float latitude;
    float longitude;
    float speed;
    float course;
    float acceleration[3];  // x, y, z acceleration from MPU6050
} VehicleData;

typedef struct {
    VehicleData localVehicle;
    VehicleData remoteVehicle;
    uint8_t collisionRisk;  // 0: No risk, 1: Warning, 2: Critical
    uint32_t warningStartTime;
} CollisionDetection;


float calculateDistance(float lat1, float lon1, float lat2, float lon2) ;
// Update local vehicle data from GPS and MPU
void updateLocalVehicleData(void);
// Send vehicle data to other vehicle
void sendVehicleData(void) ;
// Check for collision risk
void checkCollisionRisk(void);
// Display warning on LCD
void displayWarning(void);

void IMA_Update(void);
#endif /* INC_IMA_H_ */
