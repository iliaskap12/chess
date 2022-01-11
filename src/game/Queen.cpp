#include <game/Queen.h>
Queen::Queen(PawnColor color) : Pawn(color) {
  Pawn::setTexture("queen");
  this->steps.push_back(std::make_pair<int, int>(1, 1));
  this->steps.push_back(std::make_pair<int, int>(-1, 1));
  this->steps.push_back(std::make_pair<int, int>(1, -1));
  this->steps.push_back(std::make_pair<int, int>(-1, -1));
  this->steps.push_back(std::make_pair<int, int>(1, 0));
  this->steps.push_back(std::make_pair<int, int>(-1, 0));
  this->steps.push_back(std::make_pair<int, int>(0, 1));
  this->steps.push_back(std::make_pair<int, int>(0, -1));
}

std::vector<std::pair<int, int>> Queen::getAdvanceableSquares() {
  return Pawn::getAdvanceableSquares(this->steps, Queen::maxSteps, false);
}

std::vector<std::pair<int, int>> Queen::getHoldingSquares() {
  return Pawn::getAdvanceableSquares(this->steps, Queen::maxSteps, true);
}
