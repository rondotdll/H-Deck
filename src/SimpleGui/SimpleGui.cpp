#include "SimpleGui.h"

namespace SGui {
  // Handle a single input event
  void Gui::handle(input_event_t input) {
      if (input_handlers_.find(input) != input_handlers_.end()) {
        input_handlers_[input]();
      }
  }

  // Handle all inputs in the input stack
  void Gui::handle_inputs() {
    for (auto i = input_stack_.begin(); i != input_stack_.end();) {
      handle(*i);
      input_stack_.erase(i);
      i++;
    }
  }

    // Add a window to the viewport
    void Gui::addWindow(UIWindow* window) {
      this->viewport_.push_back(window);
      if (this->active_window_ == nullptr) {
        this->active_window_ = window;
      }
    }

    // Remove a window from the viewport
    void Gui::removeWindow(UIWindow* window) {
      if (this->active_window_ == window) {
        this->active_window_ = nullptr;
      }
      this->viewport_.erase(std::remove(this->viewport_.begin(), this->viewport_.end(), window), this->viewport_.end());
    }

    // Set the active window
    void Gui::setActiveWindow(UIWindow* window) {
      this->active_window_ = window;
    }

    // Bind an input event to a handler
    // input: The input event to bind
    // handle_func: The handler function to bind to the input event
    void Gui::bindInput(input_event_t input, void* handle_func) {
      this->input_handlers_[input] = handle_func;
    }

    // Remove an input event from the input handlers
    // input: The input event to remove
    void Gui::removeInput(input_event_t input) {
      this->input_handlers_.erase(input);
    }

    // Add an input event to the input stack
    // input: The input event to add
    void Gui::addInputToStack(input_event_t input) {
      this->input_stack_.push_back(input);
    }

    // Clear the input stack
    void Gui::clearInputStack() {
      this->input_stack_.clear();
    }

    // Draw the GUI
    void Gui::draw() {
      active_window_->Draw();
    }
}