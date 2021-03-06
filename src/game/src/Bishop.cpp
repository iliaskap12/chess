#include <game/Bishop.h>
#include <game/Soldier.h>
#include <App.h>

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

std::weak_ptr<Pawn> Bishop::getBlockedPawn() {
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
      if ((nextRow >= Checkboard::sideSize || nextColumn >= Checkboard::sideSize) || numberOfSteps == Bishop::maxSteps) {
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
