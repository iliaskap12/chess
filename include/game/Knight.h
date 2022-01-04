
#ifndef KNIGHT_H
#define KNIGHT_H

#include "Pawn.h"

class Knight : public Pawn {
public:
  explicit Knight(PawnColor color);
  void draw() override;
  void update(float ms) override;
};

#endif // KNIGHT_H
