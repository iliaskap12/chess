
#ifndef KNIGHT_H
#define KNIGHT_H

#include "Pawn.h"

class Knight : public Pawn {
  std::vector<std::pair<int, int>> steps{std::vector<std::pair<int, int>>()};
  static constexpr unsigned short int maxSteps{1};

public:
  explicit Knight(PawnColor color);
  std::vector<std::pair<int, int>> getAdvanceableSquares() override;
  std::vector<std::pair<int, int>> getHoldingSquares() override;
};

#endif // KNIGHT_H
