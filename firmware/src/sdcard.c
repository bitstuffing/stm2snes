#include "sdcard.h"
#include <stdint.h>
#include "ff.h"  

uint32_t SDCARD_ReadFile(const char* filename, uint8_t* buffer, uint32_t maxLen) {
    FIL fil;
    UINT bytesRead;
    FRESULT res;

    res = f_open(&fil, filename, FA_READ);
    if (res != FR_OK) {
        return 0;
    }

    // read file until maxLen or EOF
    res = f_read(&fil, buffer, maxLen, &bytesRead);
    f_close(&fil);

    if(res != FR_OK) {
        return 0;
    }
    return (uint32_t) bytesRead;
}
