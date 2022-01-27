#include <game/Knight.h>

Knight::Knight(PawnColor color) : Pawn(color) {
  Pawn::setTexture("knight");
  this->steps.push_back(std::make_pair<int, int>(2, 1));
  this->steps.push_back(std::make_pair<int, int>(-2, 1));
  this->steps.push_back(std::make_pair<int, int>(2, -1));
  this->steps.push_back(std::make_pair<int, int>(-2, -1));
  this->steps.push_back(std::make_pair<int, int>(1, 2));
  this->steps.push_back(std::make_pair<int, int>(1, -2));
  this->steps.push_back(std::make_pair<int, int>(-1, 2));
  this->steps.push_back(std::make_pair<int, int>(-1, -2));
}

std::vector<std::pair<int, int>> Knight::getAdvanceableSquares() {
  return Pawn::getAdvanceableSquares(this->steps, Knight::maxSteps, false);
}

std::vector<std::pair<int, int>> Knight::getHoldingSquares() {
  auto squares = Pawn::getAdvanceableSquares(this->steps, Knight::maxSteps, true);
  return squares;
}
