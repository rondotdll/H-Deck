#pragma once

#include "UIComponent.h"
#include "../types.h"

namespace SGui {
class UIButton : public UIComponent {
  bool isInput_ = true;
 public:
  String text_ = "";
  int text_size_ = 1;
  color_t color_ = TFT_WHITE;
  color_t bg_color_ = TFT_RED;

  UIBoxSpacing padding_ = {2, 2, 2, 2};

  bool is_focused_ = false;
  e_handler_t click_handler_ = nullptr;

  explicit UIButton(String text, e_handler_t &&click_handler) : UIComponent() {
    this->text_ = text;
    this->click_handler_ = std::move(click_handler);
    this->size_.x = tft.textWidth(text);
    this->size_.y = tft.fontHeight();
  }

  // Set the text of the button
  UIButton* SetText(String text);

  // Set the text size multiplier of the button
  // Default: 1
  UIButton* SetTextSize(int text_size);

  // Set the text color of the button
  UIButton* SetTextColor(color_t color);

  // Set the background color of the button
  UIButton* SetBgColor(color_t color);

  // Set the click handler of the button
  UIButton* SetClickHandler(e_handler_t &&handler);

  // Set the button padding
  UIButton* SetPadding(int x, int y);
  UIButton* SetPadding(int top, int left, int bottom, int right);
  UIButton* SetPadding(UIBoxSpacing padding);

  // Get the button text
  String GetText() const { return this->text_; }

  // Get the text size of the button
  int GetTextSize() const { return this->text_size_; }

  // Get the text color of the button
  color_t GetTextColor() const { return this -> color_; }

  // Get the background color of the button
  color_t GetBgColor() const { return this -> bg_color_; }

  // Focus the button (draws background)
  void Focus() { this->is_focused_ = true; }

  // Unfocus the button (draws border)
  void Unfocus() { this->is_focused_ = false; }

  // Trigger the click event
  void Click() const { this->click_handler_(); }

  // Get the actual rendered size of the button
  SGRect GetRenderedSize() const override {
    return {
      (uint16_t)(this->size_.x + this->padding_.left + this->padding_.right),
      (uint16_t)(this->size_.y + this->padding_.top + this->padding_.bottom)
    };
  };

  // Draw the button
  void Draw() override;

};
}