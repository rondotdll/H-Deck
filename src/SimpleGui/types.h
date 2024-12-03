#pragma once

#include <functional>
#include <unordered_map>

#include <TFT_eSPI.h>

#include "pins.h"

namespace SGui {
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

  enum UIOrientation {
    HORIZONTAL,
    VERTICAL,
    // HORIZONTAL_R, // unused / commented for simplicity.
    // VERTICAL_R
  };

  // Input types for input events
  enum input_type_t {
    BASIC = 1,
    TRACKBALL = 1,
    KEYBOARD = 1,
    TOUCH = 2,
  };

  // Trackball single input IDs
  enum trackball_input_id_t: uint8_t {                                        // XXXXXXXX = PIN ID
    TRACKBALL_PRESS = (16),   // 00010000
    TRACKBALL_UP =    (1),    // 00000001
    TRACKBALL_DOWN =  (2),    // 00000010
    TRACKBALL_LEFT =  (4),    // 00000100
    TRACKBALL_RIGHT = (8),    // 00001000
  };

  enum handler_exception_t {
    OK,
    NO_HANDLER,
    BAD_HANDLER,
  };

  typedef struct _Point2D {
    uint16_t x;
    uint16_t y;
  } SGRect, SGPoint;

  typedef struct _BoxSpacing {
    uint16_t top;
    uint16_t right;
    uint16_t bottom;
    uint16_t left;
  } UIBoxSpacing;

  typedef std::function<void()> e_handler_t;  // Event handler type
  typedef int color_t;                        // Color type

  // Stores specific input events (type & ID)
  typedef struct input_event_t {
    input_type_t type;
    uint16_t id;

    uint16_t flatten() const {
      return (static_cast<uint16_t>(this->type) << 8) | this->id;
    };

  } input_event_t;

  static TFT_eSPI tft = TFT_eSPI();  // TFT display object

}  // namespace SGui