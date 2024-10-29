#include "SimpleGui.h"

namespace SGui {
  // Handles a single input_event_t from the input_queue
  void Gui::handle(input_event_t input) {
      if (input_handlers_.find(input) != input_handlers_.end()) {
        input_handlers_[input](this);
      }
  }

  // Handles ALL inputs currently queued in the input_queue
  void Gui::handle_inputs() {
    for (auto i = input_queue_.begin(); i != input_queue_.end();) {
      handle(*i);
      input_queue_.erase(i);
      ++i;
    }
  }

  // Adds a window to the viewport
  void Gui::add_window(UIWindow* window) {
    this->viewport_.push_back(window);
    if (this->active_window_ == nullptr) {
      this->active_window_ = window;
    }
  }

  // Removes a window from the viewport
  void Gui::remove_window(UIWindow* window) {
    if (this->active_window_ == window) {
      this->active_window_ = nullptr;
    }
    this->viewport_.erase(std::remove(this->viewport_.begin(), this->viewport_.end(), window), this->viewport_.end());
  }

  // Sets the active window (window to be drawn
  void Gui::set_active_window(UIWindow* window) {
    this->active_window_ = window;
  }

  // Binds an in put event to a handler (void function pointer)
  // input: The input event to bind
  // handle_func: The handler function to bind to the input event
  void Gui::bind_input_event(input_event_t input, void* handle_func) {
    this->input_handlers_[input] = handle_func;

    // if the input type is basic, we need to attachInterupt it's ID (pin) to the handle_func
    if (input.type == BASIC) {
      attachInterrupt(input.id, isr_wrapper_function, RISING);
    }
  }

  // Unbinds an input event from its respective handler
  // input: The input event to remove
  void Gui::unbind_input_event(input_event_t input) {
    this->input_handlers_.erase(input);
  }

  // Adds an input event to the input queue
  // input: The input event to add
  void Gui::create_input_event(input_event_t input) {
    this->input_queue_.push_back(input);
  }

  // Clears the input queue
  void Gui::clear_input_queue() {
    this->input_queue_.clear();
  }

  // Draws the Gui (active window)
  void Gui::draw() {
    active_window_->Draw();
  }
}