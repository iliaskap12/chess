
#ifndef MAINMENU_H
#define MAINMENU_H

#include "Menu.h"

class MainMenu : public Menu {

public:
  MainMenu();
  void draw() override;
  void update(float ms) override;
  static MenuOption createMenuOption(std::string message, float verticalPoint);
  void pressButton(const ButtonType &type) const override;
};

#endif // MAINMENU_H
