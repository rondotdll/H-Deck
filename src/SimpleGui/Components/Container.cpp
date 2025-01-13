//
// Created by david on 8/29/2024.
//

#include <algorithm>

#include "../helper.h"
#include "Container.h"

namespace SGui {

  // Returns a list of pointers to recursive children
  // ***Starts with the component itself
  ComponentList Container::Children() {
    ComponentList output = { this };

    if (this->children_.empty())
      return output;

    for (Component* c : this->children_ ) {
      output.push_back(c);
      for (Component* c2 : c->Children()) {
        if (c2 == nullptr || c2 == c) break;
        output.push_back(c2);
      }
    }

    return output;
  }

  // Returns a list of pointers to direct children (not recursive)
  void Container::DrawChildren() {
    for (Component* child : this->children_) {
      child->Draw();
    }
  }

  // Set the padding of the container
  Container* Container::SetPadding(int padding_top, int padding_right, int padding_bottom, int padding_left) {
    this->style_->padding_.top = padding_top;
    this->style_->padding_.right = padding_right;
    this->style_->padding_.bottom = padding_bottom;
    this->style_->padding_.left = padding_left;
    return this;
  }

  // Add a child component to the container
  Container* Container::AddChild(Component* child) {
     // No duplicate children
    if (v_includes(this->children_, child))
      return this;

    this->children_.push_back(child);
    child->SetParent(this);
    child->MoveIntoParentBounds();

    // Check if child has rel positioning
    if (!child->isAbsolute()) {
      switch(this->orientation_) {
        case VERTICAL:
          child->MovePos(0, this->content_size_.y);
          this->content_size_.y += child->GetRenderedSize().y;
          break;
        case HORIZONTAL:
          child->MovePos(this->content_size_.x, 0);
          this->content_size_.x += child->GetRenderedSize().x;
          break;

        default:
          break;
      }
    }
    return this;
  }

  // Add multiple child components to the container
  Container* Container::AddChildren(ComponentList children) {
    for (Component* child : children) {
      Serial.printf("Adding child %p to container\n\r", child);
      this->AddChild(child);
    }
    return this;
  }
}  // namespace SGui
