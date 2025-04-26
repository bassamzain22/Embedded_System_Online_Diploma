################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/Ultrasonic/Ultrasonic_driver.c 

OBJS += \
./HAL/Ultrasonic/Ultrasonic_driver.o 

C_DEPS += \
./HAL/Ultrasonic/Ultrasonic_driver.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/Ultrasonic/Ultrasonic_driver.o: ../HAL/Ultrasonic/Ultrasonic_driver.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -c -I../Inc -I"F:/4th_year/Second_Term/Grad_Proj/Stm32_WorkSpace/B_Drivers/Stm32_F103C6_Drivers/Inc" -I"F:/4th_year/Second_Term/Grad_Proj/Stm32_WorkSpace/B_Drivers/HAL/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"HAL/Ultrasonic/Ultrasonic_driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

