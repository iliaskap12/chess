#ifndef MENUOPTION_H
#define MENUOPTION_H

#include <hud/HUD.h>
#include <sounds/ClickSound.h>
#include "Rectangle.h"

class MenuOption {
  std::shared_ptr<HUD> optionHUD;
  std::shared_ptr<Rectangle> button{std::make_shared<Rectangle>()};
  ClickSound clickSound{ClickSound()};

public:
  explicit MenuOption(const HUD &hud);
  [[nodiscard]] std::weak_ptr<HUD> getMessage() const;
  [[nodiscard]] std::weak_ptr<Rectangle> getButton() const;
  void playSound() const;
};

#endif // MENUOPTION_H
