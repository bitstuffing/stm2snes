#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>
#define STM32F407xx 1
#include "stm32f4xx_hal_gpio.h" 

// --- Pins for the 74HC595 that generate A0..A18 ---
#define SHIFT_CLK_GPIO_Port   GPIOB
#define SHIFT_CLK_Pin         GPIO_PIN_0

#define LATCH_CLK_GPIO_Port   GPIOB
#define LATCH_CLK_Pin         GPIO_PIN_1

#define SER_GPIO_Port         GPIOB
#define SER_Pin               GPIO_PIN_2

// --- SRAM control pins ---
#define WE_GPIO_Port          GPIOA
#define WE_Pin                GPIO_PIN_0

#define CE_GPIO_Port          GPIOA
#define CE_Pin                GPIO_PIN_1

#define OE_GPIO_Port          GPIOA
#define OE_Pin                GPIO_PIN_2

// --- Transceiver direction (74HCT245) ---
#define DIR_GPIO_Port         GPIOA
#define DIR_Pin               GPIO_PIN_3

// --- Data on PB0..PB7 (this conflicts with SHIFT_CLK on PB0, be careful in the real design):
//   * This is just an example. It should be separated, the pins in the actual schematic!
//   * Let's assume that in reality the data D0..D7 are on GPIOB PINs 8..15, etc.

#endif
