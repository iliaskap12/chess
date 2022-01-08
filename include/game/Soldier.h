
#ifndef SOLDIER_H
#define SOLDIER_H

#include "PawnColor.h"
#include "Pawn.h"

class Soldier : public Pawn {

public:
  explicit Soldier(PawnColor color);
  std::vector<std::pair<int, int>> getAdvanceableSquares() override;
};

#endif // SOLDIER_H
