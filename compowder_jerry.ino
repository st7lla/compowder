#include <TFT_eSPI.h>
#include <AnimatedGIF.h>
#include "jerry.h"

TFT_eSPI tft = TFT_eSPI();
AnimatedGIF gif;

void GIFDraw(GIFDRAW *pDraw) {
  uint16_t *pal = pDraw->pPalette;
  uint16_t lineBuf320[320];

  for (int x = 0; x < pDraw->iWidth; x++) {
    lineBuf320[x] = pal[pDraw->pPixels[x]];
  }

  tft.pushImage(pDraw->iX, pDraw->iY + pDraw->y, pDraw->iWidth, 1, lineBuf320);
}

void setup() {
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  gif.begin(BIG_ENDIAN_PIXELS);
}

void loop() {
  if (gif.open((uint8_t *)jerry_gif, jerry_gif_len, GIFDraw)) {
    while (gif.playFrame(true, NULL)) {}
    gif.close();
  }
}