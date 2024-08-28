#pragma once

#include <TFT_eSPI.h>

#include "UIComponent.h"
#include "SimpleGui.h"

namespace SGui {
    // Window Component
    class UIWindow : public UIComponent {

    public:
        String title;
        color_t color;

        UIWindow(int x, int y, String title, int w = 0, int h = 0, color_t color = TFT_WHITE) {
            this->x = x;
            this->y = y;

            this->w = w;
            this->h = h;

            if (this->w == 0) this->w = getScreenEdges().first;
            if (this->h == 0) this->h = getScreenEdges().second;

            this->color = color;
            this->title = title;
        };

        void draw() override;
    };
}