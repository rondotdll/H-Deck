#pragma once

#include <vector>
#include <algorithm>

#include "types.h"

namespace SGui {
// Find the true edges of the screen (useful for drawing around a screen border)
// returns (width, height)
std::pair<int, int> GetScreenEdges();

// Clear the screen to black
void clearScreen();

template <typename T>
// Check if a vector contains a value
inline bool v_includes(const std::vector<T>& vec, const T& value) {
  if (vec.empty())
    return false;
  return std::find(vec.begin(), vec.end(), value) != vec.end();
}


// Determine the appropriate text color (black or white) based on background color
color_t getContrast(color_t bg);
}