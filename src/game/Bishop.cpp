#include <game/Bishop.h>
#include "App.h"

Bishop::Bishop(PawnColor color) : Pawn(color) {
  Pawn::setTexture("bishop");
}

std::vector<std::pair<int, int>> Bishop::getAdvanceableSquares() {
  std::vector<std::pair<int, int>> steps { std::vector<std::pair<int, int>>() };
  steps.push_back(std::make_pair<int, int>(1, 1));
  steps.push_back(std::make_pair<int, int>(-1, 1));
  steps.push_back(std::make_pair<int, int>(1, -1));
  steps.push_back(std::make_pair<int, int>(-1, -1));

  constexpr unsigned short int maxSteps { 8 };

  return Pawn::getAdvanceableSquares(steps, maxSteps);
}
