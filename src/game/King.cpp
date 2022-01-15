#include <game/King.h>
#include <algorithm>
#include <App.h>

King::King(PawnColor color) : Pawn(color) {
  Pawn::setTexture("king");
  this->steps.push_back(std::make_pair<int, int>(1, 1));
  this->steps.push_back(std::make_pair<int, int>(-1, 1));
  this->steps.push_back(std::make_pair<int, int>(1, -1));
  this->steps.push_back(std::make_pair<int, int>(-1, -1));
  this->steps.push_back(std::make_pair<int, int>(1, 0));
  this->steps.push_back(std::make_pair<int, int>(-1, 0));
  this->steps.push_back(std::make_pair<int, int>(0, 1));
  this->steps.push_back(std::make_pair<int, int>(0, -1));
}

std::vector<std::pair<int, int>> King::getAdvanceableSquares() {
  auto squares {Pawn::getAdvanceableSquares(this->steps, King::maxSteps, false)};

  return this->getKingSquares(squares);
}

std::vector<std::pair<int, int>> King::getHoldingSquares() {
  auto squares { Pawn::getAdvanceableSquares(this->steps, King::maxSteps, true) };

  return this->getKingSquares(squares);
}

std::vector<std::pair<int, int>> King::getKingSquares(std::vector<std::pair<int, int>> &pairs) const {
  std::erase_if(pairs, [this](const std::pair<int, int> &pair) {
    return static_cast<App *>(graphics::getUserData())
               ->getGame()
               ->getCheckboard()
               ->getSquare(pair)
               ->getDangerReferenceCount(Pawn::getColor() == PawnColor::WHITE ? PawnColor::BLACK : PawnColor::WHITE) > 0;
  });

  return pairs;
}

bool King::isChecked() const {
  auto kingSquare { Pawn::getSquare() };
  PawnColor color { Pawn::getColor() == PawnColor::WHITE ? PawnColor::BLACK : PawnColor::WHITE };

  return kingSquare->getDangerReferenceCount(color) > 0;
}