#include <game/Bishop.h>

Bishop::Bishop(PawnColor color) : Pawn(color) {
  Pawn::setTexture("bishop");
  this->steps.push_back(std::make_pair<int, int>(1, 1));
  this->steps.push_back(std::make_pair<int, int>(-1, 1));
  this->steps.push_back(std::make_pair<int, int>(1, -1));
  this->steps.push_back(std::make_pair<int, int>(-1, -1));
}

std::vector<std::pair<int, int>> Bishop::getAdvanceableSquares() {
  return Pawn::getAdvanceableSquares(this->steps, Bishop::maxSteps, false);
}

std::vector<std::pair<int, int>> Bishop::getHoldingSquares() {
  return Pawn::getAdvanceableSquares(this->steps, Bishop::maxSteps, true);
}
