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

  explicit UILabel(String text, int text_size = 1, color_t text_color = TFT_WHITE, int x, int y, int w, int h) : UIComponent(x, y, w, h) {
    // this->x_ = x;
    // this->y_ = y;

    if (this->w_ == 0)
      this->w_ = tft.textWidth(text);
    if (this->h_ == 0)
      this->h_ = tft.fontHeight();

    this->w_ = w;
    this->h_ = h;

    this->text_ = text;
    this->text_size_ = text_size;
    this->color_ = text_color;
  };

  // Set the text of the label
  UILabel* SetText(String text);

  // Set the text size of the label
  UILabel* SetTextSize(int text_size);

  // Set the text color of the label
  UILabel* SetColor(color_t color);

  // Get the label text
  String GetText() { return this->text_; }

  // Get the text size of the label
  int GetTextSize() { return this->text_size_; }

  // Get the text color of the label
  color_t GetTextColor() { return this->color_; }

  // Draw the label
  void Draw() override;
};

}  // namespace SGui
