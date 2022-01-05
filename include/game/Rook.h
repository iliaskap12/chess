#ifndef ROOK_H
#define ROOK_H

#include "Pawn.h"

class Rook : public Pawn {

public:
  explicit Rook(PawnColor color);
  void update(float ms) override;
};

#endif // ROOK_H
