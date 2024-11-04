#include <SPI.h>
#include <TFT_eSPI.h>

#include "main.h"

#include "SimpleGui/SimpleGui.h"

#define MAX_FRAMERATE 15

constexpr double frame_sleep = 1000 / MAX_FRAMERATE;

__always_inline void powerBoard() {
  pinMode(POWER_ON_P, OUTPUT);
  digitalWrite(POWER_ON_P, HIGH);
}

__always_inline void powerTFT() {
  pinMode(TFT_BACKLIGHT_P, OUTPUT);
  digitalWrite(TFT_BACKLIGHT_P, HIGH);
}

static SGui::UIWindow* window;
static SGui::GUIManager* gui;

void setup() {
  Serial.begin(115200);

  powerBoard();
  pinMode(TFT_BACKLIGHT_P, OUTPUT);
  digitalWrite(TFT_BACKLIGHT_P, HIGH);

  gui = SGui::Init();
  gui->enable_inputs();

  window = new SGui::UIWindow();
  window->SetColor(TFT_RED);
  window->SetTitle("Example Window");
  window->AddChildren(
      {
        (new SGui::UILabel("Hello, World!"))->SetTextSize(2),
        (new SGui::UILabel("This is an example application using the SGui library!"))->MovePos(0, 16)
      }
    );

  gui->add_window(window);

  gui->bind_input_event(SGui::input_event_t{.type=SGui::TRACKBALL, .id=SGui::TRACKBALL_PRESS},
    [](SGui::GUIManager* self) {
      self->get_active_window()->SetColor(TFT_GREEN);
  });

  gui->bind_input_event(SGui::input_event_t{.type=SGui::TRACKBALL, .id=SGui::TRACKBALL_UP},
    [](SGui::GUIManager* self) {
      self->get_active_window()->SetColor(TFT_YELLOW);
  });

  gui->bind_input_event(SGui::input_event_t{.type=SGui::TRACKBALL, .id=SGui::TRACKBALL_LEFT},
    [](SGui::GUIManager* self) {
      self->get_active_window()->SetColor(TFT_RED);
  });

}

void loop() {
  // Main loop
  /* 1.) Handle Input
   * 2.) Execute Task(s)
   * 3.) Update UI
   * 4.) Render
   */
  gui->handle_inputs();
  gui->draw();
  delay(frame_sleep); // Wait for the next frame (as not to overload the Display or the CPU)
}
