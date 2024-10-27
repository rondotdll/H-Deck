#include <SPI.h>
#include <TFT_eSPI.h>

#include "SimpleGui/SimpleGui.h"
#include "TDeckInput/TDeckInput.h"
#include "main.h"

#define MAX_FRAMERATE 15

constexpr double frame_sleep = 1000 / MAX_FRAMERATE;

void powerTFT() {
  pinMode(TFT_BACKLIGHT_P, OUTPUT);
  digitalWrite(TFT_BACKLIGHT_P, HIGH);

  pinMode(POWER_ON_P, OUTPUT);
  digitalWrite(POWER_ON_P, HIGH);
}

TDeckInput::handler_t InputHandler;


void setup() {
  InputHandler = TDeckInput::handler_t();

  Serial.begin(115200);

  pinMode(POWER_ON_P, OUTPUT);
  digitalWrite(POWER_ON_P, HIGH);

  pinMode(TRACKBALL_LEFT_P, INPUT_PULLUP);
  pinMode(TRACKBALL_RIGHT_P, INPUT_PULLUP);
  pinMode(TRACKBALL_UP_P, INPUT_PULLUP);
  pinMode(TRACKBALL_DOWN_P, INPUT_PULLUP);
  pinMode(TRACKBALL_PRESS_P, INPUT_PULLUP);

  attachInterrupt(TRACKBALL_LEFT_P, doSomething, RISING);
  attachInterrupt(TRACKBALL_RIGHT_P, doSomething, RISING);
  attachInterrupt(TRACKBALL_UP_P, doSomething, RISING);
  attachInterrupt(TRACKBALL_DOWN_P, doSomething, RISING);
  attachInterrupt(TRACKBALL_PRESS_P, doSomething, RISING);

  Serial.println("Trackball Test Started");
}

void loop() {
  // Main loop
  /* 1.) Handle Input
   * 2.) Execute Task(s)
   * 3.) Update UI
   * 4.) Render
   */

    // Handle Input
    InputHandler.handle();



  delay(frame_sleep); // Wait for the next frame (as not to overload the Display or the CPU)
}
