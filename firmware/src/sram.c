#include "sram.h"
#include "gpio.h"
#include <stdint.h>

///////////////////////////////////////////////
// Adjust how many address bits you want
///////////////////////////////////////////////
#define NUM_ADDR_BITS 19  // A0..A18 = 19 bits, for 512KB of SRAM

// -- Private functions --
void HAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState){
    // TODO
}

// Small helper to pulse the SHIFT_CLK
static void pulseShiftClk(void)
{
    HAL_GPIO_WritePin(SHIFT_CLK_GPIO_Port, SHIFT_CLK_Pin, GPIO_PIN_SET);
    // Small pause (NOP or other)
    __NOP();
    HAL_GPIO_WritePin(SHIFT_CLK_GPIO_Port, SHIFT_CLK_Pin, GPIO_PIN_RESET);
    __NOP();
}

// Send the 19 bits (LSB first or MSB first, as you prefer, but be consistent!)
static void setAddress(uint32_t addr)
{
    // 1) SHIFT out the 19 bits to SER and SHIFT_CLK
    for (int i = 0; i < NUM_ADDR_BITS; i++) {
        uint8_t bit = (addr >> i) & 1; 
        // Set that bit in SER
        HAL_GPIO_WritePin(SER_GPIO_Port, SER_Pin, (bit) ? GPIO_PIN_SET : GPIO_PIN_RESET);

        // Pulse the SHIFT_CLK
        pulseShiftClk();
    }

    // 2) Pulse LATCH_CLK to "transfer" the register to the Q0..Q7 outputs of 74HC595
    HAL_GPIO_WritePin(LATCH_CLK_GPIO_Port, LATCH_CLK_Pin, GPIO_PIN_SET);
    __NOP();
    HAL_GPIO_WritePin(LATCH_CLK_GPIO_Port, LATCH_CLK_Pin, GPIO_PIN_RESET);
}

// Write a byte to the 'addr' address of the SRAM
static void writeByte(uint32_t addr, uint8_t data)
{
    // 1) Set the address
    setAddress(addr);

    // 2) Put the byte on D0..D7
    //    Assume D0..D7 are on PB0..PB7 (WATCH for conflicts!)
    //    Here we do a "clear" of the lower part and then OR with 'data'.
    GPIOB->ODR = (GPIOB->ODR & 0xFF00) | data;

    // 3) Pulse /WE low
    HAL_GPIO_WritePin(WE_GPIO_Port, WE_Pin, GPIO_PIN_RESET);
    __NOP();  // small wait
    HAL_GPIO_WritePin(WE_GPIO_Port, WE_Pin, GPIO_PIN_SET);
}

// -- Public functions --

void SRAM_BeginWrite(void)
{
    // 1) Force /CE = 0 if not controlled by /ROMSEL, to enable the SRAM
    HAL_GPIO_WritePin(CE_GPIO_Port, CE_Pin, GPIO_PIN_RESET);

    // 2) Set the transceiver direction to MCU->SRAM
    HAL_GPIO_WritePin(DIR_GPIO_Port, DIR_Pin, GPIO_PIN_SET); // if 1 = MCU->SRAM

    // 3) (Optional) Disable /OE if we don't need to read the SRAM
    HAL_GPIO_WritePin(OE_GPIO_Port, OE_Pin, GPIO_PIN_SET);
}

void SRAM_Write(const uint8_t *data, uint32_t length)
{
    for(uint32_t i = 0; i < length; i++) {
        writeByte(i, data[i]);
    }
}

void SRAM_EndWrite(void)
{
    // 1) If you want to return /CE to the "SNES control" state (by /ROMSEL),
    //    release it (set it high or something that disconnects the SRAM from your MCU).
    HAL_GPIO_WritePin(CE_GPIO_Port, CE_Pin, GPIO_PIN_SET);

    // 2) (Optional) Change DIR to "SNES->MCU" or "normal" 
    //    HAL_GPIO_WritePin(DIR_GPIO_Port, DIR_Pin, GPIO_PIN_RESET);

    // 3) (Optional) Leave /OE low if the SNES will use it.
    HAL_GPIO_WritePin(OE_GPIO_Port, OE_Pin, GPIO_PIN_RESET);
}
