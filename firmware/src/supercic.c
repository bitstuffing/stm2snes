#include "supercic.h"

void SuperCIC_HoldReset(void)
{
    // Por ejemplo:
    // HAL_GPIO_WritePin(SUPERCIC_RESET_PORT, SUPERCIC_RESET_PIN, GPIO_PIN_RESET);
    // O mandar un byte a la PIC via SPI/UART/I2C, según tu protocolo
}

void SuperCIC_ReleaseReset(void)
{
    // HAL_GPIO_WritePin(SUPERCIC_RESET_PORT, SUPERCIC_RESET_PIN, GPIO_PIN_SET);
}
