#include <SPI.h>
#include <TFT_eSPI.h>

#include "SimpleGui/SimpleGui.h"
#include "main.h"

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
  SGui::UIWindow window =
      SGui::UIWindow("H-DECK PROTOTYPE FIRMWARE", 0, 0, 0, 0, TFT_RED);

  SGui::UILabel title_label = SGui::UILabel("Hello, World!", 5, 5);

  window.AddChild(&title_label);
  window.Draw();
}

void loop() {}
