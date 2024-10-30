#include <SPI.h>
#include <TFT_eSPI.h>

#include "main.h"
#include "SimpleGui/SimpleGui.h"

#define MAX_FRAMERATE 15

constexpr double frame_sleep = 1000 / MAX_FRAMERATE;

void powerTFT() {
  pinMode(TFT_BACKLIGHT_P, OUTPUT);
  digitalWrite(TFT_BACKLIGHT_P, HIGH);

  pinMode(POWER_ON_P, OUTPUT);
  digitalWrite(POWER_ON_P, HIGH);
}

void setup() {
  Serial.begin(115200);

  pinMode(POWER_ON_P, OUTPUT);
  digitalWrite(POWER_ON_P, HIGH);

  Serial.println("Trackball Test Started");
}

void loop() {
  // Main loop
  /* 1.) Handle Input
   * 2.) Execute Task(s)
   * 3.) Update UI
   * 4.) Render
   */

  delay(frame_sleep); // Wait for the next frame (as not to overload the Display or the CPU)
}
