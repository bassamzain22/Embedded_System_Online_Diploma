################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Stm32_F103C6_Drivers/EXTI/stm32_F103C6_EXTI_driver.c 

OBJS += \
./Stm32_F103C6_Drivers/EXTI/stm32_F103C6_EXTI_driver.o 

C_DEPS += \
./Stm32_F103C6_Drivers/EXTI/stm32_F103C6_EXTI_driver.d 


# Each subdirectory must supply rules for building sources it contributes
Stm32_F103C6_Drivers/EXTI/stm32_F103C6_EXTI_driver.o: ../Stm32_F103C6_Drivers/EXTI/stm32_F103C6_EXTI_driver.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -c -I../Inc -I"F:/4th_year/Second_Term/Grad_Proj/Stm32_WorkSpace/B_Drivers/Stm32_F103C6_Drivers/Inc" -I"F:/4th_year/Second_Term/Grad_Proj/Stm32_WorkSpace/B_Drivers/HAL/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Stm32_F103C6_Drivers/EXTI/stm32_F103C6_EXTI_driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

