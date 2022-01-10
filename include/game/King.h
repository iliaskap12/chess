
#ifndef KING_H
#define KING_H

#include "Pawn.h"
#include "Checkboard.h"

class King : public Pawn {
  std::vector<std::pair<int, int>> steps { std::vector<std::pair<int, int>>() };
  static constexpr unsigned short int maxSteps { 1 };
  std::vector<std::pair<int, int>> squares_ { std::vector<std::pair<int, int>>() };

public:
  explicit King(PawnColor color);
  std::vector<std::pair<int, int>> getAdvanceableSquares() override;
  [[nodiscard]] std::vector<std::pair<int, int>> getUnsafeSquares();
  void update(float ms) override;
  void getSafeAdvanceableSquares();
  [[nodiscard]] bool isChecked();
};

#endif // KING_H
