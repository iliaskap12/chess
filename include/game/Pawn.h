
#ifndef PAWN_H
#define PAWN_H

#include "graphics/Drawable.h"
#include "graphics/Updateable.h"
#include "PawnColor.h"

class Pawn : public Drawable, public Updateable {
  PawnColor color;

public:
  explicit Pawn(PawnColor color);
  void draw() override = 0;
  void update(float ms) override = 0;
};

#endif // PAWN_H
