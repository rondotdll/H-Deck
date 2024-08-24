#pragma once

#include <TFT_eSPI.h>

#include "UIComponent.h"
#include "SimpleGui.h"

namespace SGui {

    class UIButton : public UIComponent {
    public:
        int x, y; // Button position
        String label; // Button text
        e_handler onClick; // Function to when button is pressed
        int w, h; // Button size
        int px, py; // Button padding
        color_t bg, text_color; // Button colors
        color_t a_bg, a_text_color; // Button colors when pressed

        bool isPressed = false;

        UIButton(int x, int y, String label, e_handler click, int w = 0, int h = 0, int px = 1, int py = 1, color_t bg = TFT_DARKGREY, color_t text_color = TFT_WHITE, color_t active_bg = TFT_WHITE, color_t active_text_color = TFT_BLACK)
        : x(x), y(y), label(label), onClick(click), w(w), h(h), px(px), py(py), bg(bg), text_color(text_color), a_bg(active_bg), a_text_color(active_text_color) {}

        void press(bool p);
        void draw() override;
    };

} // SGui