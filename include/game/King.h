
#ifndef KING_H
#define KING_H

#include "Pawn.h"

class King : public Pawn {

public:
  explicit King(PawnColor color);
  std::vector<std::pair<int, int>> getAdvanceableSquares() override;
};

#endif // KING_H
