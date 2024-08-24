//
// Created by david on 8/24/2024.
//

#include "UIWindow.h"

namespace SGui {
    void UIWindow::draw() {
        tft.drawRect(x, y, w, h, TFT_WHITE);
        tft.setTextColor(TFT_WHITE);
        tft.drawString(title, x + 5, y + 5);
        tft.drawLine(x, y + 20, x + w, y + 20, TFT_WHITE);  // Title bar separator
    }
} // SGui