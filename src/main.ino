#include <TFT_eSPI.h>
#include <SPI.h>

#include "main.h"
#include "SimpleGui/SimpleGui.h"

// static TFT_eSPI* tft;
static SGui::UIButton* button;

void powerTFT() {
    pinMode(TFT_BACKLIGHT_P, OUTPUT);
    digitalWrite(TFT_BACKLIGHT_P, HIGH);

    pinMode(POWER_ON_P, OUTPUT);
    digitalWrite(POWER_ON_P, HIGH);
}

void setup() {
    Serial.begin(115200);

    SGui::Init();
    powerTFT();

    // Create and draw a window
    SGui::UIWindow window(0, 0, "Main Window", 0, 0, TFT_RED);
    window.draw();

    // Create and draw a label
    SGui::UILabel label(5, 25, "Hello, World!");
    label.draw();

    // // Create and draw a button with an action
    // button = new SGui::UIButton(20, 80, "Click Me", []() {
    //     Serial.println("Button clicked!");
    // });

    // button->draw();
}

void loop() {

}
