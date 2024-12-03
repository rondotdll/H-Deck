#pragma once

#include <cstdint>

namespace SGui {
  // bunch of pre-compressed color definitions for convenience
  // (taken from TFT_eSPI.h)
  #define BLACK         TFT_BLACK             /*   0,   0,   0 */
  #define NAVY          TFT_NAVY              /*   0,   0, 128 */
  #define DARKGREEN     TFT_DARKGREEN         /*   0, 128,   0 */
  #define DARKCYAN      TFT_DARKCYAN          /*   0, 128, 128 */
  #define MAROON        TFT_MAROON            /* 128,   0,   0 */
  #define PURPLE        TFT_PURPLE            /* 128,   0, 128 */
  #define OLIVE         TFT_OLIVE             /* 128, 128,   0 */
  #define LIGHTGREY     TFT_LIGHTGREY         /* 211, 211, 211 */
  #define DARKGREY      TFT_DARKGREY          /* 128, 128, 128 */
  #define BLUE          TFT_BLUE              /*   0,   0, 255 */
  #define GREEN         TFT_GREEN             /*   0, 255,   0 */
  #define CYAN          TFT_CYAN              /*   0, 255, 255 */
  #define RED           TFT_RED               /* 255,   0,   0 */
  #define MAGENTA       TFT_MAGENTA           /* 255,   0, 255 */
  #define YELLOW        TFT_YELLOW            /* 255, 255,   0 */
  #define WHITE         TFT_WHITE             /* 255, 255, 255 */
  #define ORANGE        TFT_ORANGE            /* 255, 180,   0 */
  #define GREENYELLOW   TFT_GREENYELLOW       /* 180, 255,   0 */
  #define PINK          TFT_PINK              /* 255, 192, 203 */ //Lighter pink, was 0xFC9F
  #define BROWN         TFT_BROWN             /* 150,  75,   0 */
  #define GOLD          TFT_GOLD              /* 255, 215,   0 */
  #define SILVER        TFT_SILVER            /* 192, 192, 192 */
  #define SKYBLUE       TFT_SKYBLUE           /* 135, 206, 235 */
  #define VIOLET        TFT_VIOLET            /* 180,  46, 226 */

  class UIColor {
    uint8_t red_;
    uint8_t green_;
    uint8_t blue_;

    // Define a color using rgb format
    explicit UIColor(uint8_t r, uint8_t g, uint8_t b) {
      this->red_ = r;
      this->green_ = g;
      this->blue_ = b;
    }

    // Define a color using Hexadecimal Format (rgb)
    explicit UIColor(int hex) {
      this->red_ = hex & 0xFF0000;
      this->green_ = hex & 0x00FF00;
      this->blue_ = hex & 0x0000FF;
    }

    // Compress the color to 16-bit format (this is what the renderer uses)
    uint16_t Compress() const {
      return ((this->red_ & 0b11111000) << 8 ) + ((this->green_ & 0b11111100) << 11 ) + (this->blue_ & 0b11111000 >> 3);
    }
  };
}