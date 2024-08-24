//
// Created by david on 8/24/2024.
//

#include "UIButton.h"

namespace SGui {
    void UIButton::press(bool p) {
        isPressed = p;
        draw();
        if (p && onClick) onClick();
    }

    void UIButton::draw() {
        if (w = 0) { w = tft.textWidth(label) + (px*2); }
        if (h = 0) { h = tft.fontHeight() + (py*2); }

        if (isPressed) {
            tft.fillRect(x, y, w, h, a_bg);
            tft.setTextColor(a_text_color);

            tft.drawString(label, x + px, y + py);
        } else {
            tft.drawRect(x, y, w, h, bg);
            tft.setTextColor(text_color);
            tft.drawString(label, x + px, y + py);
        }
    }
} // SGui