#ifndef INGAMEMENU_H
#define INGAMEMENU_H

#include "Menu.h"

class InGameMenu : public Menu {

public:
  InGameMenu();
  void draw() override;
  void update(float ms) override;
  void pressButton(const ButtonType &type) const override;
};

#endif// INGAMEMENU_H
