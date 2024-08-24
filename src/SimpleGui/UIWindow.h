#pragma once

#include <TFT_eSPI.h>

#include "UIComponent.h"
#include "SimpleGui.h"

namespace SGui {
    // Window Component
    class UIWindow : public UIComponent {
    public:
        int x, y, w, h;
        String title;

        UIWindow(int x, int y, int w, int h, String title) : x(x), y(y), w(w), h(h), title(title) {};
        void draw() override;
    };
}