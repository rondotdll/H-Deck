#include <TFT_eSPI.h>
#include <SPI.h>

#include "main.h"
#include "SimpleGui/SimpleGui.h"

static TFT_eSPI* tft;
static SGui::UIButton* button;

void powerTFT() {
    pinMode(TFT_BACKLIGHT_P, OUTPUT);
    digitalWrite(TFT_BACKLIGHT_P, HIGH);

    pinMode(POWER_ON_P, OUTPUT);
    digitalWrite(POWER_ON_P, HIGH);
}

void setup() {
    Serial.begin(115200);

    tft = SGui::Init();
    powerTFT();

    // Create and draw a window
    SGui::UIWindow window(10, 10, 220, 150, "Main Window");
    window.draw();

    // Create and draw a label
    SGui::UILabel label(20, 40, "Hello, World!");
    label.draw();

    // Create and draw a button with an action
    button = new SGui::UIButton(20, 80, "Click Me", []() {
        Serial.println("Button clicked!");
    });

    button->draw();
}

void loop() {

}
