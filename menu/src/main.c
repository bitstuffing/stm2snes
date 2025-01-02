#include <snes.h>

extern char tilfont, palfont;

#define SCREEN_WIDTH_TILES  32
#define SCREEN_HEIGHT_TILES 28

void drawAsciiBorder() {
    int x, y;
    // ASCII characters for the border
    char cornerTL = '+'; 
    char cornerTR = '+';
    char cornerBL = '+';
    char cornerBR = '+';
    char hLine    = '-';
    char vLine    = '|';

    // corners
    consoleDrawText(0, 0,   "%c", cornerTL);
    consoleDrawText(SCREEN_WIDTH_TILES-1, 0,   "%c", cornerTR);
    consoleDrawText(0, SCREEN_HEIGHT_TILES-1,   "%c", cornerBL);
    consoleDrawText(SCREEN_WIDTH_TILES-1, SCREEN_HEIGHT_TILES-1,   "%c", cornerBR);

    // horizontal lines (top y bottom)
    for (x=1; x<SCREEN_WIDTH_TILES-1; x++) {
        consoleDrawText(x, 0,   "%c", hLine);
        consoleDrawText(x, SCREEN_HEIGHT_TILES-1, "%c", hLine);
    }
    // vertical lines (left y right)
    for (y=1; y<SCREEN_HEIGHT_TILES-1; y++) {
        consoleDrawText(0, y,   "%c", vLine);
        consoleDrawText(SCREEN_WIDTH_TILES-1, y,   "%c", vLine);
    }
}
//---------------------------------------------------------------------------------
int main(void)
{
    // Initialize text console with our font
    consoleSetTextVramBGAdr(0x6800);
    consoleSetTextVramAdr(0x3000);
    consoleSetTextOffset(0x0100);
    consoleInitText(0, 16 * 2, &tilfont, &palfont);

    // Init background
    bgSetGfxPtr(0, 0x2000);
    bgSetMapPtr(0, 0x6800, SC_32x32);

    // Now Put in 16 color mode and disable Bgs except current
    setMode(BG_MODE1, 0);
    drawAsciiBorder();
    bgSetDisable(1);
    bgSetDisable(2);

    // Draw a wonderful hello world text :P
    consoleDrawText(9, 10, "Hello @aisflou!");
    consoleDrawText(5, 16, "@bitstuffing rev. 0.0.1");

    // Wait for nothing :P
    setScreenOn();

    while (1){
        WaitForVBlank();
    }
    return 0;
}