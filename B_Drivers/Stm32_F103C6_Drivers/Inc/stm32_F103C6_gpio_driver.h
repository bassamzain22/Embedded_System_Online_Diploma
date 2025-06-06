/*
 * stm32f103x8_gpio_driver.h
 *
 *  Created on: Oct 8, 2024
 *      Author: Mohamed Abd El Hakeem El Said Ali
 */

#ifndef INC_STM32F103X6_GPIO_DRIVER_H_
#define INC_STM32F103X6_GPIO_DRIVER_H_




//-----------------------------
//Includes
#include "stm32f103x6.h"
//-----------------------------

//========================================
///////////////////********************************By bassam zain*********************************************??????
//////***********************************************Start*****************************************************/////
#define pin0  0
#define pin1  1
#define pin2  2
#define pin3  3
#define pin4  4
#define pin5  5
#define pin6  6
#define pin7  7
#define pin8  8
#define pin9  9
#define pin10 10
#define pin11 11
#define pin12 12
#define pin13 13
#define pin14 14
#define pin15 15
//*******************************
//pin modes
//*******************************
//CNFy[1:0]: Port x configuration bits (y= 0 .. 7)
//These bits are written by software to configure the corresponding I/O port.
//Refer to Table 20: Port bit configuration table.
//In input mode (MODE[1:0]=00):
//00: Analog mode
//01: Floating input (reset state)
//10: Input with pull-up / pull-down
//11: Reserved
//In output mode (MODE[1:0] > 00):
//00: General purpose output push-pull
//01: General purpose output Open-drain
//10: Alternate function output Push-pull
//11: Alternate function output Open-drain
//Bits 29:28, 25:24,
//21:20, 17:16, 13:12,
//9:8, 5:4, 1:0
//MODEy[1:0]: Port x mode bits (y= 0 .. 7)
//These bits are written by software to configure the corresponding I/O port.
//Refer to Table 20: Port bit configuration table.
//00: General purpose output push-pull
//01: General purpose output Open-drain
//10: Alternate function output Push-pull
//11: Alternate function output Open-drain
//00: Input mode (reset state)
//01: Output mode, max speed 10 MHz.
//10: Output mode, max speed 2 MHz.
//11: Output mode, max speed 50 MHz.

#define GPIO_MODE_ANALOG			   				0b0000     // 00: Analog mode 00: Input mode (reset state)
#define GPIO_MODE_INPUT_FLO			   				0b0100    //01: Floating input (reset state) 00: Input mode (reset state)
#define GPIO_MODE_INPUT_PU							0b11000  // 10: Input with pull-up  00: Input mode (reset state)
#define GPIO_MODE_INPUT_PD							0b01000 //10: Input with  pull-down  00: Input mode (reset state)
#define GPIO_MODE_INTPUT_AF		       			 	0b0100 // 00: Input mode (reset state)

#define GPIO_MODE_OUTPUT_push_pull_Speed10			0b0001  //00: General purpose output push-pull
#define GPIO_MODE_OUTPUT_push_pull_Speed2			0b0010 //00: General purpose output push-pull
#define GPIO_MODE_OUTPUT_push_pull_Speed50			0b0011//00: General purpose output push-pull

#define GPIO_MODE_OUTPUT_Open_drain_Speed10			0b0101  //01: General purpose output Open-drain
#define GPIO_MODE_OUTPUT_Open_drain_Speed2			0b0110 //01: General purpose output Open-drain
#define GPIO_MODE_OUTPUT_Open_drain_Speed50			0b0111//01: General purpose output Open-drain

#define GPIO_MODE_OUTPUT_AF_push_pull_Speed10		0b1001  //10: Alternate function output Push-pull
#define GPIO_MODE_OUTPUT_AF_push_pull_Speed2		0b1010 //10: Alternate function output Push-pull
#define GPIO_MODE_OUTPUT_AF_push_pull_Speed50		0b1011//10: Alternate function output Push-pull

#define GPIO_MODE_OUTPUT_AF_Open_drain_Speed10		0b1101  //11: Alternate function output Open-drain
#define GPIO_MODE_OUTPUT_AF_Open_drain_Speed2		0b1110 //11: Alternate function output Open-drain
#define GPIO_MODE_OUTPUT_AF_Open_drain_Speed50		0b1111//11: Alternate function output Open-drain


//=====================================================
#define HIGH 1
#define LOW  0
//*************************
 //API   ==  ==  ==  ==  ==
//*************************

void pinmode(GPIO_TypedDef* GPIOx,uint16_t pin,uint32_t pinmode);//port , pin , mode
void pinwrite(GPIO_TypedDef* GPIOx,uint16_t pin,uint8_t status);
void WRITE_PORT(GPIO_TypedDef* GPIOx,uint16_t status);
void set_Value_PORT(GPIO_TypedDef* GPIOx,uint16_t status,uint16_t position);
void res_Value_PORT(GPIO_TypedDef* GPIOx,uint16_t status,uint16_t position);
uint8_t READ_PIN(GPIO_TypedDef* GPIOx, uint16_t pin);
uint16_t READ_PORT(GPIO_TypedDef* GPIOx);
void TogglePin(GPIO_TypedDef* GPIOx, uint16_t pin);
uint8_t MCAL_GPIO_LockPin(GPIO_TypedDef* GPIOx, uint16_t pin_number);
//////***********************************************End*****************************************************/////

//GPIO  PIN States
#define GPIO_PIN_SET        1
#define GPIO_PIN_RESET      0


//GPIO PIN_LOCK State
#define GPIO_PIN_LOCK_ENABLED    1
#define GPIO_PIN_LOCK_FAILED     0






//-----------------------------
//User type definitions (structures)
typedef struct
{

	uint16_t GPIO_PinNumber ;     //Specifies the GPIO Pin_Number
							     //This Parameter can be a value of @ref GPIO_PINS_Define

	uint32_t GPIO_Mode;           //Specifies the operating mode for the selected pin
							     //This Parameter can be a value of @ref GPIO_Mode_Define

	uint32_t GPIO_Speed;   //Specifies the speed for the selected pin
								 //This Parameter can be a value of @ref GPIO_Speed_Define
}GPIO_PinConfig_t;
//-----------------------------



//-----------------------------
//Macros Configuration References

/* @ref GPIO_PINS_Define */
#define  GPIO_PIN_0       ((uint16_t) 0x0001)
#define  GPIO_PIN_1       ((uint16_t) 0x0002)
#define  GPIO_PIN_2       ((uint16_t) 0x0004)
#define  GPIO_PIN_3       ((uint16_t) 0x0008)
#define  GPIO_PIN_4       ((uint16_t) 0x0010)
#define  GPIO_PIN_5       ((uint16_t) 0x0020)
#define  GPIO_PIN_6       ((uint16_t) 0x0040)
#define  GPIO_PIN_7       ((uint16_t) 0x0080)
#define  GPIO_PIN_8       ((uint16_t) 0x0100)
#define  GPIO_PIN_9       ((uint16_t) 0x0200)
#define  GPIO_PIN_10      ((uint16_t) 0x0400)
#define  GPIO_PIN_11      ((uint16_t) 0x0800)
#define  GPIO_PIN_12      ((uint16_t) 0x1000)
#define  GPIO_PIN_13      ((uint16_t) 0x2000)
#define  GPIO_PIN_14      ((uint16_t) 0x4000)
#define  GPIO_PIN_15      ((uint16_t) 0x8000)
#define  GPIO_PIN_ALL     ((uint16_t) 0xFFFF)

//-----------------------------



/*@ref GPIO_Mode_Define*/
/* CNFy[1:0]
>>>>>>>>>>>>>>>>>>>>>>>>In input mode:
00: Analog mode
01: Floating input (reset state)
10: Input with pull-up / pull-down
11: Reserved
>>>>>>>>>>>>>>>>>>>>>>>In output mode:
00: General purpose output push-pull
01: General purpose output Open-drain
10: Alternate function output Push-pull
11: Alternate function output Open-drain
*/


#define GPIO_Mode_Inp_Analog               (0x00000000u)
#define GPIO_Mode_Inp_Floating             (0x00000001u)
#define GPIO_Mode_Inp_pull_up              (0x00000002u)
#define GPIO_Mode_Inp_pull_down            (0x00000003u)
#define GPIO_Mode_Inp_AF                   (0x00000001u)

#define GPIO_Mode_Out_push_pull            (0x00000004u)
#define GPIO_Mode_Out_Open_drain           (0x00000005u)
#define GPIO_Mode_Out_AF_push_pull         (0x00000006u)
#define GPIO_Mode_Out_AF_Open_drain        (0x00000007u)



/*@ref GPIO_Speed_Define*/
/*MODEy[1:0]: Port x mode bits (y= 0 .. 7), In Case Of Output Mode
These bits are written by software to configure the corresponding I/O port
00: Input mode (reset state)
01: Output mode, max speed 10 MHz.
10: Output mode, max speed 2 MHz.
11: Output mode, max speed 50 MHz
*/

#define GPIO_Speed_Reset_State          (0x00000000u)  // you should set this define in case of Input_Mode
#define GPIO_Speed_10MHz            	(0x00000001u)
#define GPIO_Speed_2MHz             	(0x00000002u)
#define GPIO_Speed_50MHz            	(0x00000003u)






/*
 * ===============================================
 * APIs Supported by "MCAL GPIO DRIVER"
 * ===============================================
 */

void MCAL_GPIO_Enable_ClocK(GPIO_TypedDef* GPIOx);

void MCAL_GPIO_Init(GPIO_TypedDef* GPIOx, GPIO_PinConfig_t* PinConfig );
void MCAL_GPIO_DInit(GPIO_TypedDef* GPIOx);

uint8_t  MCAL_GPIO_ReadPin(GPIO_TypedDef* GPIOx,uint16_t PinNumber );
uint16_t MCAL_GPIO_ReadPort(GPIO_TypedDef* GPIOx);


void MCAL_GPIO_WritePin(GPIO_TypedDef* GPIOx,uint16_t PinNumber , uint8_t Value);
void MCAL_GPIO_WritePort(GPIO_TypedDef* GPIOx, uint16_t Value);


void MCAL_GPIO_TogglePin(GPIO_TypedDef* GPIOx,uint16_t PinNumber);

uint8_t MCAL_GPIO_LockPin(GPIO_TypedDef* GPIOx,uint16_t PinNumber);









#endif /* INC_STM32F103X6_GPIO_DRIVER_H_ */
