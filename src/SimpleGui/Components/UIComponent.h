#pragma once

#include "../types.h"
#include "../UIStyle.h"
#include "../DefaultStyles.h"

namespace SGui {

// Base class for all UI components
// Stores position, size, and parent component
// (All components should inherit from this class)
class UIComponent {
private:
  bool isInput_ = false;
  bool absolute_ = false;  // positioning mode
public:
  UIPoint pos_{0, 0}; // 2D point representing position
  UIRect size_{0, 0}; // 2D point representing size

  UIStyle* style_ = nullptr;
  UIStyle* focused_style_ = nullptr;

  bool focused_ = false; // focused state (unused)
  UIComponent* parent_ = nullptr;

  UIComponent() = default; // default constructor
  explicit UIComponent(UIPoint position, UIRect dimensions, UIStyle* style = DEFAULT_STYLE, UIStyle* focused_style = DEFAULT_STYLE_FOCUSED,
                       UIComponent* parent = nullptr)
      : pos_(position), size_(dimensions), style_(style), focused_style_(focused_style), parent_(parent) {}

  // Draw the component
  virtual void Draw() = 0;

  // Get the rendered size of the component
  virtual UIRect GetRenderedSize() const { return size_; }

  bool isInput() const {return isInput_;}
  bool isAbsolute() const {return absolute_;}

  // Enable or disable absolute positioning for the component
  UIComponent* absolute(bool enabled = true);

  // Modify position to move the component into the bounds of its parent
  UIComponent* MoveIntoParentBounds();

  // Resize the component to fill its parent
  UIComponent* FillParent();

  // Align the component relative to its parent
  UIComponent* AlignToParent(UIAlignment alignment);

  // Set the position of the component
  UIComponent* SetPos(int x, int y);

  // Moves the position of the component
  // (Similar to set, but adds or subtracts relative to the current position)
  UIComponent* MovePos(int x, int y);

  // Set the size of the component
  UIComponent* SetSize(int w, int h);

  // Set the parent of the component
  UIComponent* SetParent(UIComponent* parent);
};
}  // namespace SGui
