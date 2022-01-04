
#ifndef SCREEN_H
#define SCREEN_H

#include "Drawable.h"
#include "Updateable.h"
#include "ButtonType.h"

class Screen : public Drawable, public Updateable {

public:
  Screen();
  void draw() override = 0;
  void update(float ms) override = 0;
  virtual void pressButton(ButtonType type) = 0;
};

#endif // SCREEN_H
