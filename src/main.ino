#include <SPI.h>
#include <TFT_eSPI.h>

#include "main.h"

#include "SimpleGui/SimpleGui.h"

#define MAX_FRAMERATE 15

constexpr double frame_sleep = 1000 / MAX_FRAMERATE;

void powerBoard() {
  pinMode(POWER_ON_P, OUTPUT);
  digitalWrite(POWER_ON_P, HIGH);
}

void powerTFT() {
  pinMode(TFT_BACKLIGHT_P, OUTPUT);
  digitalWrite(TFT_BACKLIGHT_P, HIGH);
}

static SGui::GUIManager gui;

void setup() {
  Serial.begin(115200);

  powerTFT();
  powerBoard();

  gui = SGui::GUIManager();

  SGui::UIWindow window = SGui::UIWindow();
  window.SetColor(TFT_RED)
    ->SetTitle("Example Window")
    ->AddChild(
        new SGui::UILabel("Hello, World!\nThis is a basic UI example to verify the code is working properly.")
    );

  gui.add_window(&window);
  gui.set_active_window(&window);

  Serial.println("Setup Finished.");

}

void loop() {
  // Main loop
  /* 1.) Handle Input
   * 2.) Execute Task(s)
   * 3.) Update UI
   * 4.) Render
   */
    Serial.println("Looped.");
  Serial.println(gui.get_active_window()->title_);
  // gui.draw();
  // delay(frame_sleep); // Wait for the next frame (as not to overload the Display or the CPU)
}
