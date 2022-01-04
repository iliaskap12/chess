
#ifndef MENU_H
#define MENU_H

#include <unordered_map>
#include "Drawable.h"
#include "Updateable.h"
#include "MenuOption.h"
#include "ButtonType.h"

class Menu : public Drawable, public Updateable {
  std::unordered_map<ButtonType, MenuOption> options { std::unordered_map<ButtonType, MenuOption>() };

public:
  Menu();
  void draw() override = 0;
  void update(float ms) override = 0;
  void addOption(const MenuOption& option, ButtonType buttonType);
  const MenuOption &getMenuOption(ButtonType buttonType);
  const std::unordered_map<ButtonType, MenuOption> &getMenuOptions() const;
};

#endif // MENU_H
