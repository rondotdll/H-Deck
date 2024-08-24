//
// Created by david on 8/24/2024.
//

#include <TFT_eSPI.h>

#include "UILabel.h"

namespace SGui {
    void UILabel::draw() {
        tft.setTextColor(color);
        tft.setTextSize(size);
        tft.drawString(text, x, y);
    }
} // SGui