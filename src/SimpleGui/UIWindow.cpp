//
// Created by david on 8/24/2024.
//

#include "UIWindow.h"

namespace SGui {
// Set the title of the window
UIWindow* UIWindow::SetTitle(String title) {
  this->title_ = title;
  return this;
}

// Set the color of the window
UIWindow* UIWindow::SetColor(color_t color) {
  this->color_ = color;
  return this;
}

// Set the padding of the container (accounts for window border and title bar)
UIContainer* UIWindow::SetPadding(int padding_x, int padding_y) {
  this->padding_.x = padding_x + border_thickness;
  this->padding_.y = padding_y + border_thickness + (2*title_padding.y);
  return this;
}

// Draw the window and its children
void UIWindow::Draw() {
  clearScreen();
  tft.drawRect(0, 0, this->dim_.x, this->dim_.y, color_);
  tft.setTextColor(getContrast(color_));

  if (title_ != nullptr && title_ != "") {

    tft.fillRect(this->pos_.x,
                 this->pos_.y,
                 this->pos_.x + this->dim_.x,
                 this->pos_.y + tft.fontHeight() + 2 * this->title_padding.y,
                 color_);  // Title bar separator
    tft.drawString(title_, this->pos_.x + this->title_padding.x, this->pos_.y + this->title_padding.y);
  }

  DrawChildren();
}

}  // namespace SGui
