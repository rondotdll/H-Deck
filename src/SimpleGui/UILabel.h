#pragma once

#include "SimpleGui.h"
#include "UIComponent.h"

namespace SGui {

struct Point2D {
  uint16_t x;
  uint16_t y;
};

// UILabel class for displaying text on the screen
class UILabel : public UIComponent {
 public:
  String text_ = "";
  int text_size_ = 1;
  color_t color_ = TFT_WHITE;

  explicit UILabel(String text) : UIComponent() {
      this->text_ = text;
      this->dim_.x = tft.textWidth(text);
      this->dim_.y = tft.fontHeight();
  };

  // Set the text of the label
  UILabel* SetText(String text);

  // Set the text size of the label
  UILabel* SetTextSize(int text_size);

  // Set the text color of the label
  UILabel* SetColor(color_t color);

  // Get the label text
  String GetText() const { return this->text_; }

  // Get the text size of the label
  int GetTextSize() const { return this->text_size_; }

  // Get the text color of the label
  color_t GetTextColor() const { return this->color_; }

  // Draw the label
  void Draw() override;
};

}  // namespace SGui
