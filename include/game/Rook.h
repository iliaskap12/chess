#ifndef ROOK_H
#define ROOK_H

#include "Pawn.h"

class Rook : public Pawn {
  std::vector<std::pair<int, int>> steps { std::vector<std::pair<int, int>>() };
  static constexpr unsigned short int maxSteps { 8 };

public:
  explicit Rook(PawnColor color);
  std::vector<std::pair<int, int>> getAdvanceableSquares() override;
  std::vector<std::pair<int, int>> getHoldingSquares() override;
};

#endif // ROOK_H
