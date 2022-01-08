#ifndef MENUOPTION_H
#define MENUOPTION_H

#include "hud/HUD.h"
#include "Rectangle.h"

class MenuOption {
  HUD optionHUD;
  Rectangle button;

public:
  explicit MenuOption(HUD hud);
  [[nodiscard]] HUD getMessage() const;
  [[nodiscard]] Rectangle getButton() const;
};

#endif // MENUOPTION_H
