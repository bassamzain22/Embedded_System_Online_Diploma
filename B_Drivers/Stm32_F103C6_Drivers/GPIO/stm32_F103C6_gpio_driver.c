/*
 * stm32f103x8_gpio_driver.c
 *
 *  Created on: Oct 8, 2024
 *      Author: Mohamed Abd El Hakeem El Said Ali
 */


#include <stm32_F103C6_gpio_driver.h>



/*
 * ===============================================
 * APIs Supported by "MCAL GPIO DRIVER"
 * ===============================================
 **/

/**================================================================
 * @Fn-MCAL_GPIO_Enable_ClocK
 * @brief -This Func is responsible for enabling clock of the peripheral and you can work successfully
 * @param [in] - Pointer of GPIOx
 * @retval -Not
 * Note-.....
 */

void MCAL_GPIO_Enable_ClocK(GPIO_TypedDef* GPIOx)
{
	if(  GPIOx ==  GPIOA)
	{
		GPIOA_CLOCK_ENABLE;
	}
	else if(GPIOx ==  GPIOB)
	{
		GPIOB_CLOCK_ENABLE;
	}
	else if(GPIOx ==  GPIOC)
	{
		GPIOC_CLOCK_ENABLE;
	}
	else if(GPIOx ==  GPIOD)
	{
		GPIOD_CLOCK_ENABLE;
	}
	else
	{
		//DoNothing
	}
}



/**================================================================
 * @Fn-MCAL_GPIO_Diable_ClocK
 * @brief -This Func is responsible for disabling clock of the peripheral.
 * @param [in] - Pointer of GPIOx
 * @retval -Not
 * Note-.....
 */

void MCAL_GPIO_Diable_ClocK(GPIO_TypedDef* GPIOx)
{
	if(  GPIOx ==  GPIOA)
	{
		GPIOA_CLOCK_DISABLE;
	}
	else if(GPIOx ==  GPIOB)
	{
		GPIOB_CLOCK_DISABLE;
	}
	else if(GPIOx ==  GPIOC)
	{
		GPIOC_CLOCK_DISABLE;
	}
	else if(GPIOx ==  GPIOD)
	{
		GPIOD_CLOCK_DISABLE;
	}
	else
	{
		//DoNothing
	}
}





/**================================================================
 * @Fn-Get_Pos_CRLH
 * @param [in] - PinNumber >>>>>> based on @ref GPIO_PINS_Define in header of gpio
 * @retval -Suitable Pos for Config_Register [uint8_t]
 * */

uint8_t Get_Pos_CRLH(uint16_t PinNumber)
{
	switch(PinNumber)
	{
	case GPIO_PIN_0:
		return 0;
		break;
	case GPIO_PIN_1:
		return 4;
		break;
	case GPIO_PIN_2:
		return 8;
		break;
	case GPIO_PIN_3:
		return 12;
		break;
	case GPIO_PIN_4:
		return 16;
		break;
	case GPIO_PIN_5:
		return 20;
		break;
	case GPIO_PIN_6:
		return 24;
		break;
	case GPIO_PIN_7:
		return 28;
		break;
	case GPIO_PIN_8:
		return 0;
		break;
	case GPIO_PIN_9 :
		return 4;
		break;
	case GPIO_PIN_10:
		return 8;
		break;
	case GPIO_PIN_11:
		return 12;
		break;
	case GPIO_PIN_12:
		return 16;
		break;
	case GPIO_PIN_13:
		return 20;
		break;
	case GPIO_PIN_14:
		return 24;
		break;
	case GPIO_PIN_15:
		return 28;
		break;

	default:
		return 0;


	}

}

/**================================================================
 * @Fn-MCAL_GPIO_Init
 * @brief -In this Func, You can Initialize All Configuration  of any PinNumber
 * @param [in] - Pointer of GPIOx ,
 * @param [in] -Address of the PinConfig------->>>>(as &PinConfig..)
 * @retval -Not
 * Note-You must Create Instant from "GPIO_PinConfig_t" Structure,
 * Before using This func "MCAL_GPIO_Init" and pass it to @param [in] -Address of the PinConfig
 */

void MCAL_GPIO_Init(GPIO_TypedDef* GPIOx, GPIO_PinConfig_t* PinConfig )
{

	volatile uint32_t* Reg_Config= NULL;

	Reg_Config = (PinConfig->GPIO_PinNumber < GPIO_PIN_8) ?  &(GPIOx->CRL):  &(GPIOx->CRH) ;
	*Reg_Config &= ~(0xF << Get_Pos_CRLH(PinConfig->GPIO_PinNumber) );


	if(PinConfig->GPIO_Mode == GPIO_Mode_Out_push_pull ||  PinConfig->GPIO_Mode == GPIO_Mode_Out_Open_drain ||
			PinConfig->GPIO_Mode == GPIO_Mode_Out_AF_push_pull ||  PinConfig->GPIO_Mode == GPIO_Mode_Out_AF_Open_drain )
	{
		*Reg_Config |= (((((PinConfig->GPIO_Mode - 4) << 2) |(PinConfig->GPIO_Speed)) & (0x0F)) << Get_Pos_CRLH(PinConfig->GPIO_PinNumber));
	}

	else
	{
		//In case Of the "Input with pull-up / pull-down"
		// Input Pull Up   >>>>>>>>>>>>> set   ODR [Selected PinNumber]
		// Input Pull Down >>>>>>>>>>>>> clear ODR [Selected PinNumber]
		if(PinConfig->GPIO_Mode == GPIO_Mode_Inp_pull_up )
		{
			GPIOx->ODR |= PinConfig->GPIO_PinNumber;
			*Reg_Config |= (((((PinConfig->GPIO_Mode) << 2) |(PinConfig->GPIO_Speed)) & (0x0F)) << Get_Pos_CRLH(PinConfig->GPIO_PinNumber));

		}
		else if (PinConfig->GPIO_Mode == GPIO_Mode_Inp_pull_down)
		{
			GPIOx->ODR &= ~(PinConfig->GPIO_PinNumber) ;
			*Reg_Config |= (((((PinConfig->GPIO_Mode - 1) << 2) |(PinConfig->GPIO_Speed)) & (0x0F)) << Get_Pos_CRLH(PinConfig->GPIO_PinNumber));


		}
		else
		{
			*Reg_Config |= (((((PinConfig->GPIO_Mode) << 2) |(PinConfig->GPIO_Speed)) & (0x0F)) << Get_Pos_CRLH(PinConfig->GPIO_PinNumber));

		}

	}

}


/**================================================================
 * @Fn-MCAL_GPIO_DInit
 * @brief -In This Func, You can Reset All Configuration  of The Selected Portx
 * @param [in] - Pointer of GPIOx ,
 * @retval -Not
 * Note-..........................................................
 */
void MCAL_GPIO_DInit(GPIO_TypedDef* GPIOx)
{
	//There are Reset Controller In Stm32f103X8, so ........
	if(     GPIOx ==  GPIOA)
	{
		RCC->APB2RSTR |=  (1 << 2)  ;
		RCC->APB2RSTR &= ~(1 << 2)  ;

	}
	else if(GPIOx ==  GPIOB)
	{
		RCC->APB2RSTR |=  (1 << 3)  ;
		RCC->APB2RSTR &= ~(1 << 3)  ;
	}
	else if(GPIOx ==  GPIOC)
	{
		RCC->APB2RSTR |=  (1 << 4)  ;
		RCC->APB2RSTR &= ~(1 << 4)  ;
	}
	else if(GPIOx ==  GPIOD)
	{
		RCC->APB2RSTR |= (1 << 5)  ;
		RCC->APB2RSTR &= ~(1 << 5)  ;
	}
	else
	{
		//DoNothing
	}
}




/**================================================================
 * @Fn-MCAL_GPIO_ReadPin
 * @brief -In This Func, You can Read state  of The Selected pin
 * @param [in] - Pointer of GPIOx ,
 * @param [in] - PinNumber >>>>>> based on @ref GPIO_PINS_Define in header of gpio,
 * @retval -State of Pin, 0 or 1
 * Note-..........................................................
 */
uint8_t  MCAL_GPIO_ReadPin(GPIO_TypedDef* GPIOx,uint16_t PinNumber )
{
	if((GPIOx->IDR & PinNumber) != (uint32_t)GPIO_PIN_RESET) return (uint8_t)GPIO_PIN_SET;
	else return (uint8_t)GPIO_PIN_RESET;

}


/**================================================================
 * @Fn-MCAL_GPIO_ReadPort
 * @brief -In This Func, You can Read All Portx
 * @param [in] - Pointer of GPIOx ,
 * @retval -16bits of selected port.
 * Note-..........................................................
 */
uint16_t MCAL_GPIO_ReadPort(GPIO_TypedDef* GPIOx)
{
	return (uint16_t)(GPIOx->IDR);
}



/**================================================================
 * @Fn-MCAL_GPIO_WritePin
 * @brief -In This Func, You can Write in any PinNumber of the selected port
 * @param [in] - Pointer of GPIOx ,
 * @param [in] - PinNumber >>>>>> based on @ref GPIO_PINS_Define in header of gpio,
 * @param [in] - Set "Value" which is 0 or 1,
 * @retval -NOT......
 * Note-..........................................................
 */
void MCAL_GPIO_WritePin(GPIO_TypedDef* GPIOx,uint16_t PinNumber , uint8_t Value)
{

	if(Value == (uint8_t) GPIO_PIN_SET)
	{
		//Bits 15:0 BSy: Port x Set bit y (y= 0 .. 15), you do not need any or "|" with Atomic Bit Register BSRR
		GPIOx->BSRR = (uint32_t)PinNumber;
	}

	else
	{
		//Bits 31:16 BRy: Port x Reset bit y (y= 0 .. 15),  you do not need any or "|" with Atomic Bit Register BSRR
		GPIOx->BSRR = (uint32_t)(PinNumber << 16);
	}
}



/**================================================================
 * @Fn-MCAL_GPIO_WritePort
 * @brief -In This Func, You can write All The Selected Portx.
 * @param [in] - Pointer of GPIOx ,
 * @param [in] - Value ,
 * @retval -Not
 * Note-..........................................................
 */
void MCAL_GPIO_WritePort(GPIO_TypedDef* GPIOx, uint16_t Value)
{

	GPIOx->ODR = (uint32_t)Value;


}



/**================================================================
 * @Fn-MCAL_GPIO_TogglePin
 * @brief -In This Func, You can Toggle the selected pin of the port.
 * @param [in] - Pointer of GPIOx ,
 * @param [in] - PinNumber >>>>>> based on @ref GPIO_PINS_Define in header of gpio,
 * @retval -Not
 * Note-..........................................................
 */
void MCAL_GPIO_TogglePin(GPIO_TypedDef* GPIOx,uint16_t PinNumber)
{
	GPIOx->ODR ^= (uint32_t)PinNumber;
}



/**================================================================
 * @Fn-MCAL_GPIO_LockPin
 * @brief -In This Func, you can lock the configuration of the register .
 * @param [in] - Pointer of GPIOx ,
 * @param [in] - PinNumber >>>>>> based on @ref GPIO_PINS_Define in header of gpio,
 * @retval -Not
 * Note-..........................................................
 */
uint8_t MCAL_GPIO_LockPin(GPIO_TypedDef* GPIOx,uint16_t PinNumber)
{

	/*This register is used to lock the configuration of the port bits when a correct write sequence
	is applied to bit 16 (LCKK). The value of bits [15:0] is used to lock the configuration of the
	GPIO. During the write sequence, the value of LCKR[15:0] must not change. When the
	LOCK sequence has been applied on a port bit it is no longer possible to modify the value of
	the port bit until the next reset.*/

	/*Bit 16 LCKK[16]: Lock key
	This bit can be read anytime. It can only be modified using the Lock Key Writing Sequence.
	0: Port configuration lock key not active
	1: Port configuration lock key active. GPIOx_LCKR register is locked until the next reset.
	LOCK key writing sequence:
	Write 1
	Write 0
	Write 1
	Read 0
	Read 1 (this read is optional but confirms that the lock is active)*/

	volatile uint32_t temp = (1 << 16) ;
	temp |= PinNumber ;

	//	Write 1
	GPIOx->LCKR = temp ;
	//	Write 0
	GPIOx->LCKR =  PinNumber ;
	//	Write 1
	GPIOx->LCKR = temp ;

	//Read 0
	temp = (GPIOx->LCKR & (1 << 16) );

	if(temp == 0)
	{
		//Read 1
		temp =(GPIOx->LCKR & (1 << 16) );
		if(temp !=0) return (uint8_t)(GPIO_PIN_LOCK_ENABLED);
		else return (uint8_t)(GPIO_PIN_LOCK_FAILED);
	}
	else return (uint8_t)(GPIO_PIN_LOCK_FAILED);
}
//************************************************************************By bassamzain***********************************************//
uint8_t getposition(uint16_t pin_num){
	uint8_t rval;
	if(pin_num == pin0){
		rval =0;
	}
	if(pin_num == pin1){
		rval =4;
	}
	if(pin_num == pin2){
		rval =8;
	}
	if(pin_num == pin3){
		rval =12;
	}
	if(pin_num == pin4){
		rval =16;
	}
	if(pin_num == pin5){
		rval =20;
	}
	if(pin_num == pin6){
		rval =24;
	}
	if(pin_num == pin7){
		rval =28;
	}
	if(pin_num == pin8){
		rval =0;
	}
	if(pin_num == pin9){
		rval =4;
	}
	if(pin_num == pin10){
		rval =8;
	}
	if(pin_num == pin11){
		rval =12;
	}
	if(pin_num == pin12){
		rval =16;
	}
	if(pin_num == pin13){
		rval =20;
	}
	if(pin_num == pin14){
		rval =24;
	}
	if(pin_num == pin15){
		rval =28;
	}
	return rval;


}
//**================================================================
//* @Fn- pinmode
// * @brief - Initialize a specified GPIO port with specified configurations modes
// * @param [in] - GPIOx: where x can be (A...E Depending on device used) to select the GPIO Peripheral
// * @param [in] - pin: pin name
// * @param [in] - pinmode:mode of the pin
// * @retval -none
// * Note-
void pinmode(GPIO_TypedDef* GPIOx,uint16_t pin,uint32_t pinmode){
	if(GPIOx==GPIOA){
		GPIOA_CLOCK_ENABLE;

	}
	else if(GPIOx==GPIOB){
		GPIOB_CLOCK_ENABLE;

	}
	else{
		GPIOC_CLOCK_ENABLE;
	}

	if(pin<8){
		GPIOx->CRL &=~(0xf<<(getposition(pin)));

		if((pinmode==GPIO_MODE_INPUT_PD)||(pinmode==GPIO_MODE_INPUT_PU)){
			if(pinmode == GPIO_MODE_INPUT_PU){
				GPIOx->CRL |=(0b1000<<(getposition(pin)));
				GPIOx->ODR |= (1<<pin);
			}
			else{
				GPIOx->CRL |=(0b1000<<(getposition(pin)));
				GPIOx->ODR &=~(1<<pin);
			}

		}
		else GPIOx->CRL |=(pinmode<<(getposition(pin)));

	}
	else if(pin>7){
		//GPIOx->GPIOx_CRH
		GPIOx->CRH &=~(0xf<<(getposition(pin)));

		if((pinmode==GPIO_MODE_INPUT_PD)||(pinmode==GPIO_MODE_INPUT_PU)){
			if(pinmode == GPIO_MODE_INPUT_PU){
				GPIOx->CRH |=(0b1000<<(getposition(pin)));
				GPIOx->ODR |= (1<<pin);
			}
			else{
				GPIOx->CRH |=(0b1000<<(getposition(pin)));
				GPIOx->ODR &=~(1<<pin);
			}

		}
		else GPIOx->CRH |=(pinmode<<(getposition(pin)));

	}



}


/**================================================================
 * @Fn- pinwrite
 * @brief - Write the GPIOx PINy according to specified parameters in Pin_config
 * @param [in] - GPIOx: where x can be (A...E Depending on device used) to select the GPIO Peripheral
 * @param [in] - pin: GPIOx PIN Number
 * @param [in] - status: The desired value to write
 * @retval - None
 * Note-
 */
void pinwrite(GPIO_TypedDef* GPIOx,uint16_t pin,uint8_t status){
	if(status!=0){
		GPIOx->ODR |=(1<<pin);
	}
	else GPIOx->ODR &=~(1<<pin);

}


/**================================================================
 * @Fn- WRITE_PORT
 * @brief - Write the GPIOx according to specified parameters in Pin_config
 * @param [in] - GPIOx: where x can be (A...E Depending on device used) to select the GPIO Peripheral
 * @param [in] - value: The desired value to write
 * @retval -
 * Note-
 */
void WRITE_PORT(GPIO_TypedDef* GPIOx,uint16_t status){
	GPIOx->ODR = (uint16_t)status;

}

/**================================================================
 * @Fn- set_valio_PORT
 * @brief - Write the GPIOx according to specified parameters in Pin_config
 * @param [in] - GPIOx: where x can be (A...E Depending on device used) to select the GPIO Peripheral
 * @param [in] - value: The desired value to write
 * @param [in] - position:position of seting Values
 * @retval -
 * Note-
 */

void set_Value_PORT(GPIO_TypedDef* GPIOx,uint16_t status,uint16_t position){

	GPIOx->ODR |=(status<<position);
}

/**================================================================
 * @Fn- set_valio_PORT
 * @brief - Write the GPIOx according to specified parameters in Pin_config
 * @param [in] - GPIOx: where x can be (A...E Depending on device used) to select the GPIO Peripheral
 * @param [in] - value: The desired value to write
 * @param [in] - position:position of seting Values
 * @retval -
 * Note-
 */

void res_Value_PORT(GPIO_TypedDef* GPIOx,uint16_t status,uint16_t position){

	GPIOx->ODR &=~(status<<position);
}
/**================================================================
 * @Fn              - READ_PIN
 * @brief           - Read the GPIOx PINy according to specified parameters in Pin_config
 * @param [in]      - GPIOx: where x can be (A...E Depending on device used) to select the GPIO Peripheral
 * @param [in]      - Pin: GPIOx PIN Number
 * @retval          - uint8_t
 * Note             - none
 */

uint8_t READ_PIN(GPIO_TypedDef* GPIOx, uint16_t pin){
	return (GPIOx->IDR>>pin)&1;
}

/**================================================================
 * @Fn              - READ_PORT
 * @brief           - Read the GPIOx _PORT according to specified parameters in Pin_config
 * @param [in]      - GPIOx:  GPIO Peripheral

 * @retval          - uint16_t
 * Note             - none
 */
uint16_t READ_PORT(GPIO_TypedDef* GPIOx){

	return GPIOx->IDR;
}

