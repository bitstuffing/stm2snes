#ifndef SDCARD_H
#define SDCARD_H

#include <stdint.h>

uint32_t SDCARD_ReadFile(const char* filename, uint8_t* buffer, uint32_t maxLen);

#endif