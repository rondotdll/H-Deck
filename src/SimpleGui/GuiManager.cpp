// File: GuiManager.cpp

#include "GuiManager.h"

#include <vector>
#include <unordered_map>

#include "types.h"

namespace SGui {

  // Poll the trackball for input
  [[noreturn]] void pollTrackballTask(GUIManager* instance) {
    while (true) {
      uint8_t tb_state = 0;

      // read up to 2 trackball inputs
      // First check the PRESS pin
      tb_state |= digitalRead(TRACKBALL_PRESS_P) * TRACKBALL_PRESS;
      if (tb_state) goto end; // no dual inputs

      // Then check the UP & DOWN pins
      tb_state |= digitalRead(TRACKBALL_UP_P) * TRACKBALL_UP;
      tb_state |= digitalRead(TRACKBALL_DOWN_P) * TRACKBALL_DOWN;
      if (tb_state) goto end;

      // Then check the LEFT & RIGHT pins
      tb_state |= digitalRead(TRACKBALL_LEFT_P) * TRACKBALL_LEFT;
      tb_state |= digitalRead(TRACKBALL_RIGHT_P) * TRACKBALL_RIGHT;

      end:
      // verify no dual inputs
      if (tb_state && (tb_state & (tb_state - 1)) == 0) {
        instance->create_input_event({TRACKBALL, tb_state});
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
      uint16_t id = input.flatten();

      if (input_handlers_.find(id) != input_handlers_.end()) {
        try {
          input_handlers_[id](self_); // <- this is so fucking cursed lmfao
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
  void GUIManager::bind_input_event(input_event_t input, void (*handle_func)(GUIManager*)) {
    this->input_handlers_[input.flatten()] = handle_func;
  }

  // Unbinds an input event from its respective handler
  // input: The input event to remove
  void GUIManager::unbind_input_event(input_event_t input) {
    this->input_handlers_.erase(input.flatten());
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
