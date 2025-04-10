/*
 * STM32F103X8.h
 *
 *  Created on: Oct 8, 2024
 *      Author: Mohamed Abd El Hakeem El Said Ali
 */

#ifndef INC_STM32F103X6_H_
#define INC_STM32F103X6_H_




//-----------------------------
//Includes
#include <stdio.h>
#include <stdlib.h>
//-----------------------------


//-----------------------------
//Base addresses for Memories
#define FLASH_Memory_BASE     						0x08000000UL
#define System_Memory_BASE     						0x1FFFF000UL
#define SRAM_BASE              						0x20000000UL

#define Peripherals_BASE       						0x40000000UL

#define Cortex_M3_Internal_Peripherals_BASE         0xE0000000UL
//-----------------------------

//...............................
//NVIC_Adresses
#define NVIC_BASE									0xE000E100UL
#define NVIC_ISER0       				*(volatile unsigned long *)(NVIC_BASE+ 0x000)
#define NVIC_ISER1       				*(volatile unsigned long *)(NVIC_BASE+ 0x004)
#define NVIC_ISER2       				*(volatile unsigned long *)(NVIC_BASE+ 0x008)
#define NVIC_ICER0       				*(volatile unsigned long *)(NVIC_BASE+ 0x080)
#define NVIC_ICER1       				*(volatile unsigned long *)(NVIC_BASE+ 0x084)
#define NVIC_ICER2       				*(volatile unsigned long *)(NVIC_BASE+ 0x088)






//-----------------------------
//Base addresses for BUS Peripherals
/*Base addresses for AHB Peripherals*/
#define RCC_BASE                                  (Peripherals_BASE + 0x00021000UL)



/*Base addresses for APB2  Peripherals*/

//GPIO
//A, B fully included in LQFP48 Package
#define GPIOA_BASE      (Peripherals_BASE + 0x00010800UL)
#define GPIOB_BASE      (Peripherals_BASE + 0x00010C00UL)
//C, D partial included in LQFP48 Package
#define GPIOC_BASE      (Peripherals_BASE + 0x00011000UL)
#define GPIOD_BASE      (Peripherals_BASE + 0x00011400UL)
//E, P Not  included in LQFP48 Package
#define GPIOE_BASE      (Peripherals_BASE + 0x00011800UL)


//Alternative & External Interrupt
#define AFIO_BASE      (Peripherals_BASE + 0x00010000UL)
#define EXTI_BASE      (Peripherals_BASE + 0x00010400UL)



#define USART1_BASE             (Peripherals_BASE + 0x00013800UL)
//-----------------------------
//Base addresses for APB1 Peripherals
//-----------------------------
#define USART2_BASE             (Peripherals_BASE + 0x00004400UL)
#define USART3_BASE             (Peripherals_BASE + 0x00004800UL)



#define SPI1_BASE              	0x40013000UL
#define SPI2_BASE         	    0x40003800UL


//I2C
#define I2C1_BASE				0x40005400UL
#define I2C2_BASE				0x40005800UL


//..........
//-----------------------------




//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register:RCC
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{

	volatile uint32_t CR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t APB2RSTR;
	volatile uint32_t APB1RSTR;
	volatile uint32_t AHBENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t APB1ENR;
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
}RCC_TypedDef;




//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register:GPIO
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{

	volatile uint32_t CRL;
	volatile uint32_t CRH;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t BRR;
	volatile uint32_t LCKR;
}GPIO_TypedDef;


//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register:AFIO
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{

	volatile uint32_t EVCR;
	volatile uint32_t MAPR;
	volatile uint32_t EXTICR[4];
	uint32_t RESERVED0;
	volatile uint32_t MAPR2;
}AFIO_TypedDef;


//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register:EXTI
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{

	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;
}EXTI_TypedDef;




//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: USART
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t BRR;
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t CR3;
	volatile uint32_t GTPR;
} USART_TypeDef;



typedef struct
{
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t CRCPR;
	volatile uint32_t RXCRCR;
	volatile uint32_t TXCRCR;
	volatile uint32_t I2SCFGR;
	volatile uint32_t I2SPR;
}SPI_TypeDef;



//========================================================
//		    Peripheral Registers : I2C
//========================================================

typedef struct
{
	volatile uint32_t CR1 ;					//Control Register 	1				(0x00)
	volatile uint32_t CR2 ;					//Control Register 	2				(0x04)
	volatile uint32_t OAR1 ;				//Own Address Register	1			(0x08)
	volatile uint32_t OAR2 ;				//Own Address Register	2			(0x0C)
	volatile uint32_t DR ;					//Data Register						(0x10)
	volatile uint32_t SR1 ;					//Status Register 1					(0x14)
	volatile uint32_t SR2 ;					//Status Register 2					(0x18)
	volatile uint32_t CCR ;					//Clock Control Register			(0x1C)
	volatile uint32_t TRISE ;				//Rise Time Register				(0x20)
}I2C_TypeDef;



//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*





//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants:
#define RCC     			 ((RCC_TypedDef*) RCC_BASE    )


#define GPIOA                ((GPIO_TypedDef*) GPIOA_BASE )
#define GPIOB                ((GPIO_TypedDef*) GPIOB_BASE )
#define GPIOC                ((GPIO_TypedDef*) GPIOC_BASE )
#define GPIOD                ((GPIO_TypedDef*) GPIOD_BASE )
#define GPIOE                ((GPIO_TypedDef*) GPIOE_BASE )

#define AFIO                 ((AFIO_TypedDef*) AFIO_BASE  )
#define EXTI                 ((EXTI_TypedDef*) EXTI_BASE  )

#define USART1                ((USART_TypeDef *)USART1_BASE)
#define USART2                ((USART_TypeDef *)USART2_BASE)
#define USART3                ((USART_TypeDef *)USART3_BASE)


#define SPI1				  ((SPI_TypeDef *)SPI1_BASE)
#define SPI2				  ((SPI_TypeDef *)SPI2_BASE)

#define I2C1				  ((I2C_TypeDef *)I2C1_BASE)
#define I2C2				  ((I2C_TypeDef *)I2C2_BASE)

//-*-*-*-*-*-*-*-*-*-*-*



//-*-*-*-*-*-*-*-*-*-*-*-
//clock enable Macros:RCC_GPIO
#define GPIOA_CLOCK_ENABLE     (RCC->APB2ENR |= (1 << 2)  )
#define GPIOB_CLOCK_ENABLE     (RCC->APB2ENR |= (1 << 3)  )
#define GPIOC_CLOCK_ENABLE     (RCC->APB2ENR |= (1 << 4)  )
#define GPIOD_CLOCK_ENABLE     (RCC->APB2ENR |= (1 << 5)  )

//clock disable Macros:RCC_GPIO
#define GPIOA_CLOCK_DISABLE    (RCC->APB2ENR &= ~(1 << 2) )
#define GPIOB_CLOCK_DISABLE    (RCC->APB2ENR &= ~(1 << 3) )
#define GPIOC_CLOCK_DISABLE    (RCC->APB2ENR &= ~(1 << 4) )
#define GPIOD_CLOCK_DISABLE    (RCC->APB2ENR &= ~(1 << 5) )

//clock enable Macros:RCC_AFIO
#define AFIO_CLOCK_ENABLE      (RCC->APB2ENR |=  (1 << 0) )

//clock disable Macros:RCC_AFIO
#define AFIO_CLOCK_DISABLE     (RCC->APB2ENR &= ~(1 << 0) )


//Clock enable  Macros:USARTx.....
#define RCC_USART1_CLK_EN()	( RCC->APB2ENR |= (1<<14) )
#define RCC_USART2_CLK_EN()	( RCC->APB1ENR |= (1<<17) )
#define RCC_USART3_CLK_EN()	( RCC->APB1ENR |= (1<<18) )


//Clock Reset  Macros:USARTx.....
#define RCC_USART1_Reset()	( RCC->APB2RSTR |= (1<<14) )
#define RCC_USART2_Reset()	( RCC->APB1RSTR |= (1<<17) )
#define RCC_USART3_Reset()	( RCC->APB1RSTR |= (1<<18) )



//Clock enable  Macros:SPIx.....
#define RCC_SPI1_CLK_EN()	(RCC->APB2ENR |= 1 << 12)
#define RCC_SPI2_CLK_EN()	(RCC->APB1ENR |= 1 << 14)

//Clock disable  Macros:SPIx.....
#define RCC_SPI1_CLK_DI()	(RCC->APB2ENR &= ~(1 << 12))
#define RCC_SPI2_CLK_DI()	(RCC->APB1ENR &= ~(1 << 14))

//Clock reset  Macros:SPIx.....
#define RCC_SPI1_RESET()	(RCC->APB2RSTR |= 1 << 12)
#define RCC_SPI2_RESET()	(RCC->APB1RSTR |= 1 << 14)


//Enable I2C Clock
#define RCC_I2C1_CLK_EN()		(RCC->APB1ENR |= 1<<21)
#define RCC_I2C2_CLK_EN()		(RCC->APB1ENR |= 1<<22)

//Disable I2C Clock
#define RCC_I2C1_CLK_RESET()	(RCC->APB1RSTR |= 1<<21)
#define RCC_I2C2_CLK_RESET()	(RCC->APB1RSTR |= 1<<22)


//-*-*-*-*-*-*-*-*-*-*-*





//-*-*-*-*-*-*-*-*-*-*-*-
//Generic Macros:
//-*-*-*-*-*-*-*-*-*-*-*
//IVT----------EXTIx:
#define EXTI0_IRQ        0
#define EXTI1_IRQ        1
#define EXTI2_IRQ        2
#define EXTI3_IRQ        3
#define EXTI4_IRQ        4
#define EXTI5_IRQ        5
#define EXTI6_IRQ        6
#define EXTI7_IRQ        7
#define EXTI8_IRQ        8
#define EXTI9_IRQ        9
#define EXTI10_IRQ       10
#define EXTI11_IRQ       11
#define EXTI12_IRQ       12
#define EXTI13_IRQ       13
#define EXTI14_IRQ       14
#define EXTI15_IRQ       15


#define USART1_IRQ		 37
#define USART2_IRQ		 38
#define USART3_IRQ		 39




#define SPI1_IRQ		35
#define SPI2_IRQ		36



#define I2C1_EV_IRQ					31
#define I2C1_ER_IRQ					32

#define I2C2_EV_IRQ					33
#define I2C2_ER_IRQ					34




//NVIC_EXTI_IRQ_ENABLE_Define
#define NVIC_IRQ6_EXTI0_ENABLE     		       (NVIC_ISER0 |= (1 << 6))
#define NVIC_IRQ7_EXTI1_ENABLE    		       (NVIC_ISER0 |= (1 << 7))
#define NVIC_IRQ8_EXTI2_ENABLE     		       (NVIC_ISER0 |= (1 << 8))
#define NVIC_IRQ9_EXTI3_ENABLE     		       (NVIC_ISER0 |= (1 << 9))
#define NVIC_IRQ10_EXTI4_ENABLE     	       (NVIC_ISER0 |= (1 << 10))
#define NVIC_IRQ23_EXTI5_9_ENABLE    	       (NVIC_ISER0 |= (1 << 23))
#define NVIC_IRQ40_EXTI10_15_ENABLE    	       (NVIC_ISER1 |= (1 << 8)) //40-32=8

//NVIC_EXTI_IRQ_DISABLE_Define
#define NVIC_IRQ6_EXTI0_DISABLE                (NVIC_ISER0 &=  ~(1 << 6))
#define NVIC_IRQ7_EXTI1_DISABLE    		       (NVIC_ISER0 &=  ~(1 << 7))
#define NVIC_IRQ8_EXTI2_DISABLE     		   (NVIC_ISER0 &=  ~(1 << 8))
#define NVIC_IRQ9_EXTI3_DISABLE     		   (NVIC_ISER0 &=  ~(1 << 9))
#define NVIC_IRQ10_EXTI4_DISABLE     	 	   (NVIC_ISER0 &=  ~(1 << 10))
#define NVIC_IRQ23_EXTI5_9_DISABLE    	 	   (NVIC_ISER0 &=  ~(1 << 23))
#define NVIC_IRQ40_EXTI10_15_DISABLE    	   (NVIC_ISER1 &=  ~(1 << 8)) //40-32=8




//NVIC_USART_IRQ_ENABLE_Define
#define NVIC_IRQ37_USART1_Enable          	(NVIC_ISER1 |= 1<<( USART1_IRQ - 32 )) //IRQ-32
#define NVIC_IRQ38_USART2_Enable   	        (NVIC_ISER1 |= 1<<( USART2_IRQ - 32 )) //IRQ-32
#define NVIC_IRQ39_USART3_Enable   			(NVIC_ISER1 |= 1<<( USART3_IRQ - 32 )) //IRQ-32

//NVIC_USART_IRQ_DISABLE_Define
#define NVIC_IRQ37_USART1_Disable   		(NVIC_ICER1 |= 1<<( USART1_IRQ- 32 )) //IRQ-32
#define NVIC_IRQ38_USART2_Disable   		(NVIC_ICER1 |= 1<<( USART2_IRQ- 32 )) //IRQ-32
#define NVIC_IRQ39_USART3_Disable   		(NVIC_ICER1 |= 1<<( USART3_IRQ- 32 )) //IRQ-32


//NVIC_SPIx_IRQ_ENABLE_Define
#define NVIC_IRQ35_SPI1_Enable()			(NVIC_ISER1 |= 1<<(SPI1_IRQ - 32))	// SPI1
#define NVIC_IRQ36_SPI2_Enable()			(NVIC_ISER1 |= 1<<(SPI2_IRQ - 32))	// SPI2


//NVIC_SPIx_IRQ__Disable_Define
#define NVIC_IRQ35_SPI1_Disable()			(NVIC_ICER1 |= 1<<(SPI1_IRQ - 32))	// SPI1
#define NVIC_IRQ36_SPI2_Disable()			(NVIC_ICER1 |= 1<<(SPI2_IRQ - 32))	// SPI2


//NVIC_I2Cx_IRQ_Enable__Define
#define NVIC_IRQ31_I2C1_EV_Enable()			(NVIC_ISER0 |= 1<<(I2C1_EV_IRQ))
#define NVIC_IRQ32_I2C1_ER_Enable()			(NVIC_ISER1 |= 1<<(I2C1_ER_IRQ - 32))
#define NVIC_IRQ33_I2C2_EV_Enable()			(NVIC_ISER1 |= 1<<(I2C2_EV_IRQ - 32))
#define NVIC_IRQ34_I2C2_ER_Enable()			(NVIC_ISER1 |= 1<<(I2C2_ER_IRQ - 32))

//NVIC_I2Cx_IRQ_Disable__Define
#define NVIC_IRQ31_I2C1_EV_Disable()		(NVIC_ICER0 |= 1<<(I2C1_EV_IRQ))
#define NVIC_IRQ32_I2C1_ER_Disable()		(NVIC_ICER1 |= 1<<(I2C1_ER_IRQ - 32))
#define NVIC_IRQ33_I2C2_EV_Disable()		(NVIC_ICER1 |= 1<<(I2C2_EV_IRQ - 32))
#define NVIC_IRQ34_I2C2_ER_Disable()		(NVIC_ICER1 |= 1<<(I2C2_ER_IRQ - 32))

//******************************************************************
//******************************************************************
//						Timer Definition
//******************************************************************
//******************************************************************


//Timers Base Addresses (Only TIM1, TIM2, TIM3, TIM4 are used)
// TIM1 is on APB2, TIM2, TIM3 and TIM4 are on APB1
#define TIM1_BASE    (Peripherals_BASE + 0x00012C00UL)
#define TIM2_BASE    (Peripherals_BASE + 0x00000000UL)
#define TIM3_BASE    (Peripherals_BASE + 0x00000400UL)
#define TIM4_BASE    (Peripherals_BASE + 0x00000800UL)

//-----------------------------
//Timer Register Structure (for basic/general purpose registers)
//-----------------------------
// Timer Register Structure (Enhanced with CCRx Registers)
typedef struct
{
    volatile uint32_t CR1;     // Control Register 1
    volatile uint32_t CR2;     // Control Register 2
    volatile uint32_t SMCR;    // Slave Mode Control Register
    volatile uint32_t DIER;    // DMA/Interrupt Enable Register
    volatile uint32_t SR;      // Status Register
    volatile uint32_t EGR;     // Event Generation Register
    volatile uint32_t CCMR1;   // Capture/Compare Mode Register 1
    volatile uint32_t CCMR2;   // Capture/Compare Mode Register 2
    volatile uint32_t CCER;    // Capture/Compare Enable Register
    volatile uint32_t CNT;     // Counter Register
    volatile uint32_t PSC;     // Prescaler Register
    volatile uint32_t ARR;     // Auto-Reload Register
    volatile uint32_t RCR;     // Repetition Counter Register (For TIM1)
    volatile uint32_t CCR1;    // Capture/Compare Register 1
    volatile uint32_t CCR2;    // Capture/Compare Register 2
    volatile uint32_t CCR3;    // Capture/Compare Register 3
    volatile uint32_t CCR4;    // Capture/Compare Register 4
    volatile uint32_t BDTR;    // Break and Dead-Time Register (For TIM1)
    volatile uint32_t DCR;     // DMA Control Register
    volatile uint32_t DMAR;    // DMA Address for Burst Mode
} TIM_TypeDef;


//Peripheral Instants for Timers:
#define TIM1    ((TIM_TypeDef*) TIM1_BASE)
#define TIM2    ((TIM_TypeDef*) TIM2_BASE)
#define TIM3    ((TIM_TypeDef*) TIM3_BASE)
#define TIM4    ((TIM_TypeDef*) TIM4_BASE)

//-----------------------------
//Clock enable Macros for Timers
// Note: For STM32F103, TIM1 is on APB2 and TIM2-4 are on APB1.
#define RCC_TIM1_CLK_EN()   (RCC->APB2ENR |= (1 << 11))   // TIM1EN is bit 11 of APB2ENR
#define RCC_TIM2_CLK_EN()   (RCC->APB1ENR |= (1 << 0))    // TIM2EN is bit 0 of APB1ENR
#define RCC_TIM3_CLK_EN()   (RCC->APB1ENR |= (1 << 1))    // TIM3EN is bit 1 of APB1ENR
#define RCC_TIM4_CLK_EN()   (RCC->APB1ENR |= (1 << 2))    // TIM4EN is bit 2 of APB1ENR

#endif  /* INC_STM32F103X6_H_ */
