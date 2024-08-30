#include "init.h"

namespace SGui {
// Initialize the TFT display
// returns a pointer to the TFT_eSPI object
TFT_eSPI* Init() {
  tft.init();
  tft.setRotation(1);
  clearScreen();

  return &tft;
}
}