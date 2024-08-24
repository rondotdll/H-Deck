#pragma once

#include <vector>
#include <TFT_eSPI.h>
#include <Wire.h>
#include <SPI.h>


namespace SGui {
    static TFT_eSPI tft = TFT_eSPI();

    typedef std::function<void()> e_handler;
    typedef int color_t;

    inline TFT_eSPI* Init() {
        tft.init();
        tft.setRotation(1);
        tft.fillScreen(TFT_BLACK);

        return &tft;
    }
};

#include "UIComponent.h"
#include "UIWindow.h"
#include "UILabel.h"
#include "UIButton.h"
