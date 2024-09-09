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

  // Create a window
  SGui::UIWindow mainWindow = SGui::UIWindow();
    mainWindow.SetTitle("H-DECK PROTOTYPE");
    mainWindow.SetColor(TFT_RED);

  // Create a sub window
  SGui::UIWindow subWindow = SGui::UIWindow();
    subWindow.SetTitle("Sub Window");
    subWindow.SetColor(TFT_GREEN);

  mainWindow.AddChild(&subWindow);  // Add the sub window to the main window
  subWindow.FillParent();           // Fill the sub window to the parent window

  // Create a label
  SGui::UILabel title_label = SGui::UILabel("Hello, World!");
    title_label.SetPos(5, 2);

  // Add the label to the sub window
  subWindow.AddChild(&title_label);

  // Center the label within the parent
  title_label.AlignToParent(SGui::BOTTOM_CENTER);

  // Draw the main window
  mainWindow.Draw();
}

void loop() {}
