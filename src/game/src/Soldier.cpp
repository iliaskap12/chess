#include <game/Soldier.h>
#include <game/Knight.h>
#include <App.h>
#include <algorithm>
#include <graphics/PlayingScreen.h>

Soldier::Soldier(PawnColor color) : Pawn(color) {
  Pawn::setTexture("soldier");
}

std::vector<std::pair<int, int>> Soldier::getAdvanceableSquares() {
  std::vector<std::pair<int, int>> steps{std::vector<std::pair<int, int>>()};
  auto checkboard{static_cast<App *>(graphics::getUserData())->getGame().lock()->getCheckboard()};

  steps.push_back(std::make_pair<int, int>(1, 0));
  steps.push_back(std::make_pair<int, int>(1, 1));
  steps.push_back(std::make_pair<int, int>(1, -1));

  if (const int nextRowWhite{this->getSquare().lock()->getRow() + 1}; nextRowWhite <= 7) {
    const bool startingPositionWhite{this->getSquare().lock()->getRow() == 1};
    const bool pawnAheadWhite{checkboard->getSquareInfo(std::make_pair(nextRowWhite, this->getSquare().lock()->getColumn())).first};
    if (startingPositionWhite && Pawn::getColor() == PawnColor::WHITE && !pawnAheadWhite) {
      steps.push_back(std::make_pair<int, int>(2, 0));
    }
  }

  if (const int nextRowBlack{this->getSquare().lock()->getRow() - 1}; nextRowBlack >= 0) {
    const bool startingPositionBlack{this->getSquare().lock()->getRow() == 6};
    const bool pawnAheadBlack{checkboard->getSquareInfo(std::make_pair(nextRowBlack, this->getSquare().lock()->getColumn())).first};
    if (startingPositionBlack && Pawn::getColor() == PawnColor::BLACK && !pawnAheadBlack) {
      steps.push_back(std::make_pair<int, int>(2, 0));
    }
  }

  constexpr unsigned short int maxSteps{1};

  auto advanceableSquares{Pawn::getAdvanceableSquares(steps, maxSteps, false)};

  std::erase_if(advanceableSquares, [&checkboard, this](const auto &pair) {
    if (pair.second != this->getSquare().lock()->getColumn()) {
      const auto &[hasPawn, pawnColor]{checkboard->getSquareInfo(pair)};
      return !hasPawn;
    }

    if (pair.second == this->getSquare().lock()->getColumn()) {
      const auto &[hasPawn, pawnColor]{checkboard->getSquareInfo(pair)};
      return hasPawn;
    }

    return false;
  });

  const auto enPassantMove{this->addEnPassant()};

  if (enPassantMove.first != 0) {
    advanceableSquares.push_back(enPassantMove);
  }

  return advanceableSquares;
}

std::vector<std::pair<int, int>> Soldier::getHoldingSquares() {
  std::vector<std::pair<int, int>> steps { std::vector<std::pair<int, int>>() };

  steps.push_back(std::make_pair<int, int>(1, 1));
  steps.push_back(std::make_pair<int, int>(1, -1));

  constexpr unsigned short int maxSteps { 1 };

  auto advanceableSquares { Pawn::getAdvanceableSquares(steps, maxSteps, true) };

  std::erase_if(advanceableSquares, [this](const auto& pair) {
    if (pair.second == this->getSquare().lock()->getColumn()) {
      auto checkboard{static_cast<App *>(graphics::getUserData())->getGame().lock()->getCheckboard()};
      const auto &[hasPawn, pawnColor]{checkboard->getSquareInfo(pair)};
      return hasPawn;
    }

    return false;
  });

  return advanceableSquares;
}

void Soldier::promote() {
  Pawn::getSquare().lock()->unregisterPawn();
  Pawn::getSquare().lock()->registerPawn(this->selectedPawn);
}

void Soldier::update(float ms) {
  Pawn::update(ms);
  if (Pawn::getSquare().lock()->getRow() == 7 && Pawn::getColor() == PawnColor::WHITE) {
    this->initiatePromotion();
  }
  if (Pawn::getSquare().lock()->getRow() == 0 && Pawn::getColor() == PawnColor::BLACK) {
    this->initiatePromotion();
  }
}

void Soldier::initiatePromotion() {
  const auto playingScreen{std::static_pointer_cast<PlayingScreen>(static_cast<App *>(graphics::getUserData())->getScreen())};
  playingScreen->getGame()->getCheckboard()->setPawnMoving(true);
  playingScreen->setPromotion(std::dynamic_pointer_cast<Soldier>(this->shared_from_this()));
}

void Soldier::setPromotion(std::shared_ptr<Pawn> pawn) {
  this->selectedPawn = {pawn};
}

void Soldier::setEnPassant(bool en_passant) {
  this->enPassant = {en_passant};
}

std::pair<int, int> Soldier::addEnPassant() {
  // left && right square
  const auto checkboard{static_cast<App *>(graphics::getUserData())->getGame().lock()->getCheckboard()};
  const int nextRow{Pawn::getColor() == PawnColor::WHITE ? 1 : -1};
  if (Pawn::getSquare().lock()->getColumn() != 0) {
    // left
    const auto nextPawn{std::make_pair(Pawn::getSquare().lock()->getRow(), Pawn::getSquare().lock()->getColumn() - 1)};
    const bool hasPawn{checkboard->getSquare(nextPawn).lock()->hasPawn()};
    if (hasPawn && (std::dynamic_pointer_cast<Soldier>(checkboard->getSquare(nextPawn).lock()->getPawn()))) {
      if (std::dynamic_pointer_cast<Soldier>(checkboard->getSquare(nextPawn).lock()->getPawn())->isEnPassant()) {
        const auto candidate{std::make_pair(nextRow + Pawn::getSquare().lock()->getRow(), Pawn::getSquare().lock()->getColumn() - 1)};
        if (this->bannedEnPassantSquare.has_value()) {
          const auto bannedSquare{std::make_pair(this->bannedEnPassantSquare.value().first + nextRow, this->bannedEnPassantSquare.value().second)};
          if (bannedSquare != candidate) {
            return candidate;
          }
        } else {
          return candidate;
        }
      }
    }
  }

  if (Pawn::getSquare().lock()->getColumn() != 7) {
    // right
    const auto nextPawn{std::make_pair(Pawn::getSquare().lock()->getRow(), Pawn::getSquare().lock()->getColumn() + 1)};
    const bool hasPawn{checkboard->getSquare(nextPawn).lock()->hasPawn()};
    if (hasPawn && (std::dynamic_pointer_cast<Soldier>(checkboard->getSquare(nextPawn).lock()->getPawn()))) {
      if (std::dynamic_pointer_cast<Soldier>(checkboard->getSquare(nextPawn).lock()->getPawn())->isEnPassant()) {
        const auto candidate{std::make_pair(nextRow + Pawn::getSquare().lock()->getRow(), Pawn::getSquare().lock()->getColumn() + 1)};
        if (this->bannedEnPassantSquare.has_value()) {
          const auto bannedSquare{std::make_pair(this->bannedEnPassantSquare.value().first + nextRow, this->bannedEnPassantSquare.value().second)};
          if (bannedSquare != candidate) {
            return candidate;
          }
        } else {
          return candidate;
        }
      }
    }
  }

  return std::pair<int, int>(0, 0);
}

bool Soldier::isEnPassant() const {
  return this->enPassant;
}

void Soldier::banEnPassantOn(const std::pair<int, int> &square) {
  this->bannedEnPassantSquare.emplace(std::move(square));
}
