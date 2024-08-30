#pragma once

#include <utility>
#include <vector>

#include "UIComponent.h"

namespace SGui {
// Expanded UIComponent class for all NESTING UI components
// Stores horizontal padding, vertical padding, and child components
// (All NESTING components should inherit from this class)
class UIContainer : public UIComponent {
 private:
  std::vector<UIComponent*> children_;
  int px_ = 0; // horizontal padding
  int py_ = 0; // vertical padding

 public:
  explicit UIContainer() : UIComponent() {
    this->children_ = {};

    this->px_ = 0;
    this->py_ = 0;
  };

  // Draw just the children of the component (not the component itself)
  void DrawChildren();

  // Set the padding of the container
  virtual UIContainer* SetPadding(int padding_x, int padding_y);

  // Add a child component to the container
  virtual UIContainer* AddChild(UIComponent* child);

  // Add multiple child components to the container
  virtual UIContainer* AddChildren(std::vector<UIComponent*>* children);

};
}  // namespace SGui
