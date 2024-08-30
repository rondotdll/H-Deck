#pragma once

#include "types.h"

namespace SGui {
// Find the true edges of the screen (useful for drawing around a screen border)
// returns (width, height)
std::pair<int, int> GetScreenEdges();

// Clear the screen to black
void clearScreen();

// Determine the appropriate text color (black or white) based on background color
color_t getContrast(color_t bg);
}