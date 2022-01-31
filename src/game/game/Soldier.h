
#ifndef SOLDIER_H
#define SOLDIER_H

#include "PawnColor.h"
#include "Pawn.h"
#include "Promotable.h"
#include <optional>

class Soldier : public Pawn, public Promotable {
  std::shared_ptr<Pawn> selectedPawn{nullptr};
  bool enPassant{false};
  std::optional<std::pair<int, int>> bannedEnPassantSquare{std::make_optional<std::pair<int, int>>()};

public:
  explicit Soldier(PawnColor color);
  std::vector<std::pair<int, int>> getAdvanceableSquares() override;
  std::vector<std::pair<int, int>> getHoldingSquares() override;
  void promote() override;
  void update(float ms) override;
  void initiatePromotion();
  void setPromotion(std::shared_ptr<Pawn> pawn);
  void setEnPassant(bool en_passant);
  bool isEnPassant() const;
  std::pair<int, int> addEnPassant();
  void banEnPassantOn(const std::pair<int, int> &square);
};

#endif // SOLDIER_H
