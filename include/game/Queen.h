
#ifndef QUEEN_H
#define QUEEN_H

#include "Pawn.h"

class Queen : public Pawn {

public:
  explicit Queen(PawnColor color);
  std::vector<std::pair<int, int>> getAdvanceableSquares() override;
};

#endif // QUEEN_H
