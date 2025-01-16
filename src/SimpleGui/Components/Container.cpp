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

  // Focus the next child component
  UIContainerFocusStatus Container::FocusNext() {
    // No children?
    if (this->children_.empty())
      return NO_CHILDREN;

    while (this->focused_child_index_ < children_.size() - 1) {
      if (this->children_[this->focused_child_index_]->isInput()) {
        this->focused_child_ = this->children_[this->focused_child_index_]->Focus();
        return SUCCESS;
        break;
      }

      this->focused_child_index_++;
    }
    return OUT_OF_BOUNDS;
  }

  // Focus the previous child component
  UIContainerFocusStatus Container::FocusPrev() {
    // No children?
    if (this->children_.empty())
      return NO_CHILDREN;

    // Iterate children following focused child
    while (this->focused_child_index_ > 0) {
      // Is this an input?
      if (this->children_[this->focused_child_index_]->isInput()) {
        this->focused_child_ = this->children_[this->focused_child_index_]->Focus();
        return SUCCESS;
      }

      this->focused_child_index_--;
    }
    return OUT_OF_BOUNDS;
  }

  // Focus the specified child component
  UIContainerFocusStatus Container::FocusChild(int index) {
    // No children?
    if (this->children_.size() == 0)
      return NO_CHILDREN;

    // Verify index is within bounds
    if (index >= 0 && index < this->children_.size()) {
      // Is this an input?
      if (this->children_[index]->isInput()) {
        this->focused_child_ = this->children_[index]->Focus();
        this->focused_child_index_ = index;
        return SUCCESS;
      }
      return DELINQUENT_CHILD;
    }
    return OUT_OF_BOUNDS;
  }

  // Focus the specified child component
  UIContainerFocusStatus Container::FocusChild(Component* child) {
    // No children?
    if (this->children_.size() == 0)
      return NO_CHILDREN;

    if (child->isInput()) {
      for (int i = 0; i < this->children_.size(); i++) {
        if (this->children_[i] == child) {
          this->focused_child_ = child->Focus();
          this->focused_child_index_ = i;
          return SUCCESS;
        }
      }
      return OUT_OF_BOUNDS;
    }
    return DELINQUENT_CHILD;
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
    // If empty, skip all logic
    if (this->children_.empty()) {
      this->children_.push_back(child);
      goto END;
    }

    int i = 0;

    switch (this->orientation_) {
      case HORIZONTAL: {
        // If relatively positioned, re-position the child to the parent
        if (!child->isAbsolute()) {
          child->MovePos(this->ContentWidth(), 0);
          this->content_size_.y += child->GetRenderedSize().y;
        }

        // Iterate through all children
        for (Component* c : this->children_) {
          // No duplicate children
          if (c == child) return this;

          if (c->x() > child->x()) {
            this->children_.insert(this->children_.begin() + i, child);
            goto END;
          }

          i += 1;
        }
        break;
      }

      case VERTICAL: {
        if (!child->isAbsolute()) {
          child->MovePos(0, this->ContentHeight());
          this->content_size_.y += child->GetRenderedSize().y;
        }

        for (Component* c : this->children_) {
          if (c == child) return this;

          if (c->y() > child->y()) {
            this->children_.insert(this->children_.begin() + i, child);
            goto END;
          }

          i += 1;
        }
        break;
      }
    }

    // If it's further down than everything else, add it to the end of the stack
    this->children_.push_back(child);

    END:
    child->SetParent(this);
    child->MoveIntoParentBounds();

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
