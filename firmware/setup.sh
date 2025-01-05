sudo apt update
sudo apt install gcc-arm-none-eabi openocd -y

mkdir drivers
cd drivers
# git clone https://github.com/ARM-software/CMSIS_5.git
# git clone https://github.com/STMicroelectronics/stm32f4xx_hal_driver.git
git clone --recursive https://github.com/STMicroelectronics/STM32CubeF4/
cd ..
