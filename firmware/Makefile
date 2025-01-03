TARGET = cartfw

OBJS =  src/main.o src/sram.o src/sdcard.o src/supercic.o 

OBJS += drivers/STM32CubeF4/Middlewares/Third_Party/FatFs/src/ff.o \
		drivers/STM32CubeF4/Middlewares/Third_Party/FatFs/src/diskio.o \
		drivers/STM32CubeF4/Middlewares/Third_Party/FatFs/src/ff_gen_drv.o \
		# src/stm32f4xx_hal_msp.o \
		# src/stm32f4xx_hal_timebase_tim.o \
        # drivers/STM32CubeF4/Middlewares/Third_Party/FatFs/src/option/ccsbcs.o \
		# startup/startup_stm32f407vgtx.o

# OBJS += drivers/STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal.h \
		# drivers/STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.o \
		# drivers/STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.h \
		# drivers/STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.h \
		# drivers/STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.h \
		# drivers/STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.h \

		
CC = arm-none-eabi-gcc
CFLAGS = -O2 -mcpu=cortex-m4 -mthumb -Isrc \
		 -Idrivers/STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Inc \
		 -Idrivers/STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy \
		 -Idrivers/STM32CubeF4/Drivers/CMSIS/Device/ST/STM32F4xx/Include \
		 -Idrivers/STM32CubeF4/Drivers/CMSIS/Include \
		 -Idrivers/STM32CubeF4/Drivers/CMSIS/Core/Include \
		 -Idrivers/STM32CubeF4/Middlewares/ST/STM32_USB_Host_Library/Core/Inc/ \
		 -Idrivers/STM32CubeF4/Middlewares/Third_Party/FatFs/src/drivers/ \
		 -Idrivers/STM32CubeF4/Middlewares/Third_Party/FatFs/src \
		 -Idrivers/STM32CubeF4/Projects/STM32F4-Discovery/Applications/FatFs/FatFs_USBDisk/Inc \
		#  -Idrivers/STM32CubeF4/Drivers/CMSIS/Device/ST/STM32F4xx/Include/ \
		#  -Idrivers/CMSIS_5/Device/ST/STM32F4xx/Include \
        #  -Idrivers/CMSIS_5/CMSIS/Core/Include \
        #  -Idrivers/stm32f4xx_hal_driver/Inc \
        #  -Idrivers/stm32f4xx_hal_driver/Inc/Legacy \

LDFLAGS = -Tdrivers/STM32CubeF4/Projects/STM32F4-Discovery/Templates_LL/STM32CubeIDE/STM32F407VGTX_FLASH.ld -lc -lm -lnosys

all: $(TARGET).bin
	
$(TARGET).elf: $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)
	arm-none-eabi-size $@



%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET).bin: $(TARGET).elf
	arm-none-eabi-objcopy -O binary $< $@

clean:
	rm -f $(OBJS) $(TARGET).elf $(TARGET).bin

flash: $(TARGET).bin
	openocd -f interface/stlink.cfg -f target/stm32f4x.cfg \
	        -c "program $(TARGET).bin verify reset exit"

.PHONY: all clean flash
