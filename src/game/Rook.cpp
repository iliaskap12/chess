#include <game/Rook.h>

Rook::Rook(PawnColor color) : Pawn(color) {
  Pawn::setTexture("rook");
  this->steps.push_back(std::make_pair<int, int>(1, 0));
  this->steps.push_back(std::make_pair<int, int>(-1, 0));
  this->steps.push_back(std::make_pair<int, int>(0, 1));
  this->steps.push_back(std::make_pair<int, int>(0, -1));
}

std::vector<std::pair<int, int>> Rook::getAdvanceableSquares() {
  return Pawn::getAdvanceableSquares(this->steps, Rook::maxSteps, false);
}

std::vector<std::pair<int, int>> Rook::getHoldingSquares() {
  return Pawn::getAdvanceableSquares(this->steps, Rook::maxSteps, true);
}
