#pragma once

#include <SPI.h>
#include <TFT_eSPI.h>
#include <Wire.h>
#include <utility>
#include <vector>

#include "helper.h"
#include "types.h"
#include "pins.h"

#include "UIComponent.h"
#include "UIContainer.h"
#include "UILabel.h"
#include "UIWindow.h"

#include "GuiManager.h"

namespace SGui {
  // Initialize the TFT display
  // returns a pointer to the TFT_eSPI object
  GUIManager* Init();
};
