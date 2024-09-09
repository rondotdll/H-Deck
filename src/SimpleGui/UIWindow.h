#pragma once

#include <TFT_eSPI.h>

#include "init.h"
#include "helper.h"
#include "UIContainer.h"

namespace SGui {
// Window Component
class UIWindow : public UIContainer {
 public:
  const SGBoxSpacing title_padding{4, 4, 4, 4};
  String title_ = ""; // Window title
  color_t color_ = TFT_WHITE; // Window color

  explicit UIWindow() : UIContainer() {
    if (this->size_.x == 0)
      this->size_.x = TFT_WIDTH;
    if (this->size_.y == 0)
      this->size_.y = TFT_HEIGHT;

    this->padding_.top = (title_padding.top + title_padding.bottom)      // account for padding in title bar
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
  UIContainer* SetPadding(int padding_top, int padding_right, int padding_bottom, int padding_left) override;

  // Draw the window and its children
  void Draw() override;
};
}  // namespace SGui
