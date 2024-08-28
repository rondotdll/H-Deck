#pragma once

#include "UIComponent.h"
#include "SimpleGui.h"

namespace SGui {
    class UILabel : public UIComponent {
    public:
        color_t color, size;
        String text;

        UILabel(int x, int y, String text, int w = 0, int h = 0, int text_size = 1, int text_color = TFT_WHITE) {
            this->x = x;
            this->y = y;

            if (this->w == 0) this->w = tft.textWidth(text);
            if (this->h == 0) this->h = tft.fontHeight();

            this->w = w;
            this->h = h;

            this->text = text;
            this->size = text_size;
            this->color = text_color;
        };
        void draw() override;
    };
}