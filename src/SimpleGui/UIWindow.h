#pragma once

#include <TFT_eSPI.h>

#include "init.h"
#include "helper.h"
#include "UIContainer.h"

namespace SGui {
// Window Component
class UIWindow : public UIContainer {
 public:
  int title_px = 4; // Title horizontal padding
  int title_py = 4; // Title vertical padding
  int border_thickness = 1;
  String title; // Window title
  color_t color; // Window color

  explicit UIWindow(String title = "", int x = 0, int y = 0, int w = 0,
                    int h = 0, color_t color = TFT_WHITE) {
    this->x_ = x;
    this->y_ = y;

    this->w_ = w;
    this->h_ = h;

    this->px_ = px_ + border_thickness;
    this->py_ = py_ + border_thickness + (2*title_py);

    if (this->w_ == 0)
      this->w_ = GetScreenEdges().first;
    if (this->h_ == 0)
      this->h_ = GetScreenEdges().second;

    this->color = color;
    this->title = title;

    if (title != "") {
      this->py_ = tft.fontHeight() + y + 1;
    }
  };

  // Set the title of the window
  UIWindow* SetTitle(String title);

  // Set the color of the window
  UIWindow* SetColor(color_t color);

  // Set the padding of the container (accounts for window border and title bar)
  UIContainer* SetPadding(int padding_x, int padding_y) override;

  // Draw the window and its children
  void Draw() override;
};
}  // namespace SGui
