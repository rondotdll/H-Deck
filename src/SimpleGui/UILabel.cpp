//
// Created by david on 8/24/2024.
//

#include <TFT_eSPI.h>

#include "UILabel.h"

namespace SGui {
  // Set the text of the label
  UILabel* UILabel::SetText(String text) {
    this->text_ = text;
    this->size_.x = tft.textWidth(text);
    this->size_.y = tft.fontHeight();
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
    tft.setTextColor(this->color_);
    tft.setTextSize(this->text_size_);
    tft.drawString(this->text_, this->pos_.x, this->pos_.y);
  }
}  // namespace SGui
