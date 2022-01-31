#include <game/Queen.h>
#include <game/Soldier.h>
#include <App.h>

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

std::weak_ptr<Pawn> Queen::getBlockedPawn() {
  auto game{static_cast<App *>(graphics::getUserData())->getGame().lock()};
  auto checkboard{game->getCheckboard()};

  const unsigned short int currentRow{this->getSquare().lock()->getRow()};
  const unsigned short int currentColumn{this->getSquare().lock()->getColumn()};

  unsigned short int nextRow{currentRow};
  unsigned short int nextColumn{currentColumn};
  for (const auto &[rowStep, columnStep]: Pawn::correctDirection(this->steps)) {
    bool shouldTerminate{false};
    std::shared_ptr<Pawn> pawn{nullptr};
    std::shared_ptr<Soldier> friendlySoldier{nullptr};
    std::shared_ptr<Soldier> enemySoldier{nullptr};

    unsigned short int numberOfSteps{0};
    while (!shouldTerminate) {
      nextRow += rowStep;
      nextColumn += columnStep;
      if ((nextRow >= Checkboard::sideSize || nextColumn >= Checkboard::sideSize) || numberOfSteps == Queen::maxSteps) {
        shouldTerminate = {true};
        continue;
      }
      ++numberOfSteps;

      const std::pair<int, int> squareCoordinates{std::make_pair<int, int>(nextRow, nextColumn)};
      const auto [hasPawn, pawnColor]{checkboard->getSquareInfo(squareCoordinates)};

      const bool blockEnPassant{(friendlySoldier != nullptr) && (enemySoldier != nullptr) && hasPawn && (checkboard->isKing(!Pawn::getColor(), squareCoordinates))};
      if (blockEnPassant) {
        const auto bannedSquare{std::make_pair(friendlySoldier->getSquare().lock()->getRow(), friendlySoldier->getSquare().lock()->getColumn())};
        enemySoldier->banEnPassantOn(bannedSquare);
        return std::weak_ptr<Pawn>();
      }

      const bool lonelyPawn{(((pawn == enemySoldier) && (enemySoldier != nullptr)) || ((pawn != nullptr) && (enemySoldier == nullptr)))};
      const bool blockPawn{(lonelyPawn) && (friendlySoldier == nullptr) && hasPawn && (checkboard->isKing(!Pawn::getColor(), squareCoordinates))};
      if (blockPawn) {
        return pawn;
      }

      if (hasPawn) {
        if (pawnColor != Pawn::getColor()) {
          if (pawn == nullptr) {
            pawn = {checkboard->getSquare(squareCoordinates).lock()->getPawn()};
          }
          if (enemySoldier == nullptr) {
            enemySoldier = {std::dynamic_pointer_cast<Soldier>(checkboard->getSquare(squareCoordinates).lock()->getPawn())};
          }
        } else {
          if (friendlySoldier == nullptr) {
            friendlySoldier = {std::dynamic_pointer_cast<Soldier>(checkboard->getSquare(squareCoordinates).lock()->getPawn())};
          }
        }
      }
    }

    nextRow = { currentRow };
    nextColumn = { currentColumn };
  }

  return std::weak_ptr<Pawn>();
}
