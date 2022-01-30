
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
  virtual void cleanup() = 0;
  virtual ~Screen() = default;
};

#endif // SCREEN_H
