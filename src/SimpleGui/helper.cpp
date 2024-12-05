#include <utility>
#include <TFT_eSPI.h>

#include "types.h"
#include "helper.h"

namespace SGui {
// Find the true edges of the screen (useful for drawing around a screen border)
// returns (width, height)
std::pair<int, int> GetScreenEdges() {
  int w = TFT_WIDTH;
  int h = TFT_HEIGHT;

  // if landscape orientation, invert width & height
  if (tft.getRotation() % 2 != 1) {
    w = TFT_HEIGHT;
    h = TFT_WIDTH;
  }

  return std::make_pair(w, h);
}

// Clear the screen to black
void clearScreen() {
  tft.fillRect(0, 0, tft.width(), tft.height(), TFT_BLACK);
}
}