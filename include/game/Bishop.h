
#ifndef BISHOP_H
#define BISHOP_H

#include "Pawn.h"

class Bishop : public Pawn {

public:
  explicit Bishop(PawnColor color);
  std::vector<std::pair<int, int>> getAdvanceableSquares() override;
};


#endif // BISHOP_H
