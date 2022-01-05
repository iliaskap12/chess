
#ifndef OPENINGSCREEN_H
#define OPENINGSCREEN_H

#include "Screen.h"
#include "MainMenu.h"
#include <memory>

class OpeningScreen : public Screen {
  std::unique_ptr<Menu> mainMenu = std::make_unique<MainMenu>();
  std::optional<HUD> welcomeMessage;

public:
  OpeningScreen();
  void draw() override;
  void update(float ms) override;
};

#endif // OPENINGSCREEN_H
