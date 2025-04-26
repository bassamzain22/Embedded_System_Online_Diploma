#include "Motor_L298N.h"

#define max_speed 1000  //from 0-->1000 note do not increase it above 1000
#define min_speed				  0

#define action_distance     	  40  				 // cm
#define min_distance   		      10  			 	 // cm
#define braking_distance          5                  // cm
#define turn_distance             10                 // cm



// Define motor control pins
#define IN1  pin4  // PA1 - IN1
#define IN2  pin5  // PA2 - IN2
#define IN3  pin6  // PA3 - IN3
#define IN4  pin7  // PA4 - IN4

// Initialize motor control pins
void Motors_Init(void) {
    GPIOA_CLOCK_ENABLE;
    MCAL_speed_init(CLK_SORC_IN_CLK8MHz, mood_FAST_MOOD_36MHzCORE);
    pinmode(GPIOA, IN1, GPIO_MODE_OUTPUT_push_pull_Speed50);
    pinmode(GPIOA, IN2, GPIO_MODE_OUTPUT_push_pull_Speed50);
    pinmode(GPIOA, IN3, GPIO_MODE_OUTPUT_push_pull_Speed50);
    pinmode(GPIOA, IN4, GPIO_MODE_OUTPUT_push_pull_Speed50);


    Motors_Stop();
}
void Set_Speed(uint32_t speed){
    PWM(TIM1, CH_1, speed, 3500, clk);
    PWM(TIM1, CH_3, speed, 3500, clk);
}

// Move forward (both motors forward)
void Move_Forward(void) {
    // Right motor forward (IN1=1, IN2=0)
    pinwrite(GPIOA, IN1, HIGH);
    pinwrite(GPIOA, IN2, LOW);

    // Left motor forward (IN3=1, IN4=0)
    pinwrite(GPIOA, IN3, HIGH);
    pinwrite(GPIOA, IN4, LOW);
}

// Move backward (both motors backward)
void Move_Backward(void) {
    // Right motor backward (IN1=0, IN2=1)
    pinwrite(GPIOA, IN1, LOW);
    pinwrite(GPIOA, IN2, HIGH);

    // Left motor backward (IN3=0, IN4=1)
    pinwrite(GPIOA, IN3, LOW);
    pinwrite(GPIOA, IN4, HIGH);
}

// Turn left (right motor forward, left motor backward)
void Move_Right(void) {
    // Right motor forward (IN1=1, IN2=0)
    pinwrite(GPIOA, IN1, HIGH);
    pinwrite(GPIOA, IN2, LOW);

    // Left motor backward (IN3=0, IN4=1)
    pinwrite(GPIOA, IN3, LOW);
    pinwrite(GPIOA, IN4, HIGH);

}

// Turn right (left motor forward, right motor backward)
// note that you reverse connection at IN3,4 is right motor and In1,2 left motor
void Move_Left(void) {
    // Left motor forward (IN1=1, IN2=0)
    pinwrite(GPIOA, IN1, LOW);
    pinwrite(GPIOA, IN2, HIGH);

    // Right motor backward (IN1=3, IN2=4)
    pinwrite(GPIOA, IN3, HIGH);
    pinwrite(GPIOA, IN4, LOW);

}

// Stop all motors
void Motors_Stop(void) {
    // Right motor stop (IN1=0, IN2=0)
    pinwrite(GPIOA, IN1, LOW);
    pinwrite(GPIOA, IN2, LOW);

    // Left motor stop (IN3=0, IN4=0)
    pinwrite(GPIOA, IN3, LOW);
    pinwrite(GPIOA, IN4, LOW);

}



void speed_increment(uint32_t *current_speed, uint32_t V2_speed, uint32_t distance) {
    if (distance > action_distance+5) {
       if(V2_speed == max_speed){
    	   *current_speed = V2_speed;
       }
       else if(V2_speed < max_speed){
    	   if(distance - action_distance > 15){
    		   if(V2_speed<=700) *current_speed = V2_speed + 200;
    		   else if (V2_speed > 700) *current_speed = max_speed;

    	   }
    	   if(distance-action_distance <= 15 && distance-action_distance > 5){
    		   if(V2_speed<=700) *current_speed = V2_speed + 100;
    		    else if (V2_speed > 700) *current_speed = max_speed;


    	   }

       }
       // Update PWM with new speed
       Set_Speed(*current_speed);
    }


}

void speed_decrement(uint32_t *current_speed, uint32_t V2_speed, uint32_t distance) {
  if(distance <= action_distance && distance >= min_distance )
  {
	  *current_speed = V2_speed-100;
	  if(*current_speed < 0 )*current_speed = V2_speed;
      // Update PWM with new speed
      Set_Speed(*current_speed);
  }


}
void speed_increment_distance(uint32_t *current_speed , uint32_t distance){
	if (distance > action_distance+5) {


	    	   if(distance - action_distance > 15){
	    		   if(*current_speed<=700) *current_speed += 200;
	    		   else if (*current_speed > 700) *current_speed = max_speed;


	    	   if(distance-action_distance <= 15 && distance-action_distance > 5){
	    		   if(*current_speed<=700) *current_speed += 100;
	    		    else if (*current_speed > 700) *current_speed = max_speed;


	    	   }

	       }
	       // Update PWM with new speed
	       Set_Speed(*current_speed);
	    }

}
void speed_decrement_distance(uint32_t *current_speed , uint32_t distance){
	if(distance <= action_distance && distance >= min_distance )
	  {
		  *current_speed-= 100;
		  if(*current_speed < 0 )*current_speed = min_speed;
	      // Update PWM with new speed
	      Set_Speed(*current_speed);
	  }

}
void Turn_left(uint32_t current_speed ,uint32_t Left_distance, uint32_t Right_distance){
	if(Right_distance <= turn_distance && Left_distance > turn_distance + 5 ){
		if (current_speed <= max_speed && current_speed>= 800) {
			Move_Left();
			delay(1000, U_ms, clk);
		}
		else if (current_speed < 800 && current_speed>= 600) {
					Move_Left();
					delay(2000, U_ms, clk);
				}
		else if (current_speed <600 && current_speed >= 500) {
							Move_Left();
							delay(3000, U_ms, clk);
						}
		else {
			Move_Left();
			delay(3500, U_ms, clk);
		}

	}
	Move_Forward();

}
void Turn_right(uint32_t current_speed  , uint32_t Left_distance , uint32_t Right_distance){
	if(Left_distance <= turn_distance && Right_distance > turn_distance + 5 ){
			if (current_speed <= max_speed && current_speed>= 800) {
				Move_Right();
				delay(500, U_ms, clk);
			}
			else if (current_speed < 800 && current_speed>= 600) {
						Move_Right();
						delay(1000, U_ms, clk);
					}
			else if (current_speed <600 && current_speed >= 500) {
								Move_Right();
								delay(1500, U_ms, clk);
							}
			else {
				Move_Right();
				delay(2500, U_ms, clk);
			}

		}
		Move_Forward();
}
void Move_Stop(uint32_t *current_speed , uint32_t distance){
	if (distance <= braking_distance)*current_speed = min_speed;
	Set_Speed(*current_speed);
}
