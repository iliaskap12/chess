#ifndef MENUOPTION_H
#define MENUOPTION_H

#include "hud/HUD.h"

class MenuOption {
  HUD optionHUD;

public:
  explicit MenuOption(HUD hud);
  [[nodiscard]] HUD getMessage() const;
  [[nodiscard]] bool clicked(const float &mouseHorizontalPoint, const float &mouseVerticalPoint) const;
};

#endif // MENUOPTION_H
