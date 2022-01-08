
#ifndef KNIGHT_H
#define KNIGHT_H

#include "Pawn.h"

class Knight : public Pawn {
public:
  explicit Knight(PawnColor color);
  std::vector<std::pair<int, int>> getAdvanceableSquares() override;
};

#endif // KNIGHT_H
