################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Stm32_F103C6_Drivers/USART/subdir.mk
-include Stm32_F103C6_Drivers/Timer/subdir.mk
-include Stm32_F103C6_Drivers/Speed/subdir.mk
-include Stm32_F103C6_Drivers/Rcc/subdir.mk
-include Stm32_F103C6_Drivers/ISR/subdir.mk
-include Stm32_F103C6_Drivers/GPIO/subdir.mk
-include Stm32_F103C6_Drivers/EXTI/subdir.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include HAL/Ultrasonic/subdir.mk
-include HAL/Motor/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
B_Drivers.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
B_Drivers.list \

OBJCOPY_HEX += \
B_Drivers.hex \

OBJCOPY_BIN += \
B_Drivers.bin \


# All Target
all: B_Drivers.elf secondary-outputs

# Tool invocations
B_Drivers.elf: $(OBJS) $(USER_OBJS) F:\4th_year\Second_Term\Grad_Proj\Stm32_WorkSpace\B_Drivers\STM32F103C8TX_FLASH.ld
	arm-none-eabi-gcc -o "B_Drivers.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"F:\4th_year\Second_Term\Grad_Proj\Stm32_WorkSpace\B_Drivers\STM32F103C8TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="B_Drivers.map" -Wl,--gc-sections -static -L"F:\4th_year\Second_Term\Grad_Proj\Stm32_WorkSpace\B_Drivers\Stm32_F103C6_Drivers" --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

B_Drivers.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "B_Drivers.list"
	@echo 'Finished building: $@'
	@echo ' '

B_Drivers.hex: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "B_Drivers.hex"
	@echo 'Finished building: $@'
	@echo ' '

B_Drivers.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "B_Drivers.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
