#pragma once

#include "UIComponent.h"
#include "../types.h"

namespace SGui {

// UILabel class for displaying text on the screen
class UILabel : public UIComponent {
 public:
  String text_ = "";
  int text_size_ = 1;

  explicit UILabel(String text) : UIComponent() {
      this->text_ = text;
      this->size_.x = tft.textWidth(text);
      this->size_.y = tft.fontHeight();
  };

  // Set the text of the label
  UILabel* SetText(String text);

  // Set the text size multiplier of the label
  // Default: 1
  UILabel* SetTextSize(int text_size);

  // Get the label text
  String GetText() const { return this->text_; }

  // Get the text size of the label
  int GetTextSize() const { return this->text_size_; }

  // Draw the label
  void Draw() override;
};

}  // namespace SGui
