################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/SCSM11/Downloads/X-CUBE-TOF1/Drivers/BSP/53L8A1/53l8a1_ranging_sensor.c 

OBJS += \
./Drivers/BSP/53L8A1/53l8a1_ranging_sensor.o 

C_DEPS += \
./Drivers/BSP/53L8A1/53l8a1_ranging_sensor.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/53L8A1/53l8a1_ranging_sensor.o: C:/Users/SCSM11/Downloads/X-CUBE-TOF1/Drivers/BSP/53L8A1/53l8a1_ranging_sensor.c Drivers/BSP/53L8A1/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../../Inc -I"C:/Users/SCSM11/Downloads/X-CUBE-TOF1/Projects/NUCLEO-L476RG/Examples/53L8A1/53L8A1_SimpleRanging/STM32CubeIDE/Application/User" -I../../../../../../../Drivers/STM32L4xx_HAL_Driver/Inc -I../../../../../../../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../../../../../../../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../../../../../../../Drivers/CMSIS/Include -I../../../../../../../Drivers/BSP/Components/Common -I../../../../../../../Drivers/BSP/53L8A1 -I../../../../../../../Drivers/BSP/Components/vl53l8cx/modules -I../../../../../../../Drivers/BSP/Components/vl53l8cx/porting -I../../../../../../../Drivers/BSP/Components/vl53l8cx -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-53L8A1

clean-Drivers-2f-BSP-2f-53L8A1:
	-$(RM) ./Drivers/BSP/53L8A1/53l8a1_ranging_sensor.cyclo ./Drivers/BSP/53L8A1/53l8a1_ranging_sensor.d ./Drivers/BSP/53L8A1/53l8a1_ranging_sensor.o ./Drivers/BSP/53L8A1/53l8a1_ranging_sensor.su

.PHONY: clean-Drivers-2f-BSP-2f-53L8A1

