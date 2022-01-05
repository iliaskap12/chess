
#ifndef KING_H
#define KING_H

#include "Pawn.h"

class King : public Pawn {

public:
  explicit King(PawnColor color);
  void update(float ms) override;
};

#endif // KING_H
