
#ifndef QUEEN_H
#define QUEEN_H

#include "Pawn.h"

class Queen : public Pawn {

public:
  explicit Queen(PawnColor color);
  void draw() override;
  void update(float ms) override;
};

#endif // QUEEN_H
