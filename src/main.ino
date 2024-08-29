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
    SGui::UIWindow window(0, 0, "H-DECK PROTOTYPE FIRMWARE", 0, 0, TFT_RED);
    window.draw();

    // Create and draw a label
    SGui::UILabel platform_label(5, 25, "PLATFORM: ESP32-S3 WiFi Enabled Chipset");
    SGui::UILabel based_on_label(5, 50, "DEVICE: T-DECK-920M");
    SGui::UILabel clockspeed_label(5, 75, "CPU: Dual Core XTensa LX7 MCU @ 240MHz");
    platform_label.draw();
    based_on_label.draw();
    clockspeed_label.draw();

    SGui::UILabel check_label(5, 100, "CHECK", 0, 0, 4);
    SGui::UILabel your_label(5, 150, "YOUR", 0, 0, 4);
    SGui::UILabel wifi_label(5, 200, "WIFI", 0, 0, 4);
    check_label.draw();
    your_label.draw();
    wifi_label.draw();

    // // Create and draw a button with an action
    // button = new SGui::UIButton(20, 80, "Click Me", []() {
    //     Serial.println("Button clicked!");
    // });

    // button->draw();
}

void loop() {

}
