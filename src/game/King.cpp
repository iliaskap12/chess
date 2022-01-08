#include <game/King.h>

King::King(PawnColor color) : Pawn(color) {
  Pawn::setTexture("king");
}

std::vector<std::pair<int, int>> King::getAdvanceableSquares() {
  std::vector<std::pair<int, int>> steps { std::vector<std::pair<int, int>>() };
  steps.push_back(std::make_pair<int, int>(1, 1));
  steps.push_back(std::make_pair<int, int>(-1, 1));
  steps.push_back(std::make_pair<int, int>(1, -1));
  steps.push_back(std::make_pair<int, int>(-1, -1));
  steps.push_back(std::make_pair<int, int>(1, 0));
  steps.push_back(std::make_pair<int, int>(-1, 0));
  steps.push_back(std::make_pair<int, int>(0, 1));
  steps.push_back(std::make_pair<int, int>(0, -1));

  constexpr unsigned short int maxSteps { 1 };

  return Pawn::getAdvanceableSquares(steps, maxSteps);
}
