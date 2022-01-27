#ifndef MENUOPTION_H
#define MENUOPTION_H

#include <hud/HUD.h>
#include <sounds/ClickSound.h>
#include "Rectangle.h"

class MenuOption {
  HUD optionHUD;
  Rectangle button;
  ClickSound clickSound{ClickSound()};

public:
  explicit MenuOption(HUD hud);
  [[nodiscard]] HUD getMessage() const;
  [[nodiscard]] Rectangle getButton() const;
  void playSound() const;
};

#endif // MENUOPTION_H
