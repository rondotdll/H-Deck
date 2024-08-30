//
// Created by david on 8/29/2024.
//

#include "UIContainer.h"

namespace SGui {
  void UIContainer::DrawChildren() {
    for (UIComponent* child : children_) {
      child->Draw();
    }
  }

  UIContainer* UIContainer::AddChild(UIComponent* child) {
    children_.push_back(child);
    child->SetParent(this);
    return this;
  }

  UIContainer* UIContainer::AddChildren(std::vector<UIComponent*>* children) {
    for (UIComponent* child : *children) {
      this->children_.push_back(child);
      child->SetParent(this);
    }
    return this;
  }

  UIContainer* UIContainer::SetPadding(int padding_x, int padding_y) {
    this->px_ = padding_x;
    this->py_ = padding_y;
    return this;
  }
}  // namespace SGui
