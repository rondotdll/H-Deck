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
  SGui::UIWindow mainWindow = SGui::UIWindow();
  mainWindow.SetTitle("H-DECK PROTOTYPE");
  mainWindow.SetColor(TFT_RED);

  SGui::UILabel title_label = SGui::UILabel("Hello, World!");
  title_label.SetPos(5, 2);

  mainWindow.AddChild(&title_label);
  mainWindow.Draw();
}

void loop() {}
