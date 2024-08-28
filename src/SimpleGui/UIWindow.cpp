//
// Created by david on 8/24/2024.
//

#include "UIWindow.h"

namespace SGui {
    void UIWindow::draw() {
        clearScreen();
        tft.drawRect(0, 0, w, h, color);
        tft.setTextColor(getContrast(color));

        if (title != nullptr && title != "") {
            int title_px = 4;
            int title_py = 4;
            tft.fillRect(x, y,
                         x + w,
                         y + tft.fontHeight() + 2*title_py,
                         color);  // Title bar separator
            tft.drawString(title, x + title_px, y + title_py);
        }
    }
} // SGui