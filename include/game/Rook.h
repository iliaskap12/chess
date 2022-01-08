#ifndef ROOK_H
#define ROOK_H

#include "Pawn.h"

class Rook : public Pawn {

public:
  explicit Rook(PawnColor color);
  std::vector<std::pair<int, int>> getAdvanceableSquares() override;
};

#endif // ROOK_H
