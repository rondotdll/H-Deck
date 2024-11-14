//
// Created by david on 11/14/2024.
//

#include "UINavList.h"

namespace SGui {

  // Add a new item (entry) to the NavList
  UINavList* UINavList::AddItem(NavItem&& item) {
    items_.push_back(std::move(item));
    return this;
  }

  // Add a list of new items (entries) to the nav list
  UINavList* UINavList::AddItems(std::vector<NavItem>&& items) {
    items_.insert(items_.end(),
      std::make_move_iterator(items.begin()),
      std::make_move_iterator(items.end())
      );
    return this;
  }

}