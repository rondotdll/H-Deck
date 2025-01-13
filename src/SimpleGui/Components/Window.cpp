//
// Created by david on 8/24/2024.
//

#include "Window.h"

namespace SGui {
  // Set the title of the window
  Window* Window::SetTitle(String title) {
    this->title_ = title;
    return this;
  }

  // Set the color of the window
  Window* Window::SetColor(UIColor color) {
    this->style_->SetBorderColor(color);
    return this;
  }

  // Set the padding of the container (accounts for window border and title bar)
  Container* Window::SetPadding(int padding_top, int padding_right, int padding_bottom, int padding_left) {
    this->style_->padding_.top = padding_top + this->title_padding.top + this->title_padding.bottom + tft.fontHeight();
    this->style_->padding_.right = padding_right;
    this->style_->padding_.bottom = padding_bottom;
    this->style_->padding_.left = padding_left;
    return this;
  }

  // Focus next component in the specified direction
  void Window::FocusNext(UIOrientation direction){
    // focused x coordinate
    uint16_t x = this->focused_pos_.x;
    // focused y coordinate
    uint16_t y = this->focused_pos_.y;
    switch (direction) {
      case HORIZONTAL: {
        if (x == (this->tree_.size() - 1)) return;

        this->focused_->SetFocus(false); // un-focus previously focused
        this->focused_ = this->tree_[this->focused_pos_.x + 1][this->focused_pos_.y]->SetFocus();
        this->focused_pos_ = { x++, y }; // dumbass compiler won't let me do `x + 1`
        break;
      }
      case VERTICAL: {
        // do nothing if already at last item
        if (y == (this->tree_[x].size() - 1)) return;

        this->focused_->SetFocus(false); // un-focus previously focused
        this->focused_ = this->tree_[x][y + 1]->SetFocus();
        this->focused_pos_ = { x, y++ };
        break;
      }
    }
  }

  // Focus previous component in the specified direction
  void Window::FocusPrev(UIOrientation direction){
    // focused x coordinate
    uint16_t x = this->focused_pos_.x;
    // focused y coordinate
    uint16_t y = this->focused_pos_.y;
    switch (direction) {
      case HORIZONTAL: {
        if (x == (this->tree_.size() - 1)) return;

        this->focused_->SetFocus(false); // un-focus previously focused
        this->focused_ = this->tree_[this->focused_pos_.x - 1][this->focused_pos_.y]->SetFocus();
        this->focused_pos_ = { x--, y }; // dumbass compiler won't let me do `x - 1`
        break;
      }
      case VERTICAL: {
        // do nothing if already at last item
        if (y == (this->tree_[x].size() - 1)) return;

        this->focused_->SetFocus(false); // un-focus previously focused
        this->focused_ = this->tree_[x][y - 1]->SetFocus();
        this->focused_pos_ = { x, y-- };
        break;
      }
    }
  }

  // Add a child component to the window
  Container* Window::AddChild(Component* child) {
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

    auto sub_children = child->Children();
    sub_children.erase(sub_children.begin()); // remove the child from the list

    if (sub_children.empty()) {
      return this;
    }

    for (Component* c : sub_children) {
      if (!c->isInput()) continue;

      // Account for empty tree
      if (this->tree_.empty()) {
        this->tree_.push_back({c});
        this->focused_ = c;
        this->focused_pos_ = {0, 0};
        return this;
      }

      // Scan horizontally
      for (int x = 0; x <= this->tree_.size(); x++) {
        // Scan vertically
        for (int y = 0; y <= this->tree_[x].size(); y++) {

          float slope_ = slope(tree_[x][y]->pos_, c->pos_);

          // If vertically oriented
          if (abs(slope_) >= 1) {
            // Register child to left of component
            if (slope_ > 0) {
              this->tree_[x].insert(tree_[x].begin() + x, c);
              goto UPDATE_FOCUSED;
            }
            // Register child to right of component
            this->tree_[x].insert(tree_[x].begin() + (x - 1), c);
            goto UPDATE_FOCUSED;
          }

          if (slope_ > 0) {
            this->tree_.insert(tree_.begin() + y, {c});
            goto UPDATE_FOCUSED;
          }
          // Register child below component
          this->tree_.insert(tree_.begin() + (y - 1), {c});

          UPDATE_FOCUSED:
            if (this->focused_pos_.y == y) {
              this->focused_pos_.y += 1;
            }
          if (this->focused_pos_.x == x) {
            this->focused_pos_.x += 1;
          }
          return this;
        }
      }
    }
    return this;
  }

  // Draw the window and its children
  void Window::Draw() {
    // If the window is inside a container, adjust its position accordingly.
    if (this->parent_ != nullptr) {
      this->MoveIntoParentBounds();
    }

    tft.drawRect(this->pos_.x, this->pos_.y, this->size_.x, this->size_.y, this->style_->border_color_);
    tft.setTextColor(this->style_->foreground_.Compress());

    // If title isn't null, draw the title bar
    if (title_ != nullptr && title_ != "") {
      tft.fillRect(this->pos_.x,
                   this->pos_.y,
                   this->size_.x,
                   tft.fontHeight() + (this->title_padding.bottom + this->title_padding.top),
                   this->style_->border_color_);  // Title bar separator
      tft.drawString(title_, this->pos_.x + this->title_padding.left, this->pos_.y + this->title_padding.top);
    }

    DrawChildren();
  }

}  // namespace SGui
