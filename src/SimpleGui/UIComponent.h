#pragma once

#include "types.h"

namespace SGui {

// Base class for all UI components
// Stores position, size, and parent component
// (All components should inherit from this class)
class UIComponent {
 public:
  // int x_ = 0;  // x position
  // int y_ = 0;  // y position
  // int w_ = 0;  // width
  // int h_ = 0;  // height

  SGPoint pos_{0, 0};
  SGRect dim_{0, 0};

  bool focused_ = false; // focused state (unused)
  UIComponent* parent_ = nullptr;

  UIComponent() = default; // default constructor
  explicit UIComponent(SGPoint position, SGRect dimensions,
                       UIComponent* parent = nullptr)
      : pos_(position), dim_(dimensions), parent_(parent) {}

  // Draw the component
  virtual void Draw() = 0;

  // Align the component relative to its parent
  void AlignParent(UIAlignment alignment);

  // Set the position of the component
  UIComponent* SetPos(int x, int y);

  // Set the size of the component
  UIComponent* SetSize(int w, int h);

  // Set the parent of the component
  UIComponent* SetParent(UIComponent* parent);
};
}  // namespace SGui
