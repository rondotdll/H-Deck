#pragma once

#include "types.h"
#include "UIColor.h"

namespace SGui{
  class UIStyle {
  private:
    UIColor* foreground_;
    UIColor* background_;
    UIColor* border_color_;

    uint8_t border_thickness_;
    uint8_t text_size_;

    UIBoxSpacing padding_;
  public:
    explicit UIStyle(UIColor* foreground, UIColor background, UIColor border_color, uint8_t border_thickness, uint8_t text_size, UIBoxSpacing padding) {
      this->foreground_ = foreground;
      this->background_ = background;
      this->border_color_ = border_color;

      this->border_thickness_ = border_thickness;
      this->text_size_ = text_size;

      this->padding_ = padding;
    }

    UIStyle* SetForeground(UIColor* color) {
      this->foreground_ = color;
      return this;
    }

    UIStyle* SetBackground(UIColor* color) {
      this->background_ = color;
      return this;
    }
    

  };
}