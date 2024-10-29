#pragma once

#include <SPI.h>
#include <TFT_eSPI.h>
#include <Wire.h>
#include <utility>
#include <vector>

#include "helper.h"
#include "types.h"
#include "init.h"

#include "UIComponent.h"
#include "UIContainer.h"
#include "UILabel.h"
#include "UIWindow.h"

namespace SGui {

  void pollTrackballTask(Gui param) {
    while (true) {
      // Poll the trackball
      if (digitalRead(TRACKBALL_LEFT_P) == LOW) {
        param.create_input_event({BASIC, TRACKBALL_LEFT});
      }
      if (digitalRead(TRACKBALL_RIGHT_P) == LOW) {
        param.create_input_event({BASIC, TRACKBALL_RIGHT});
      }
      if (digitalRead(TRACKBALL_UP_P) == LOW) {
        param.create_input_event({BASIC, TRACKBALL_UP});
      }
      if (digitalRead(TRACKBALL_DOWN_P) == LOW) {
        param.create_input_event({BASIC, TRACKBALL_DOWN});
      }
      if (digitalRead(TRACKBALL_PRESS_P) == LOW) {
        param.create_input_event({BASIC, TRACKBALL_PRESS});
      }
      delay(10);
    }
  }


  typedef std::vector<UIWindow*> viewport_t;

  // namespace SGui
  class Gui {
  private:
    UIComponent* focused_ = nullptr;
    UIWindow* active_window_ = nullptr;
    viewport_t viewport_ = {};
    std::vector<input_event_t> input_queue_ = {};
    std::unordered_map<input_event_t, void*> input_handlers_;

    static Gui* self_;
  public:

    Gui(); // default constructor

    // Initialize the Gui (this MUST be called before use, or inputs will not function)
    void init() {
      self_ = this;


    }

    // Handles a single input_event_t from the input_queue
    void handle(input_event_t input);
    // Handles ALL inputs currently queued in the input_queue
    void handle_inputs();

    // Returns pointer to the component that is currently input focused
    UIComponent* get_focused_component() const { return focused_;}
    // Returns pointer to the active window
    UIWindow* get_active_window() const { return active_window_;}
    // Returns the current viewport (vector of pointers to each added window)
    viewport_t get_viewport() const {return viewport_;}
    // Returns pointer to the current input queue
    const std::vector<input_event_t>* get_input_queue() const {return &input_queue_;}

    // Adds a window to the viewport
    void add_window(UIWindow* window);
    // Removes a window from the viewport
    void remove_window(UIWindow* window);
    // Sets the active window (window to be drawn)
    void set_active_window(UIWindow* window);

    // Binds an input event to a handler (void function pointer)
    // input: The input event to bind
    // handler: The handler function to bind to the input event
    void bind_input_event(input_event_t input, void* handler);
    // Unbinds an input event from its respective handler
    // input: The input event to remove
    void unbind_input_event(input_event_t input);

    // Adds an input event to the input queue
    // input: The input event to add
    void create_input_event(input_event_t input);
    // Clears the input queue
    void clear_input_queue();


    // Draws the Gui (active window)
    void draw();

  };
};
