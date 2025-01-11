//
// Created by david on 8/24/2024.
//

#include "Window.h"

namespace SGui {
// Set the title of the window
Window* Window::SetTitle(String title) {
  this->title_ = title;
  return this;
}

// Set the color of the window
Window* Window::SetColor(UIColor color) {
  this->style_->SetBorderColor(color);
  return this;
}

// Set the padding of the container (accounts for window border and title bar)
Container* Window::SetPadding(int padding_top, int padding_right, int padding_bottom, int padding_left) {
  this->style_->padding_.top = padding_top + this->title_padding.top + this->title_padding.bottom + tft.fontHeight();
  this->style_->padding_.right = padding_right;
  this->style_->padding_.bottom = padding_bottom;
  this->style_->padding_.left = padding_left;
  return this;
}

// Draw the window and its children
void Window::Draw() {
  // If the window is inside a container, adjust its position accordingly.
  if (this->parent_ != nullptr) {
    this->MoveIntoParentBounds();
  }

  tft.drawRect(this->pos_.x, this->pos_.y, this->size_.x, this->size_.y, this->style_->border_color_);
  tft.setTextColor(this->style_->foreground_.Compress());

  // If title isn't null, draw the title bar
  if (title_ != nullptr && title_ != "") {
    tft.fillRect(this->pos_.x,
                 this->pos_.y,
                 this->size_.x,
                 tft.fontHeight() + (this->title_padding.bottom + this->title_padding.top),
                 this->style_->border_color_);  // Title bar separator
    tft.drawString(title_, this->pos_.x + this->title_padding.left, this->pos_.y + this->title_padding.top);
  }

  DrawChildren();
}

}  // namespace SGui
