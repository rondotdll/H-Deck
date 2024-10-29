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
  typedef std::vector<UIWindow*> viewport_t;

  // namespace SGui
  class Gui {
  private:
    UIComponent* focused_ = nullptr;
    UIWindow* active_window_ = nullptr;
    viewport_t viewport_ = {};
    std::vector<input_event_t> input_stack_ = {};
    std::unordered_map<input_event_t, void*> input_handlers_;

  public:

    Gui(); // default constructor

    void handle(input_event_t input);
    void handle_inputs();

    UIComponent* getFocused() const { return focused_;}
    UIWindow* getActiveWindow() const { return active_window_;}
    viewport_t getViewport() const {return viewport_;}

    void addWindow(UIWindow* window);
    void removeWindow(UIWindow* window);
    void setActiveWindow(UIWindow* window);

    void bindInput(input_event_t input, void* handler);
    void removeInput(input_event_t input);

    void addInputToStack(input_event_t input);
    void clearInputStack();

    void draw();

  };
};
