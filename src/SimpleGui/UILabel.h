#pragma once

#include "UIComponent.h"
#include "SimpleGui.h"

namespace SGui {
    class UILabel : public UIComponent {
    public:
        int x, y, color, size;
        String text;

        UILabel(int x, int y, String text, int text_size = 1, int text_color = TFT_WHITE) : x(x), y(y), text(text), size(text_size), color(text_color) {}

        void draw() override;
    };
}