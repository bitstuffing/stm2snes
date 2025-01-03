#ifndef SRAM_H
#define SRAM_H

#include <stdint.h>

void SRAM_BeginWrite(void);
void SRAM_Write(const uint8_t *data, uint32_t length);
void SRAM_EndWrite(void);

#endif
