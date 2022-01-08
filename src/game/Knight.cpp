#include <game/Knight.h>

Knight::Knight(PawnColor color) : Pawn(color) {
  Pawn::setTexture("knight");
}

std::vector<std::pair<int, int>> Knight::getAdvanceableSquares() {
  std::vector<std::pair<int, int>> steps { std::vector<std::pair<int, int>>() };
  steps.push_back(std::make_pair<int, int>(2, 1));
  steps.push_back(std::make_pair<int, int>(-2, 1));
  steps.push_back(std::make_pair<int, int>(2, -1));
  steps.push_back(std::make_pair<int, int>(-2, -1));
  steps.push_back(std::make_pair<int, int>(1, 2));
  steps.push_back(std::make_pair<int, int>(1, -2));
  steps.push_back(std::make_pair<int, int>(-1, 2));
  steps.push_back(std::make_pair<int, int>(-1, -2));

  constexpr unsigned short int maxSteps { 1 };

  return Pawn::getAdvanceableSquares(steps, maxSteps);
}
