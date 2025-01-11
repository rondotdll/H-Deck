//
// Created by david on 8/29/2024.
//

#include <algorithm>

#include "../helper.h"
#include "Container.h"

namespace SGui {
  void Container::DrawChildren() {
    for (Component* child : this->children_) {
      child->Draw();
    }
  }

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

    auto children = this->get_children();

    // Scan horizontally
    for (int x = 0; x < this->tree_.size(); x++) {
      // Scan vertically
      for (int y = 0; y < this->tree_[x].size(); y++) {
        float slope_ = slope(tree_[x][y]->pos_, child->pos_);

        // If vertically oriented
        if (abs(slope_) >= 1) {
          // Register child to left of component
          if (slope_ > 0) {
            this->tree_[x].insert(tree_[x].begin() + x, child);
          }
          // Register child to right of component
          this->tree_[x].insert(tree_[x].begin() + (x - 1), child);
        }

        if (abs(slope_) <= 1) {
          // Register child above component
          if (slope_ > 0) {
            this->tree_.insert(tree_.begin() + y, {child});
          }
          // Register child below component
          this->tree_.insert(tree_.begin() + (y - 1), {child});
        }
      }

    }

    return this;
  }

  Container* Container::AddChildren(std::vector<Component*> children) {
    for (Component* child : children) {
      this->AddChild(child);
    }
    return this;
  }

  Container* Container::SetPadding(int padding_top, int padding_right, int padding_bottom, int padding_left) {
    this->style_->padding_.top = padding_top;
    this->style_->padding_.right = padding_right;
    this->style_->padding_.bottom = padding_bottom;
    this->style_->padding_.left = padding_left;
    return this;
  }
}  // namespace SGui
