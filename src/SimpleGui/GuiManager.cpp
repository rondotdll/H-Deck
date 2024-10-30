// File: GuiManager.cpp

#include "GuiManager.h"

#include <vector>
#include <unordered_map>

#include "types.h"

namespace SGui {

  constexpr uint8_t DUAL_INPUT_FLAG = 0xC0; // 11000000

  // Poll the trackball for input
  void pollTrackballTask(GUIManager* instance) {

    while (true) {
      uint8_t tb_state = 0;

      // read up to 2 trackball inputs
      // First check the PRESS pin
      if (digitalRead(TRACKBALL_PRESS_P) == LOW) {
        // set the press bit to ON
        tb_state |= TRACKBALL_PRESS;
        // no directional inputs should take place if the trackball is pressed in.
        tb_state = DUAL_INPUT_FLAG;
      }

      // Then check the UP & DOWN pins
      if ((tb_state & DUAL_INPUT_FLAG) < DUAL_INPUT_FLAG && digitalRead(TRACKBALL_UP_P) == LOW) {
        // set the up bit to ON
        tb_state |= TRACKBALL_UP;
        // add 1 input to our DUAL_INPUT tracker portion
        tb_state += 0x40; // 01000000
      } else if ((tb_state & DUAL_INPUT_FLAG) < DUAL_INPUT_FLAG && digitalRead(TRACKBALL_DOWN_P) == LOW) {
        // set the down bit to ON
        tb_state |= TRACKBALL_DOWN;
        tb_state += 0x40;
      }

      // Finally check the LEFT & RIGHT pins
      if ((tb_state & DUAL_INPUT_FLAG) < DUAL_INPUT_FLAG && digitalRead(TRACKBALL_LEFT_P) == LOW) {
        tb_state |= TRACKBALL_LEFT;
        tb_state += 0x40;
      } else if ((tb_state & DUAL_INPUT_FLAG) < DUAL_INPUT_FLAG && digitalRead(TRACKBALL_RIGHT_P) == LOW) {
        tb_state |= TRACKBALL_RIGHT;
        tb_state += 0x40;
      }

      if (tb_state != 0) {
        instance->create_input_event({TRACKBALL, tb_state & ~DUAL_INPUT_FLAG});
      }

    }
  }

  void GUIManager::init() {
    self_ = this;

    // Verify pins are set up for input
    pinMode(TRACKBALL_UP_P, INPUT_PULLUP);
    pinMode(TRACKBALL_DOWN_P, INPUT_PULLUP);
    pinMode(TRACKBALL_LEFT_P, INPUT_PULLUP);
    pinMode(TRACKBALL_RIGHT_P, INPUT_PULLUP);
  }

  // Handles a single input_event_t from the input_queue
  handler_exception_t GUIManager::handle(input_event_t input) {
      if (input_handlers_.find(input) != input_handlers_.end()) {
        try {
          input_handlers_[input](this);
          return OK;
        } catch (...) {
          return BAD_HANDLER;
        }
      }
      return NO_HANDLER;
  }

  // Handles ALL inputs currently queued in the input_queue
  handler_exception_t GUIManager::handle_inputs() {
    for (auto i = input_queue_.begin(); i != input_queue_.end();) {
      handler_exception_t status = handle(*i);
      if (status) {
        return status;
      }
      input_queue_.erase(i);
      ++i;
    }
    return OK;
  }

  // Adds a window to the viewport
  void GUIManager::add_window(UIWindow* window) {
    this->viewport_.push_back(window);
    if (this->active_window_ == nullptr) {
      this->active_window_ = window;
    }
  }

  // Removes a window from the viewport
  void GUIManager::remove_window(UIWindow* window) {
    if (this->active_window_ == window) {
      this->active_window_ = nullptr;
    }
    this->viewport_.erase(std::remove(this->viewport_.begin(), this->viewport_.end(), window), this->viewport_.end());
  }

  // Sets the active window (window to be drawn
  void GUIManager::set_active_window(UIWindow* window) {
    this->active_window_ = window;
  }

  // Binds an in put event to a handler (void function pointer)
  // input: The input event to bind
  // handle_func: The handler function to bind to the input event
  void GUIManager::bind_input_event(input_event_t input, void* handle_func) {
    this->input_handlers_[input] = handle_func;


  }

  // Unbinds an input event from its respective handler
  // input: The input event to remove
  void GUIManager::unbind_input_event(input_event_t input) {
    this->input_handlers_.erase(input);
  }

  // Adds an input event to the input queue
  // input: The input event to add
  void GUIManager::create_input_event(input_event_t input) {
    this->input_queue_.push_back(input);
  }

  // Clears the input queue
  void GUIManager::clear_input_queue() {
    this->input_queue_.clear();
  }

  // Draws the Gui (active window)
  void GUIManager::draw() {
    active_window_->Draw();
  }
}
