//
// Created by david on 8/24/2024.
//

#include <TFT_eSPI.h>

#include "UILabel.h"

namespace SGui {
  // Set the text of the label
  UILabel* UILabel::SetText(String text) {
    this->text_ = text;
    return this;
  }

  // Set the text size of the label
  UILabel* UILabel::SetTextSize(int text_size) {
      this->text_size_ = text_size;
      return this;
  }

  // Set the text color of the label
  UILabel* UILabel::SetColor(color_t color) {
      this->color_ = color;
      return this;
  }

  // Draw the label
  void UILabel::Draw() {
    if (this->parent_ != nullptr) {
      x_ =  this->parent_->x_
          + static_cast<UIContainer*>(this->parent_)->px_
          + this->x_;

      y_ =  this->parent_->y_
          + static_cast<UIContainer*>(this->parent_)->py_
          + this->y_;
    }

    tft.setTextColor(this->color_);
    tft.setTextSize(this->text_size_);
    tft.drawString(this->text_, this->x_, this->y_);
  }
}  // namespace SGui
