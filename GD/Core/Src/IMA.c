/*
 * IMA.c
 * 		Author:Omar shawki
 */
#include "IMA.h"


extern UART_HandleTypeDef huart2;

char GGA[100];
char RMC[100];
GPSSTRUCT gpsData;
Struct_MPU6050 mpuData;
CollisionDetection collisionData;
int flagGGA = 0, flagRMC = 0;
char lcdBuffer[50];
int VCCTimeout = 5000;
// Calculate distance between two GPS coordinates in meters
float calculateDistance(float lat1, float lon1, float lat2, float lon2) {
	const float R = 6371000; // Earth's radius in meters
	float lat1Rad = lat1 * M_PI / 180.0;
	float lat2Rad = lat2 * M_PI / 180.0;
	float deltaLat = (lat2 - lat1) * M_PI / 180.0;
	float deltaLon = (lon2 - lon1) * M_PI / 180.0;

	float a = sin(deltaLat/2) * sin(deltaLat/2) +
			cos(lat1Rad) * cos(lat2Rad) *
			sin(deltaLon/2) * sin(deltaLon/2);
	float c = 2 * atan2(sqrt(a), sqrt(1-a));
	return R * c;
}

// Update local vehicle data from GPS and MPU
void updateLocalVehicleData(void) {
	if (flagGGA == 2) {
		collisionData.localVehicle.latitude = gpsData.ggastruct.lcation.latitude;
		collisionData.localVehicle.longitude = gpsData.ggastruct.lcation.longitude;
	}
	if (flagRMC == 2) {
		collisionData.localVehicle.speed = gpsData.rmcstruct.speed;
		collisionData.localVehicle.course = gpsData.rmcstruct.course;
	}

	// Update MPU data
	collisionData.localVehicle.acceleration[0] = mpuData.acc_x_raw;
	collisionData.localVehicle.acceleration[1] = mpuData.acc_y_raw;
	collisionData.localVehicle.acceleration[2] = mpuData.acc_z_raw;
}

// Send vehicle data to other vehicle
void sendVehicleData(void) {
	char dataBuffer[100];
	sprintf(dataBuffer, "VDATA:%.6f,%.6f,%.2f,%.2f,%.2f,%.2f,%.2f\r\n",
			collisionData.localVehicle.latitude,
			collisionData.localVehicle.longitude,
			collisionData.localVehicle.speed,
			collisionData.localVehicle.course,
			collisionData.localVehicle.acceleration[0],
			collisionData.localVehicle.acceleration[1],
			collisionData.localVehicle.acceleration[2]);

	HAL_UART_Transmit(&huart2, (uint8_t*)dataBuffer, strlen(dataBuffer), HAL_MAX_DELAY);
}

// Check for collision risk
void checkCollisionRisk(void) {
	float distance = calculateDistance(
			collisionData.localVehicle.latitude,
			collisionData.localVehicle.longitude,
			collisionData.remoteVehicle.latitude,
			collisionData.remoteVehicle.longitude
	);

	if (distance < COLLISION_CRITICAL_THRESHOLD) {
		collisionData.collisionRisk = 2; // Critical
		if (HAL_GetTick() - collisionData.warningStartTime > WARNING_TIMEOUT) {
			// Implement emergency braking
			// TODO: Add motor control code here
		}
	}
	else if (distance < COLLISION_WARNING_THRESHOLD) {
		collisionData.collisionRisk = 1; // Warning
		if (collisionData.warningStartTime == 0) {
			collisionData.warningStartTime = HAL_GetTick();
		}
	}
	else {
		collisionData.collisionRisk = 0; // No risk
		collisionData.warningStartTime = 0;
	}
}

// Display warning on LCD
void displayWarning(void) {
	lcd_put_cur(0, 0);
	switch(collisionData.collisionRisk) {
	case 0:
		lcd_send_string("No Collision Risk");
		break;
	case 1:
		lcd_send_string("Warning: Vehicle");
		lcd_put_cur(1, 0);
		lcd_send_string("Nearby! Slow Down");
		break;
	case 2:
		lcd_send_string("CRITICAL: STOP!");
		lcd_put_cur(1, 0);
		lcd_send_string("Emergency Brake");
		break;
	}
}
void IMA_Update(void){
	if (Wait_for("GGA") == 1)
	{
		VCCTimeout = 5000;  // Reset the VCC Timeout indicating the GGA is being received
		Copy_upto("*", GGA);
		if (decodeGGA(GGA, &gpsData.ggastruct) == 0) flagGGA = 2;  // 2 indicates the data is valid
		else flagGGA = 1;  // 1 indicates the data is invalid
	}

	if (Wait_for("RMC") == 1)
	{
		VCCTimeout = 5000;  // Reset the VCC Timeout indicating the RMC is being received
		Copy_upto("*", RMC);
		if (decodeRMC(RMC, &gpsData.rmcstruct) == 0) flagRMC = 2;  // 2 indicates the data is valid
		else flagRMC = 1;  // 1 indicates the data is invalid
	}

	// Update local vehicle data
	updateLocalVehicleData();

	// Send data to other vehicle
	sendVehicleData();

	// Check for incoming data from other vehicle
	if (IsDataAvailable() > 0) {
		char rxBuffer[100];
		int i = 0;
		while (IsDataAvailable() > 0 && i < 99) {
			rxBuffer[i] = Uart_read();
			if (rxBuffer[i] == '\n') {
				rxBuffer[i] = '\0';
				break;
			}
			i++;
		}
		rxBuffer[99] = '\0';

		// Parse received data
		if (strncmp(rxBuffer, "VDATA:", 6) == 0) {
			sscanf(rxBuffer + 6, "%f,%f,%f,%f,%f,%f,%f",
					&collisionData.remoteVehicle.latitude,
					&collisionData.remoteVehicle.longitude,
					&collisionData.remoteVehicle.speed,
					&collisionData.remoteVehicle.course,
					&collisionData.remoteVehicle.acceleration[0],
					&collisionData.remoteVehicle.acceleration[1],
					&collisionData.remoteVehicle.acceleration[2]);
		}
	}

	// Check for collision risk
	checkCollisionRisk();

	// Display warnings
	displayWarning();

	// Handle VCC timeout
	if (VCCTimeout <= 0)
	{
		VCCTimeout = 5000;  // Reset the timeout
		flagGGA = flagRMC = 0;
		lcd_put_cur(0, 0);
		lcd_send_string("    VCC Issue   ");
		lcd_put_cur(1, 0);
		lcd_send_string("Check Connection");
	}



}
