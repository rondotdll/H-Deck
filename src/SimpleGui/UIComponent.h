#pragma once

#include "types.h"

namespace SGui {

// Base class for all UI components
// Stores position, size, and parent component
// (All components should inherit from this class)
class UIComponent {
 public:

  SGPoint pos_{0, 0}; // 2D point representing position
  SGRect size_{0, 0}; // 2D point representing size

  bool focused_ = false; // focused state (unused)
  UIComponent* parent_ = nullptr;

  UIComponent() = default; // default constructor
  explicit UIComponent(SGPoint position, SGRect dimensions,
                       UIComponent* parent = nullptr)
      : pos_(position), size_(dimensions), parent_(parent) {}

  // Draw the component
  virtual void Draw() = 0;

  // Modify position to move the component into the bounds of its parent
  void MoveIntoParentBounds();

  // Resize the component to fill its parent
  void FillParent();

  // Align the component relative to its parent
  void AlignToParent(UIAlignment alignment);

  // Set the position of the component
  UIComponent* SetPos(int x, int y);

  // Set the size of the component
  UIComponent* SetSize(int w, int h);

  // Set the parent of the component
  UIComponent* SetParent(UIComponent* parent);
};
}  // namespace SGui
