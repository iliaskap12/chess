
#ifndef QUEEN_H
#define QUEEN_H

#include "Pawn.h"

class Queen : public Pawn {
  std::vector<std::pair<int, int>> steps { std::vector<std::pair<int, int>>() };
  static constexpr unsigned short int maxSteps { 8 };

public:
  explicit Queen(PawnColor color);
  std::vector<std::pair<int, int>> getAdvanceableSquares() override;
  std::vector<std::pair<int, int>> getHoldingSquares() override;
  std::weak_ptr<Pawn> getBlockedPawn() override;
};

#endif // QUEEN_H
