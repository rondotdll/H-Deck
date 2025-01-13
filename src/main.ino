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

using namespace SGui;

static Window* window;
static GUIManager* gui;

void setup() {
  Serial.begin(115200);

  powerBoard();
  pinMode(TFT_BACKLIGHT_P, OUTPUT);
  digitalWrite(TFT_BACKLIGHT_P, HIGH);

  gui = Init();
  gui->enable_inputs();

  window = new Window();
  window->SetColor((SGui::UIColor)RED);
  window->SetTitle("Example Window");
  window->AddChildren(
      {
        (new Label("Hello, World!"))->SetTextSize(2),
        (new Button("Button 1")),
        (new Button("Button 2")),
        (new Label("This is an example application using the SGui library!"))
      }
    );

  gui->add_window(window);

  gui->bind_input_event(input_event_t{.type=TRACKBALL, .id=TRACKBALL_UP},
    [](GUIManager* self) {
      self->get_active_window()->FocusPrev(VERTICAL);
  });

  gui->bind_input_event(input_event_t{.type=TRACKBALL, .id=TRACKBALL_DOWN},
    [](GUIManager* self) {
      self->get_active_window()->FocusNext(VERTICAL);
  });

  gui->bind_input_event(SGui::input_event_t{.type=TRACKBALL, .id=TRACKBALL_LEFT},
    [](GUIManager* self) {
      self->get_active_window()->FocusPrev(HORIZONTAL);
  });

  gui->bind_input_event(SGui::input_event_t{.type=TRACKBALL, .id=TRACKBALL_RIGHT},
    [](GUIManager* self) {
      self->get_active_window()->FocusPrev(HORIZONTAL);
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
