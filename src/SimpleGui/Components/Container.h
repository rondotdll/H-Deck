#pragma once

#include <utility>
#include <vector>

#include "Component.h"
#include "../DefaultStyles.h"

namespace SGui {

typedef std::vector<ComponentList> navtree_t;

// Expanded UIComponent class for all NESTING UI components
// Stores horizontal padding, vertical padding, and child components
// (All NESTING components should inherit from this class)
class Container : public Component {
private:
  ComponentList children_ = {};
  navtree_t tree_ = {};

public:
  UIOrientation orientation_ = VERTICAL;
  UIRect content_size_ {0, 0};

  Container() = default; // default constructor
  explicit Container(ComponentList children)
      : Component(), children_(std::move(children)) {}

  ComponentList get_children() override {
    ComponentList output = { this };
    for (Component* c : children_ ) {
      output.push_back(c);
      for (Component* c2 : c->get_children()) {
        output.push_back(c2);
      }
    }

    return output;
  }

  ComponentList get_direct_children() const { return children_; }

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
