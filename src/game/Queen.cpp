#include <game/Queen.h>
Queen::Queen(PawnColor color) : Pawn(color) {
  Pawn::setTexture("queen");
}

std::vector<std::pair<int, int>> Queen::getAdvanceableSquares() {
  std::vector<std::pair<int, int>> steps { std::vector<std::pair<int, int>>() };
  steps.push_back(std::make_pair<int, int>(1, 1));
  steps.push_back(std::make_pair<int, int>(-1, 1));
  steps.push_back(std::make_pair<int, int>(1, -1));
  steps.push_back(std::make_pair<int, int>(-1, -1));
  steps.push_back(std::make_pair<int, int>(1, 0));
  steps.push_back(std::make_pair<int, int>(-1, 0));
  steps.push_back(std::make_pair<int, int>(0, 1));
  steps.push_back(std::make_pair<int, int>(0, -1));

  constexpr unsigned short int maxSteps { 8 };

  return Pawn::getAdvanceableSquares(steps, maxSteps);
}
