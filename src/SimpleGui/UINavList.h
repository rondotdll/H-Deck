#pragma once

#include <vector>

#include "UIComponent.h"
#include "UIContainer.h"
#include "UILabel.h"
#include "UIWindow.h"
#include "helper.h"
#include "types.h"

typedef std::pair<SGui::UILabel, SGui::UIWindow*> NavItem;

namespace SGui {

class UINavList : public UIContainer {
  std::vector<NavItem> items_;
 public:
  explicit UINavList(std::vector<NavItem> items) : UIContainer() {
    items_ = items;
  }

  // Add a new item (entry) to the NavList
  UINavList* AddItem(NavItem&& item);

  // Add a list of new items (entries) to the nav list
  UINavList* AddItems(std::vector<NavItem>&& items);

  void Draw() override;
};
}