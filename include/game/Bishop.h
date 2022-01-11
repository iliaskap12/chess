
#ifndef BISHOP_H
#define BISHOP_H

#include "Pawn.h"

class Bishop : public Pawn {
  std::vector<std::pair<int, int>> steps { std::vector<std::pair<int, int>>() };
  static constexpr unsigned short int maxSteps { 8 };

public:
  explicit Bishop(PawnColor color);
  std::vector<std::pair<int, int>> getAdvanceableSquares() override;
  std::vector<std::pair<int, int>> getHoldingSquares() override;
};


#endif // BISHOP_H
