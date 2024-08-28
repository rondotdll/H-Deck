#pragma once

#include <TFT_eSPI.h>

#include "UIComponent.h"
#include "SimpleGui.h"

namespace SGui {

    class UIButton : public UIComponent {
    public:
        String label; // Button text
        e_handler onClick; // Function to when button is pressed
        int px, py; // Button padding
        color_t bg, text_color; // Button colors
        color_t a_bg, a_text_color; // Button colors when pressed

        bool isPressed = false;

        UIButton(int x, int y, String label, e_handler click, int w = 0, int h = 0, int px = 1, int py = 1, color_t bg = TFT_DARKGREY, color_t text_color = TFT_WHITE, color_t active_bg = TFT_WHITE, color_t active_text_color = TFT_BLACK) {
            this->x = x;
            this->y = y;
            this->label = label;
            this->onClick = click;

            if (this->w == 0) this->w = tft.textWidth(label);
            if (this->h == 0) this->h = tft.fontHeight();

            this->text_color = text_color;
            this->a_text_color = active_text_color;

            this->bg = bg;
            this->a_bg = active_bg;

            this->px = px;
            this->py = py;
        }

        void press(bool state);
        void draw() override;
    };

} // SGui