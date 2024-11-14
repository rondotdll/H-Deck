//
// Created by david on 8/29/2024.
//

#include <algorithm>

#include "helper.h"
#include "UIContainer.h"

namespace SGui {
  void UIContainer::DrawChildren() {
    for (UIComponent* child : this->children_) {
      child->Draw();
    }
  }

  UIContainer* UIContainer::AddChild(UIComponent* child) {
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
          this->content_size_.y += child->size_.y;
          break;
        case HORIZONTAL:
          child->MovePos(this->content_size_.x, 0);
          this->content_size_.x += child->size_.x;
          break;

        default:
          break;
      }
    }
    return this;
  }

  UIContainer* UIContainer::AddChildren(std::vector<UIComponent*> children) {
    for (UIComponent* child : children) {
      this->AddChild(child);
    }
    return this;
  }

  UIContainer* UIContainer::SetPadding(int padding_top, int padding_right, int padding_bottom, int padding_left) {
    this->padding_.top = padding_top;
    this->padding_.right = padding_right;
    this->padding_.bottom = padding_bottom;
    this->padding_.left = padding_left;
    return this;
  }
}  // namespace SGui
