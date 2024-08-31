#include "UIComponent.h"

namespace SGui {

  // Align the component relative to its parent
  void UIComponent::AlignParent(UIAlignment alignment) {
    if (parent_ == nullptr)
      return;

    switch (alignment) {
      case TOP_LEFT:
        this->pos_.x = 0;
        this->pos_.y = 0;
        break;
      case TOP_CENTER:
        this->pos_.x = (parent_->dim_.x - this->dim_.x) / 2;
        this->pos_.y = 0;
        break;
      case TOP_RIGHT:
        this->pos_.x = parent_->dim_.x - this->dim_.x;
        this->pos_.y = 0;
        break;
      case MID_LEFT:
        this->pos_.x = 0;
        this->pos_.y = (parent_->dim_.y - this->dim_.y) / 2;
        break;
      case MID_CENTER:
        this->pos_.x = (parent_->dim_.x - this->dim_.x) / 2;
        this->pos_.y = (parent_->dim_.y - this->dim_.y) / 2;
        break;
      case MID_RIGHT:
        this->pos_.x = parent_->dim_.x - this->dim_.x;
        this->pos_.y = (parent_->dim_.y - this->dim_.y) / 2;
        break;
      case BOTTOM_LEFT:
        this->pos_.x = 0;
        this->pos_.y = parent_->dim_.y - dim_.y;
        break;
      case BOTTOM_CENTER:
        this->pos_.x = (parent_->dim_.x - this->dim_.x) / 2;
        this->pos_.y = parent_->dim_.y - this->dim_.y;
        break;
      case BOTTOM_RIGHT:
        this->pos_.x = parent_->dim_.x - this->dim_.x;
        this->pos_.y = parent_->dim_.y - this->dim_.y;
        break;
    }
  }

  // Set the position of the component
  UIComponent* UIComponent::SetPos(int x, int y) {
    this->pos_.x = x;
    this->pos_.y = y;
    return this;
  }

  // Set the size of the component
  UIComponent* UIComponent::SetSize(int w, int h) {
    this->dim_.x = w;
    this->dim_.y = h;
    return this;
  }

  // Set the parent of the component
  UIComponent* UIComponent::SetParent(UIComponent* parent) {
    this->parent_ = parent;
    return this;
  }
}