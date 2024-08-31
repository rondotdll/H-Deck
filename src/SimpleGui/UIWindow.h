#pragma once

#include <TFT_eSPI.h>

#include "init.h"
#include "helper.h"
#include "UIContainer.h"

namespace SGui {
// Window Component
class UIWindow : public UIContainer {
 public:
  const SGRect title_padding{4, 4};
  int border_thickness = 1;
  String title_ = ""; // Window title
  color_t color_ = TFT_WHITE; // Window color

  explicit UIWindow() : UIContainer() {
    if (this->dim_.x == 0)
      this->dim_.x = TFT_WIDTH;
    if (this->dim_.y == 0)
      this->dim_.y = TFT_HEIGHT;

    this->padding_.x = border_thickness;
    this->padding_.y = border_thickness
                        + (2*title_padding.y)   // account for padding in title bar
                        + tft.fontHeight();     // account for title text

    if (title_ != "") {
      this->pos_.y = tft.fontHeight() + this->pos_.y + 1;
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
