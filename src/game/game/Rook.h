#ifndef ROOK_H
#define ROOK_H

#include "Pawn.h"

class Rook : public Pawn {
  std::vector<std::pair<int, int>> steps{std::vector<std::pair<int, int>>()};
  static constexpr unsigned short int maxSteps{8};
  bool hasMoved{false};

public:
  explicit Rook(PawnColor color);
  std::vector<std::pair<int, int>> getAdvanceableSquares() override;
  std::vector<std::pair<int, int>> getHoldingSquares() override;
  std::weak_ptr<Pawn> getBlockedPawn() override;
  void setMoved();
  [[nodiscard]] bool getMoved() const;
};

#endif // ROOK_H
