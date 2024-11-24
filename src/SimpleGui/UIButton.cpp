//
// Created by david on 11/24/2024.
//

#include <TFT_eSPI.h>

#include "UIButton.h"

namespace SGui {

  // Set the text of the button
  UIButton* UIButton::SetText(String text) {
    this->text_ = text;

    // Update the size of the button
    this->size_.x = tft.textWidth(text) * this->text_size_;
    this->size_.y = tft.fontHeight() * this->text_size_;
    return this;
  }

  // Set the text size of the button
  // Default: 1
  UIButton* UIButton::SetTextSize(int text_size) {
    this->text_size_ = text_size;

    // Update the size of the button
    this->size_.x = tft.textWidth(this->text_) * this->text_size_;
    this->size_.y = tft.fontHeight() * this->text_size_;
    return this;
  }

  // Set the text color of the button
  UIButton* UIButton::SetTextColor(color_t color) {
      this->color_ = color;
      return this;
  }

  // Set the background color of the button
  UIButton* UIButton::SetBgColor(color_t color) {
    this->bg_color_ = color;
    return this;
  }

  // Set the click handler of the button
  UIButton* UIButton::SetClickHandler(e_handler_t &&handler) {
      this->click_handler_ = std::move(handler);
      return this;
  }

  // Set the button padding
  UIButton* UIButton::SetPadding(int x, int y) {
      this->padding_.top = y;
      this->padding_.left = x;
      this->padding_.bottom = y;
      this->padding_.right = x;
      return this;
  }
  UIButton* UIButton::SetPadding(int top, int left, int bottom, int right) {
      this->padding_.top = top;
      this->padding_.left = left;
      this->padding_.bottom = bottom;
      this->padding_.right = right;
      return this;
  }
  UIButton* UIButton::SetPadding(SGBoxSpacing padding) {
      this->padding_ = padding;
      return this;
  }

  // Draw the button
  void UIButton::Draw() {
    // Draw the button border
    tft.drawRect(this->pos_.x, this->pos_.y,
                  this->size_.x + (this->padding_.left + this->padding_.right),
                  this->size_.y + (this->padding_.top + this->padding_.bottom),
                  this->color_);

    // Draw the button background
    if (this->is_focused_) {
      tft.fillRect(this->pos_.x, this->pos_.y,
                    this->size_.x + (this->padding_.left + this->padding_.right),
                    this->size_.y + (this->padding_.top + this->padding_.bottom),
                    this->bg_color_);
    }
    // Draw the button text
    tft.setTextColor(this->color_);
    tft.setTextSize(this->text_size_);
    tft.drawString(this->text_, this->pos_.x + this->padding_.left, this->pos_.y + this->padding_.bottom);
  }
}