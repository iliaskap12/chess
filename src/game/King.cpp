#include <game/King.h>
#include <game/Soldier.h>
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
  return this->squares_;
}
void King::update(float ms) {
  if (static_cast<App *>(graphics::getUserData())->getGame() != nullptr && static_cast<App *>(graphics::getUserData())->getGame()->getCheckboard() != nullptr) {
    if (Pawn::checkboard == nullptr) {
      Pawn::checkboard = { static_cast<App *>(graphics::getUserData())->getGame()->getCheckboard() };
    }
    this->getSafeAdvanceableSquares();
    Pawn::update(ms);
  }
}

void King::getSafeAdvanceableSquares() {
  auto squares { Pawn::getAdvanceableSquares(this->steps, King::maxSteps) };
  std::vector<std::pair<int, int>> unsafeSquares { this->getUnsafeSquares() };

  std::erase_if(squares, [&unsafeSquares](const std::pair<int, int> &pair) {
    return std::ranges::find(unsafeSquares, pair) != unsafeSquares.end();
  });

  this->squares_ = { squares };
}

bool King::isChecked() {
  auto kingSquare { Pawn::getSquare() };
  std::pair<int, int> kingSquareCoordinates { std::make_pair(static_cast<int>(kingSquare->getRow()), static_cast<int>(kingSquare->getColumn())) };
  std::vector<std::pair<int, int>> unsafeSquares {this->getUnsafeSquares()};

  if (std::input_iterator auto result { std::ranges::find_if(
          unsafeSquares.begin(),
          unsafeSquares.end(),
          [&kingSquareCoordinates](const std::pair<int, int> &coordinates) {
            return kingSquareCoordinates == coordinates;
          })
      };
      result != unsafeSquares.end()) {
    return true;
  }

  return false;
}

std::vector<std::pair<int, int>> King::getUnsafeSquares() {
  auto squares { Pawn::getAdvanceableSquares(this->steps, King::maxSteps) };
  auto kingSquare { Pawn::getSquare() };
  std::pair<int, int> kingSquareCoordinates { std::make_pair(static_cast<int>(kingSquare->getRow()), static_cast<int>(kingSquare->getColumn())) };
  std::vector<std::pair<int, int>> unsafeSquares{ std::vector<std::pair<int, int>>() };

  for (auto const& row : *Pawn::checkboard->getSquares()) {
    for (auto const& square : row) {
      if (square->hasPawn() && square->getPawn()->getColor() != Pawn::getColor() && dynamic_pointer_cast<Soldier>(square->getPawn()) != nullptr) {
        auto squareCoordinates {dynamic_pointer_cast<Soldier>(square->getPawn())->getCapturableSquares()};
        unsafeSquares.resize(unsafeSquares.size() + squareCoordinates.size());
        std::ranges::copy_if(squareCoordinates.begin(), squareCoordinates.end(), std::back_inserter(unsafeSquares),
                             [&squares, &kingSquareCoordinates](const std::pair<int, int>& dest) {
                               return std::ranges::find(squares, dest) != squares.end() || dest == kingSquareCoordinates;
                             });
        continue;
      }
      if (square->hasPawn() && square->getPawn()->getColor() != Pawn::getColor()) {
        auto squareCoordinates {square->getPawn()->getAdvanceableSquares()};
        unsafeSquares.resize(unsafeSquares.size() + squareCoordinates.size());
        std::ranges::copy_if(squareCoordinates.begin(), squareCoordinates.end(), std::back_inserter(unsafeSquares),
         [&squares, &kingSquareCoordinates](const std::pair<int, int>& dest) {
           return std::ranges::find(squares, dest) != squares.end() || dest == kingSquareCoordinates;
         });
      }
    }
  }

  return unsafeSquares;
}
