#pragma once

#include <utility>
#include <vector>

#include "UIComponent.h"

namespace SGui {
// Expanded UIComponent class for all NESTING UI components
// Stores horizontal padding, vertical padding, and child components
// (All NESTING components should inherit from this class)
class UIContainer : public UIComponent {
 public:
  UIOrientation orientation_ = VERTICAL;
  std::vector<UIComponent*> children_ = {};
  SGBorderSize border_size_ {1, 1, 1, 1};
  UIBoxSpacing padding_ {0, 0, 0, 0};
  SGRect content_size_ {0, 0};

  UIContainer() = default; // default constructor
  explicit UIContainer(UIBoxSpacing padding, SGBorderSize border_size, std::vector<UIComponent*> children)
      : UIComponent(), border_size_(border_size), padding_(padding), children_(std::move(children)) {}

  // Draw just the children of the component (not the component itself)
  void DrawChildren();

  // Set the padding of the container
  virtual UIContainer* SetPadding(int padding_top, int padding_right, int padding_bottom, int padding_left);

  // Add a child component to the container
  virtual UIContainer* AddChild(UIComponent* child);

  // Add multiple child components to the container
  virtual UIContainer* AddChildren(std::vector<UIComponent*> children);

};
}  // namespace SGui
