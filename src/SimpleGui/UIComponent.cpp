#include "UIComponent.h"

namespace SGui {

  // Align the component relative to its parent
  void UIComponent::AlignParent(UIAlignment alignment) {
    if (parent_ == nullptr)
      return;

    switch (alignment) {
      case TOP_LEFT:
        this->pos_->..x = 0;
        this->pos_->.y = 0;
        break;
      case TOP_CENTER:
        this->pos_->.x = (parent_->w_ - w_) / 2;
        this->pos_->.y = 0;
        break;
      case TOP_RIGHT:
        this->pos_->.x = parent_->w_ - w_;
        this->pos_->.y = 0;
        break;
      case MID_LEFT:
        this->pos_->.x = 0;
        this->pos_->.y = (parent_->h_ - h_) / 2;
        break;
      case MID_CENTER:
        this->pos_->.x = (parent_->w_ - w_) / 2;
        this->pos_->.y = (parent_->h_ - h_) / 2;
        break;
      case MID_RIGHT:
        this->pos_->x = parent_->w_ - w_;
        this->pos_->y = (parent_->h_ - h_) / 2;
        break;
      case BOTTOM_LEFT:
        this->x_ = 0;
        this->y_ = parent_->h_ - h_;
        break;
      case BOTTOM_CENTER:
        this->x_ = (parent_->w_ - w_) / 2;
        this->y_ = parent_->h_ - h_;
        break;
      case BOTTOM_RIGHT:
        this->x_ = parent_->w_ - w_;
        this->y_ = parent_->h_ - h_;
        break;
    }
  }

  // Set the position of the component
  UIComponent* UIComponent::SetPos(int x, int y) {
    this->x_ = x;
    this->y_ = y;
    return this;
  }

  // Set the size of the component
  UIComponent* UIComponent::SetSize(int w, int h) {
    this->w_ = w;
    this->h_ = h;
    return this;
  }

  // Set the parent of the component
  UIComponent* UIComponent::SetParent(UIComponent* parent) {
    this->parent_ = parent;
    return this;
  }
}