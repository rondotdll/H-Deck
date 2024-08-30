#pragma once

#include <functional>

namespace SGui {

typedef struct _Vector2D {
  uint16_t x;
  uint16_t y;
} SGRect, SGPoint;

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