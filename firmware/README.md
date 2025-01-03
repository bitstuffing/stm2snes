# Firmware

This folder stores the first version of the basic firmware to start working with.

## Dev. Notes

### Overview

The firmware in this folder is responsible for initializing the STM32, interfacing with the SD card, and copying a chosen ROM into the external SRAM before handing control back to the SNES. This allows the SNES to see and execute the “uploaded” game or homebrew code from the SRAM.
Main Firmware Workflow

#### STM32 Boot and Initialization
At power-onsinterface (SPI or SDIO) is initialized.

#### Enter “STM32 Mode”
The firmware asserts a “hold reset” signal on the SNES (often via the SuperCIC or a dedicated /RESET pin).
This ensures the SNES remains inactive while the STM32 controls the SRAM bus.

#### Copy ROM from SD to SRAM
The firmware reads the .sfc (or .bin) file from the SD card.
Using the address shift registers (74HC595) and the data transceiver (74HCT245), the STM32 writes each byte to the correct address in the external SRAM.
During this phase, the SNES is still held in reset so it does not attempt to access the SRAM.

#### Switch to “SNES Mode”
Once the copy is complete, the firmware changes GPIO signals so the SNES now has ownership of the SRAM bus.
This typically involves setting the direction pin of the bus transceiver (74HCT245) to “SNES → SRAM,” enabling /CE and /OE for the SNES, and letting /ROMSEL or other lines from the SNES control the SRAM addresses.
The STM32 stops driving the SRAM lines.

#### Release SNES Reset
The firmware deasserts the /RESET line (or instructs the SuperCIC to do so).
The SNES boots and sees the just-loaded code in the SRAM as if it were a normal cartridge ROM.

#### SNES Execution
The SNES fetches code and data from the SRAM.
The STM32 can enter a low-power state or remain idle unless you need more advanced features (e.g., saving data back to the SD, switching games on-the-fly, etc.).

### Modes Explanation

#### STM32 Mode
“STM32 Mode” indicates that the STM32 has control over the address/data lines to the SRAM. The SNES is kept in reset (or otherwise prevented from accessing the SRAM). During this mode, the firmware can read from the SD card and write the resulting data into the SRAM.

#### SNES Mode
“SNES Mode” is where the SNES has free access to the SRAM. Address lines and control signals (/CE, /OE, /WR, etc.) are driven by the SNES hardware. The STM32’s role is minimized (or tri-stated) on the bus, allowing the console to execute from SRAM seamlessly.

### Future Improvements

Additional Drivers: If you want to expand features (e.g., dynamic ROM switching, partial writes, save states, etc.), the firmware will need more advanced routines.
HAL Integration: Currently, some calls to HAL functions may be stubbed out (TODO items). They will need proper implementations or references to build fully without linker errors.
Enhanced Menu: A dedicated menu system (SNES side) could allow users to select which ROM to load from the SD in real-time, requiring more communications between the SNES and the STM32.


## Requirements

There is an script for that task:

./setup.sh