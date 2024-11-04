#include <algorithm>

#include "UIComponent.h"
#include "UIContainer.h"

namespace SGui {

  // Modify position to move the component into the bounds of its parent
  void UIComponent::MoveIntoParentBounds() {
    UIContainer* parent = static_cast<UIContainer*>(this->parent_);

    this->pos_.x += parent->pos_.x              // account for parent x position
                    + parent->padding_.left      // account for parent x padding
                    + parent->border_size_.left; // account for parent x border

    this->pos_.y += parent->pos_.y              // account for parent position
                  + parent->padding_.top       // account for parent padding
                  + parent->border_size_.top;  // account for parent border
  }


  // Resize the component to fill its parent
  void UIComponent::FillParent() {
    if (parent_ == nullptr)
      return;

    UIContainer* parent = static_cast<UIContainer*>(parent_);

    this->SetSize(parent->size_.x - (parent->padding_.left + parent->padding_.right) // account for X padding
                                 - (parent->border_size_.left + parent->border_size_.right), // Account for X border

                  parent->size_.y - (parent->padding_.top + parent->padding_.bottom) // Account for Y padding
                                 - (parent->border_size_.top + parent->border_size_.bottom) // Account for Y border
    );
  }



  // Align the component relative to its parent
  void UIComponent::AlignToParent(UIAlignment alignment) {
    if (parent_ == nullptr)
      return;

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