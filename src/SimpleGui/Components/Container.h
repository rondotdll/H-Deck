#pragma once

#include <utility>
#include <vector>

#include "Component.h"
#include "../DefaultStyles.h"

namespace SGui {


// Expanded UIComponent class for all NESTING UI components
// Stores horizontal padding, vertical padding, and child components
// (All NESTING components should inherit from this class)
class Container : public Component {
protected:
  ComponentList children_ = {};

public:
  UIOrientation orientation_ = VERTICAL;
  UIRect content_size_ {0, 0};

  Container() = default; // default constructor
  explicit Container(ComponentList children)
      : Component(), children_(std::move(children)) {}

  // Returns a list of pointers to recursive children
  // ***Starts with the component itself
  ComponentList Children() override;

  // Returns a list of pointers to direct children (not recursive)
  ComponentList DirectChildren() const { return children_; }

  // Draw just the children of the component (not the component itself)
  void DrawChildren();

  // Set the padding of the container
  virtual Container* SetPadding(int padding_top, int padding_right, int padding_bottom, int padding_left);

  // Add a child component to the container
  virtual Container* AddChild(Component* child);

  // Add multiple child components to the container
  virtual Container* AddChildren(std::vector<Component*> children);

};
}  // namespace SGui
