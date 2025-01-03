#include <main.h>

/**
 * TODO: check this reference
 */
int main(void)
{
    // 1. Basic initialization of the STM32
    HAL_Init();
    SystemClock_Config();   

    // 2. Initialize GPIOs, etc.
    MX_GPIO_Init();         
    MX_DMA_Init();          // If you are going to use DMA
    MX_FSMC_Init();         // If you have an FSMC for SRAM (in STM32F1/F4/F7 chips)
    // TODO: include if necessary the init for pins that control the 74HC595 / 74HCT245

    // 3. Initialize the SD Card (SPI/SDIO + FatFS, etc.)
    if (!SDCARD_Init()) {
        // Handle error: could not mount the SD, etc.
    }

    // 4. Read the .sfc file from the SD
    //    (e.g. "menu.sfc")
    uint8_t *romBuffer = malloc(MAX_ROM_SIZE);
    if (romBuffer == NULL) {
        // Handle memory error
    }

    uint32_t romSize = SDCARD_ReadFile("menu.sfc", romBuffer, MAX_ROM_SIZE);
    if (romSize == 0) {
        // Handle error: file not found or size 0
    }

    // 5. Put the SNES in /RESET so it does not access the SRAM while we write
    SuperCIC_HoldReset();  // or the /RESET signal you have

    // 6. Copy the ROM to the SRAM
    //    Assume your cart defines a "STM32 mode" where the SRAM is controlled by the microcontroller
    SRAM_BeginWrite();  // e.g. put /CE in "controlled by STM32" mode
    SRAM_Write(romBuffer, romSize); 
    SRAM_EndWrite();

    free(romBuffer);

    // 7. Release /RESET so the SNES starts from the SRAM
    SuperCIC_ReleaseReset(); 

    // 8. Optionally, turn off or "sleep" the STM32 (if you don't need to do anything else)
    //    Or stay in a loop
    while (1) {
        // TODO: sleep, etc.
        HAL_Delay(1000);
    }

}
