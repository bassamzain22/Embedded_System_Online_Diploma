
#include "STM32_TIMERS_DRIVER.h"
#include "stm32_F103C6_gpio_driver.h"
#include "stm32f103c6_ISR_DRIVER.h"
#include "Ultrasonic_driver.h"
#include "Motor_L298N.h"
#include <stdio.h>

#define DISTANCE_THRESHOLD 40  // Distance threshold in cm
#define LED_DURATION 5000  // 5 seconds in milliseconds
uint32_t V2_speed  = 1000;


uint32_t current_speed = 700;



int main() {
	Ultrasonic_Init();
	Motors_Init();
	Set_Speed(current_speed);

    while(1) {
        Move_Forward();
        uint32_t distance = Get_Distance_Front();
        speed_increment(&current_speed, V2_speed, distance);
        delay(3000, U_ms, clk);
        speed_decrement(&current_speed, V2_speed, distance);

        delay(3000, U_ms, clk);

        uint32_t Left_distance = Get_Distance_Left();

        uint32_t Right_distance = Get_Distance_Right();

        Turn_left(current_speed , Left_distance , Right_distance);
        delay(3000, U_ms, clk);
        Turn_right(current_speed , Left_distance , Right_distance);
        delay(3000, U_ms, clk);
    }

}
