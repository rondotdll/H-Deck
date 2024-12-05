#include <algorithm>

#include "UIComponent.h"
#include "UIContainer.h"

namespace SGui {

  // Modify position to move the component into the bounds of its parent
  UIComponent* UIComponent::MoveIntoParentBounds() {
    UIContainer* parent = static_cast<UIContainer*>(this->parent_);

    this->pos_.x += parent->pos_.x              // account for parent x position
                    + parent->style_->padding_.left       // account for parent x padding
                    + parent->style_->border_thickness_;  // account for parent x border

    this->pos_.y += parent->pos_.y              // account for parent position
                    + parent->style_->padding_.top        // account for parent padding
                    + parent->style_->border_thickness_;  // account for parent border

    return this;
  }


  // Resize the component to fill its parent
  UIComponent* UIComponent::FillParent() {
    if (parent_ == nullptr)
      return this;

    auto* parent = static_cast<UIContainer*>(parent_);

    this->SetSize(parent->size_.x - (parent->style_->padding_.left + parent->style_->padding_.right) // account for X padding
                                 - (2 * parent->style_->border_thickness_), // Account for X border

                  parent->size_.y - (parent->style_->padding_.top + parent->style_->padding_.bottom) // Account for Y padding
                                 - (2 * parent->style_->border_thickness_) // Account for Y border
    );

    return this;
  }

  UIComponent* UIComponent::absolute(bool enabled) {
    this->absolute_ = enabled;
    if (!this->absolute_) {
      this->SetPos(0,0);
      this->MoveIntoParentBounds(); // re-assign its relative position
    }
    return this;
  }

  // Align the component relative to its parent
  UIComponent* UIComponent::AlignToParent(UIAlignment alignment) {
    if (parent_ == nullptr)
      return this;

    switch (alignment) {
      case TOP_LEFT:
        this->pos_.x = 0;
        this->pos_.y = 0;
        break;
      case TOP_CENTER:
        this->pos_.x = (parent_->size_.x - this->size_.x) / 2;
        this->pos_.y = 0;
        break;
      case TOP_RIGHT:
        this->pos_.x = parent_->size_.x - this->size_.x;
        this->pos_.y = 0;
        break;
      case MID_LEFT:
        this->pos_.x = 0;
        this->pos_.y = (parent_->size_.y - this->size_.y) / 2;
        break;
      case MID_CENTER:
        this->pos_.x = (parent_->size_.x - this->size_.x) / 2;
        this->pos_.y = (parent_->size_.y - this->size_.y) / 2;
        break;
      case MID_RIGHT:
        this->pos_.x = parent_->size_.x - this->size_.x;
        this->pos_.y = (parent_->size_.y - this->size_.y) / 2;
        break;
      case BOTTOM_LEFT:
        this->pos_.x = 0;
        this->pos_.y = parent_->size_.y - size_.y;
        break;
      case BOTTOM_CENTER:
        this->pos_.x = (parent_->size_.x - this->size_.x) / 2;
        this->pos_.y = parent_->size_.y - this->size_.y;
        break;
      case BOTTOM_RIGHT:
        this->pos_.x = parent_->size_.x - this->size_.x;
        this->pos_.y = parent_->size_.y - this->size_.y;
        break;
    }
    return this;
  }

  // Set the position of the component
  UIComponent* UIComponent::SetPos(int x, int y) {
    this->pos_.x = x;
    this->pos_.y = y;
    return this;
  }

  UIComponent* UIComponent::MovePos(int x, int y) {
    this->pos_.x += x;
    this->pos_.y += y;
    return this;
  }

  // Set the size of the component
  UIComponent* UIComponent::SetSize(int w, int h) {
    this->size_.x = w;
    this->size_.y = h;
    return this;
  }

  // Set the parent of the component
  UIComponent* UIComponent::SetParent(UIComponent* parent) {
    this->parent_ = parent;

    return this;
  }
}