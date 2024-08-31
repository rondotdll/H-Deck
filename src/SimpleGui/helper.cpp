#include <utility>
#include <TFT_eSPI.h>

#include "types.h"
#include "helper.h"
#include "init.h"

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

// Determine the appropriate text color (black or white) based on background color
color_t getContrast(color_t bg) {
  // Extract red, green, and blue components from 16-bit RGB565 color
  uint8_t red = (bg >> 11) & 0x1F;
  uint8_t green = (bg >> 5) & 0x3F;
  uint8_t blue = bg & 0x1F;

  // Convert 5/6-bit color components to 8-bit
  red = red << 3;
  green = green << 2;
  blue = blue << 3;

  // Calculate luminance using the ITU-R BT.601 formula
  // Y = 0.299 * R + 0.587 * G + 0.114 * B
  color_t luminance = (color_t)(0.299 * red + 0.587 * green + 0.114 * blue);

  // If luminance is less than 128, return white; otherwise, return black
  return (luminance < 128) ? TFT_WHITE : TFT_BLACK;
}
}