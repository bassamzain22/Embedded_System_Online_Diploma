/**
 ******************************************************************************
 * @file           : main.c
 * @author         : bassam zain
 * @brief          :
 ******************************************************************************
 */
#include "stm32_speed_DRIVER.h"
#include "STM32_TIMERS_DRIVER.h"
#include "Motor_L298N.h"
#include "stm32f103c6_ISR_DRIVER.h"
//===================================
#define clk 36000000

uint32_t speed = 1000; // global to change speed


int main(void)
{

	Motors_Init();

	Set_Speed(speed);
	while(1){

		Move_Forward();
	    delay(5000, U_ms, clk);

		Move_Right();

		delay(5000, U_ms, clk);



		Motors_Stop();
		delay(3000, U_ms, clk);

		Move_Left();
		delay(5000, U_ms, clk);

		Move_Backward();
		delay(5000, U_ms, clk);



			//===========================================================

	}
}
