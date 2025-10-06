################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application/User/ROI.c \
C:/Users/SCSM11/Downloads/X-CUBE-TOF1/Projects/NUCLEO-L476RG/Examples/53L8A1/53L8A1_SimpleRanging/Src/app_tof.c \
C:/Users/SCSM11/Downloads/X-CUBE-TOF1/Projects/NUCLEO-L476RG/Examples/53L8A1/53L8A1_SimpleRanging/Src/app_tof_pin_conf.c \
C:/Users/SCSM11/Downloads/X-CUBE-TOF1/Projects/NUCLEO-L476RG/Examples/53L8A1/53L8A1_SimpleRanging/Src/bsp.c \
C:/Users/SCSM11/Downloads/X-CUBE-TOF1/Projects/NUCLEO-L476RG/Examples/53L8A1/53L8A1_SimpleRanging/Src/gpio.c \
C:/Users/SCSM11/Downloads/X-CUBE-TOF1/Projects/NUCLEO-L476RG/Examples/53L8A1/53L8A1_SimpleRanging/Src/main.c \
../Application/User/oled_ssd1306.c \
../Application/User/serial_monitor.c \
C:/Users/SCSM11/Downloads/X-CUBE-TOF1/Projects/NUCLEO-L476RG/Examples/53L8A1/53L8A1_SimpleRanging/Src/stm32l4xx_hal_msp.c \
C:/Users/SCSM11/Downloads/X-CUBE-TOF1/Projects/NUCLEO-L476RG/Examples/53L8A1/53L8A1_SimpleRanging/Src/stm32l4xx_it.c \
C:/Users/SCSM11/Downloads/X-CUBE-TOF1/Projects/NUCLEO-L476RG/Examples/53L8A1/53L8A1_SimpleRanging/Src/stm32l4xx_nucleo.c \
C:/Users/SCSM11/Downloads/X-CUBE-TOF1/Projects/NUCLEO-L476RG/Examples/53L8A1/53L8A1_SimpleRanging/Src/stm32l4xx_nucleo_bus.c \
../Application/User/syscalls.c \
../Application/User/sysmem.c 

OBJS += \
./Application/User/ROI.o \
./Application/User/app_tof.o \
./Application/User/app_tof_pin_conf.o \
./Application/User/bsp.o \
./Application/User/gpio.o \
./Application/User/main.o \
./Application/User/oled_ssd1306.o \
./Application/User/serial_monitor.o \
./Application/User/stm32l4xx_hal_msp.o \
./Application/User/stm32l4xx_it.o \
./Application/User/stm32l4xx_nucleo.o \
./Application/User/stm32l4xx_nucleo_bus.o \
./Application/User/syscalls.o \
./Application/User/sysmem.o 

C_DEPS += \
./Application/User/ROI.d \
./Application/User/app_tof.d \
./Application/User/app_tof_pin_conf.d \
./Application/User/bsp.d \
./Application/User/gpio.d \
./Application/User/main.d \
./Application/User/oled_ssd1306.d \
./Application/User/serial_monitor.d \
./Application/User/stm32l4xx_hal_msp.d \
./Application/User/stm32l4xx_it.d \
./Application/User/stm32l4xx_nucleo.d \
./Application/User/stm32l4xx_nucleo_bus.d \
./Application/User/syscalls.d \
./Application/User/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Application/User/%.o Application/User/%.su Application/User/%.cyclo: ../Application/User/%.c Application/User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../../Inc -I"C:/Users/SCSM11/Downloads/X-CUBE-TOF1/Projects/NUCLEO-L476RG/Examples/53L8A1/53L8A1_SimpleRanging/STM32CubeIDE/Application/User" -I../../../../../../../Drivers/STM32L4xx_HAL_Driver/Inc -I../../../../../../../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../../../../../../../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../../../../../../../Drivers/CMSIS/Include -I../../../../../../../Drivers/BSP/Components/Common -I../../../../../../../Drivers/BSP/53L8A1 -I../../../../../../../Drivers/BSP/Components/vl53l8cx/modules -I../../../../../../../Drivers/BSP/Components/vl53l8cx/porting -I../../../../../../../Drivers/BSP/Components/vl53l8cx -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/app_tof.o: C:/Users/SCSM11/Downloads/X-CUBE-TOF1/Projects/NUCLEO-L476RG/Examples/53L8A1/53L8A1_SimpleRanging/Src/app_tof.c Application/User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../../Inc -I"C:/Users/SCSM11/Downloads/X-CUBE-TOF1/Projects/NUCLEO-L476RG/Examples/53L8A1/53L8A1_SimpleRanging/STM32CubeIDE/Application/User" -I../../../../../../../Drivers/STM32L4xx_HAL_Driver/Inc -I../../../../../../../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../../../../../../../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../../../../../../../Drivers/CMSIS/Include -I../../../../../../../Drivers/BSP/Components/Common -I../../../../../../../Drivers/BSP/53L8A1 -I../../../../../../../Drivers/BSP/Components/vl53l8cx/modules -I../../../../../../../Drivers/BSP/Components/vl53l8cx/porting -I../../../../../../../Drivers/BSP/Components/vl53l8cx -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/app_tof_pin_conf.o: C:/Users/SCSM11/Downloads/X-CUBE-TOF1/Projects/NUCLEO-L476RG/Examples/53L8A1/53L8A1_SimpleRanging/Src/app_tof_pin_conf.c Application/User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../../Inc -I"C:/Users/SCSM11/Downloads/X-CUBE-TOF1/Projects/NUCLEO-L476RG/Examples/53L8A1/53L8A1_SimpleRanging/STM32CubeIDE/Application/User" -I../../../../../../../Drivers/STM32L4xx_HAL_Driver/Inc -I../../../../../../../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../../../../../../../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../../../../../../../Drivers/CMSIS/Include -I../../../../../../../Drivers/BSP/Components/Common -I../../../../../../../Drivers/BSP/53L8A1 -I../../../../../../../Drivers/BSP/Components/vl53l8cx/modules -I../../../../../../../Drivers/BSP/Components/vl53l8cx/porting -I../../../../../../../Drivers/BSP/Components/vl53l8cx -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/bsp.o: C:/Users/SCSM11/Downloads/X-CUBE-TOF1/Projects/NUCLEO-L476RG/Examples/53L8A1/53L8A1_SimpleRanging/Src/bsp.c Application/User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../../Inc -I"C:/Users/SCSM11/Downloads/X-CUBE-TOF1/Projects/NUCLEO-L476RG/Examples/53L8A1/53L8A1_SimpleRanging/STM32CubeIDE/Application/User" -I../../../../../../../Drivers/STM32L4xx_HAL_Driver/Inc -I../../../../../../../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../../../../../../../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../../../../../../../Drivers/CMSIS/Include -I../../../../../../../Drivers/BSP/Components/Common -I../../../../../../../Drivers/BSP/53L8A1 -I../../../../../../../Drivers/BSP/Components/vl53l8cx/modules -I../../../../../../../Drivers/BSP/Components/vl53l8cx/porting -I../../../../../../../Drivers/BSP/Components/vl53l8cx -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/gpio.o: C:/Users/SCSM11/Downloads/X-CUBE-TOF1/Projects/NUCLEO-L476RG/Examples/53L8A1/53L8A1_SimpleRanging/Src/gpio.c Application/User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../../Inc -I"C:/Users/SCSM11/Downloads/X-CUBE-TOF1/Projects/NUCLEO-L476RG/Examples/53L8A1/53L8A1_SimpleRanging/STM32CubeIDE/Application/User" -I../../../../../../../Drivers/STM32L4xx_HAL_Driver/Inc -I../../../../../../../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../../../../../../../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../../../../../../../Drivers/CMSIS/Include -I../../../../../../../Drivers/BSP/Components/Common -I../../../../../../../Drivers/BSP/53L8A1 -I../../../../../../../Drivers/BSP/Components/vl53l8cx/modules -I../../../../../../../Drivers/BSP/Components/vl53l8cx/porting -I../../../../../../../Drivers/BSP/Components/vl53l8cx -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/main.o: C:/Users/SCSM11/Downloads/X-CUBE-TOF1/Projects/NUCLEO-L476RG/Examples/53L8A1/53L8A1_SimpleRanging/Src/main.c Application/User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../../Inc -I"C:/Users/SCSM11/Downloads/X-CUBE-TOF1/Projects/NUCLEO-L476RG/Examples/53L8A1/53L8A1_SimpleRanging/STM32CubeIDE/Application/User" -I../../../../../../../Drivers/STM32L4xx_HAL_Driver/Inc -I../../../../../../../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../../../../../../../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../../../../../../../Drivers/CMSIS/Include -I../../../../../../../Drivers/BSP/Components/Common -I../../../../../../../Drivers/BSP/53L8A1 -I../../../../../../../Drivers/BSP/Components/vl53l8cx/modules -I../../../../../../../Drivers/BSP/Components/vl53l8cx/porting -I../../../../../../../Drivers/BSP/Components/vl53l8cx -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/stm32l4xx_hal_msp.o: C:/Users/SCSM11/Downloads/X-CUBE-TOF1/Projects/NUCLEO-L476RG/Examples/53L8A1/53L8A1_SimpleRanging/Src/stm32l4xx_hal_msp.c Application/User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../../Inc -I"C:/Users/SCSM11/Downloads/X-CUBE-TOF1/Projects/NUCLEO-L476RG/Examples/53L8A1/53L8A1_SimpleRanging/STM32CubeIDE/Application/User" -I../../../../../../../Drivers/STM32L4xx_HAL_Driver/Inc -I../../../../../../../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../../../../../../../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../../../../../../../Drivers/CMSIS/Include -I../../../../../../../Drivers/BSP/Components/Common -I../../../../../../../Drivers/BSP/53L8A1 -I../../../../../../../Drivers/BSP/Components/vl53l8cx/modules -I../../../../../../../Drivers/BSP/Components/vl53l8cx/porting -I../../../../../../../Drivers/BSP/Components/vl53l8cx -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/stm32l4xx_it.o: C:/Users/SCSM11/Downloads/X-CUBE-TOF1/Projects/NUCLEO-L476RG/Examples/53L8A1/53L8A1_SimpleRanging/Src/stm32l4xx_it.c Application/User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../../Inc -I"C:/Users/SCSM11/Downloads/X-CUBE-TOF1/Projects/NUCLEO-L476RG/Examples/53L8A1/53L8A1_SimpleRanging/STM32CubeIDE/Application/User" -I../../../../../../../Drivers/STM32L4xx_HAL_Driver/Inc -I../../../../../../../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../../../../../../../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../../../../../../../Drivers/CMSIS/Include -I../../../../../../../Drivers/BSP/Components/Common -I../../../../../../../Drivers/BSP/53L8A1 -I../../../../../../../Drivers/BSP/Components/vl53l8cx/modules -I../../../../../../../Drivers/BSP/Components/vl53l8cx/porting -I../../../../../../../Drivers/BSP/Components/vl53l8cx -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/stm32l4xx_nucleo.o: C:/Users/SCSM11/Downloads/X-CUBE-TOF1/Projects/NUCLEO-L476RG/Examples/53L8A1/53L8A1_SimpleRanging/Src/stm32l4xx_nucleo.c Application/User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../../Inc -I"C:/Users/SCSM11/Downloads/X-CUBE-TOF1/Projects/NUCLEO-L476RG/Examples/53L8A1/53L8A1_SimpleRanging/STM32CubeIDE/Application/User" -I../../../../../../../Drivers/STM32L4xx_HAL_Driver/Inc -I../../../../../../../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../../../../../../../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../../../../../../../Drivers/CMSIS/Include -I../../../../../../../Drivers/BSP/Components/Common -I../../../../../../../Drivers/BSP/53L8A1 -I../../../../../../../Drivers/BSP/Components/vl53l8cx/modules -I../../../../../../../Drivers/BSP/Components/vl53l8cx/porting -I../../../../../../../Drivers/BSP/Components/vl53l8cx -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/stm32l4xx_nucleo_bus.o: C:/Users/SCSM11/Downloads/X-CUBE-TOF1/Projects/NUCLEO-L476RG/Examples/53L8A1/53L8A1_SimpleRanging/Src/stm32l4xx_nucleo_bus.c Application/User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../../Inc -I"C:/Users/SCSM11/Downloads/X-CUBE-TOF1/Projects/NUCLEO-L476RG/Examples/53L8A1/53L8A1_SimpleRanging/STM32CubeIDE/Application/User" -I../../../../../../../Drivers/STM32L4xx_HAL_Driver/Inc -I../../../../../../../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../../../../../../../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../../../../../../../Drivers/CMSIS/Include -I../../../../../../../Drivers/BSP/Components/Common -I../../../../../../../Drivers/BSP/53L8A1 -I../../../../../../../Drivers/BSP/Components/vl53l8cx/modules -I../../../../../../../Drivers/BSP/Components/vl53l8cx/porting -I../../../../../../../Drivers/BSP/Components/vl53l8cx -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Application-2f-User

clean-Application-2f-User:
	-$(RM) ./Application/User/ROI.cyclo ./Application/User/ROI.d ./Application/User/ROI.o ./Application/User/ROI.su ./Application/User/app_tof.cyclo ./Application/User/app_tof.d ./Application/User/app_tof.o ./Application/User/app_tof.su ./Application/User/app_tof_pin_conf.cyclo ./Application/User/app_tof_pin_conf.d ./Application/User/app_tof_pin_conf.o ./Application/User/app_tof_pin_conf.su ./Application/User/bsp.cyclo ./Application/User/bsp.d ./Application/User/bsp.o ./Application/User/bsp.su ./Application/User/gpio.cyclo ./Application/User/gpio.d ./Application/User/gpio.o ./Application/User/gpio.su ./Application/User/main.cyclo ./Application/User/main.d ./Application/User/main.o ./Application/User/main.su ./Application/User/oled_ssd1306.cyclo ./Application/User/oled_ssd1306.d ./Application/User/oled_ssd1306.o ./Application/User/oled_ssd1306.su ./Application/User/serial_monitor.cyclo ./Application/User/serial_monitor.d ./Application/User/serial_monitor.o ./Application/User/serial_monitor.su ./Application/User/stm32l4xx_hal_msp.cyclo ./Application/User/stm32l4xx_hal_msp.d ./Application/User/stm32l4xx_hal_msp.o ./Application/User/stm32l4xx_hal_msp.su ./Application/User/stm32l4xx_it.cyclo ./Application/User/stm32l4xx_it.d ./Application/User/stm32l4xx_it.o ./Application/User/stm32l4xx_it.su ./Application/User/stm32l4xx_nucleo.cyclo ./Application/User/stm32l4xx_nucleo.d ./Application/User/stm32l4xx_nucleo.o ./Application/User/stm32l4xx_nucleo.su ./Application/User/stm32l4xx_nucleo_bus.cyclo ./Application/User/stm32l4xx_nucleo_bus.d ./Application/User/stm32l4xx_nucleo_bus.o ./Application/User/stm32l4xx_nucleo_bus.su ./Application/User/syscalls.cyclo ./Application/User/syscalls.d ./Application/User/syscalls.o ./Application/User/syscalls.su ./Application/User/sysmem.cyclo ./Application/User/sysmem.d ./Application/User/sysmem.o ./Application/User/sysmem.su

.PHONY: clean-Application-2f-User

