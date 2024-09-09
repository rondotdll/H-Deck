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
    if (v_includes(this->children_, child))
      return this;

    this->children_.push_back(child);
    child->SetParent(this);
    return this;
  }

  UIContainer* UIContainer::AddChildren(std::vector<UIComponent*>* children) {
    for (UIComponent* child : *children) {
      if (v_includes(this->children_, child))
        continue;

      this->children_.push_back(child);
      child->SetParent(this);
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
