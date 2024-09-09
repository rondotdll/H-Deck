#pragma once

#include <functional>

namespace SGui {

typedef struct _Point2D {
  uint16_t x;
  uint16_t y;
} SGRect, SGPoint;

typedef struct _BoxSpacing {
  uint16_t top;
  uint16_t right;
  uint16_t bottom;
  uint16_t left;
} SGBoxSpacing, SGBorderSize;

typedef std::function<void()> e_handler_t;  // Event handler type
typedef int color_t;                        // Color type

// Alignment options for UIComponents
enum UIAlignment {
  TOP_LEFT,
  TOP_CENTER,
  TOP_RIGHT,
  MID_LEFT,
  MID_CENTER,
  MID_RIGHT,
  BOTTOM_LEFT,
  BOTTOM_CENTER,
  BOTTOM_RIGHT
};

}  // namespace SGui