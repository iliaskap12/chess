
#ifndef SOLDIER_H
#define SOLDIER_H

#include "PawnColor.h"
#include "Pawn.h"
#include "Promotable.h"

class Soldier : public Pawn, public Promotable {
  std::shared_ptr<Pawn> selectedPawn{nullptr};

public:
  explicit Soldier(PawnColor color);
  std::vector<std::pair<int, int>> getAdvanceableSquares() override;
  std::vector<std::pair<int, int>> getHoldingSquares() override;
  void promote() override;
  void update(float ms) override;
  void initiatePromotion();
  void setPromotion(std::shared_ptr<Pawn> pawn);
};

#endif // SOLDIER_H
