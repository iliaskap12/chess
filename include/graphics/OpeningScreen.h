
#ifndef OPENINGSCREEN_H
#define OPENINGSCREEN_H

#include "Screen.h"

class OpeningScreen : public Screen {

public:
  OpeningScreen();
  void draw() override;
  void update(float ms) override;
  void pressButton(ButtonType type) override;
};

#endif // OPENINGSCREEN_H
