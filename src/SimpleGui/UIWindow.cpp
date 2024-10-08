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
UIContainer* UIWindow::SetPadding(int padding_top, int padding_right, int padding_bottom, int padding_left) {
  this->padding_.top = padding_top + this->title_padding.top + this->title_padding.bottom + tft.fontHeight();
  this->padding_.right = padding_right;
  this->padding_.bottom = padding_bottom;
  this->padding_.left = padding_left;
  return this;
}

// Draw the window and its children
void UIWindow::Draw() {
  if (this->parent_ != nullptr) {
    this->MoveIntoParentBounds();
  }

  tft.drawRect(this->pos_.x, this->pos_.y, this->size_.x, this->size_.y, color_);
  tft.setTextColor(getContrast(color_));

  // If title isn't null, draw the title bar
  if (title_ != nullptr && title_ != "") {
    tft.fillRect(this->pos_.x,
                 this->pos_.y,
                 this->size_.x,
                 tft.fontHeight() + (this->title_padding.bottom + this->title_padding.top),
                 color_);  // Title bar separator
    tft.drawString(title_, this->pos_.x + this->title_padding.left, this->pos_.y + this->title_padding.top);
  }

  DrawChildren();
}

}  // namespace SGui
