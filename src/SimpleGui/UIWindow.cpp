//
// Created by david on 8/24/2024.
//

#include "UIWindow.h"

namespace SGui {
// Set the title of the window
UIWindow* UIWindow::SetTitle(String title) {
  this->title = title;
  return this;
}

// Set the color of the window
UIWindow* UIWindow::SetColor(color_t color) {
  this->color = color;
  return this;
}

// Set the padding of the container (accounts for window border and title bar)
UIContainer* UIWindow::SetPadding(int padding_x, int padding_y) {
  this->px_ = padding_x + border_thickness;
  this->py_ = padding_y + border_thickness + (2*title_py);
  return this;
}

// Draw the window and its children
void UIWindow::Draw() {
  clearScreen();
  tft.drawRect(0, 0, w_, h_, color);
  tft.setTextColor(getContrast(color));

  if (title != nullptr && title != "") {

    tft.fillRect(this->x_,
                 this->y_,
                 this->x_ + this->w_,
                 this->y_ + tft.fontHeight() + 2 * this->title_py,
                 color);  // Title bar separator
    tft.drawString(title, x_ + this->title_px, y_ + this->title_py);
  }

  DrawChildren();
}

}  // namespace SGui
