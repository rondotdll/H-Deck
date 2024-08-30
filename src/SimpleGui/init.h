#pragma once

#include <TFT_eSPI.h>

#include "helper.h"

namespace SGui {
static TFT_eSPI tft = TFT_eSPI();  // TFT display object

// Initialize the TFT display
// returns a pointer to the TFT_eSPI object
TFT_eSPI* Init();
}