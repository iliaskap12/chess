#include <game/Bishop.h>
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

std::shared_ptr<Pawn> Bishop::getBlockedPawn() {
  const unsigned short int currentRow { this->getSquare()->getRow() };
  const unsigned short int currentColumn { this->getSquare()->getColumn() };

  unsigned short int nextRow { currentRow };
  unsigned short int nextColumn { currentColumn };
  for (const auto& [rowStep, columnStep] : Pawn::correctDirection(this->steps)) {
    bool shouldTerminate { false };
    bool foundPawn { false };
    std::shared_ptr<Pawn> pawn { nullptr };

    unsigned short int numberOfSteps { 0 };
    while (!shouldTerminate) {
      nextRow += rowStep;
      nextColumn += columnStep;
      if ((nextRow >= Checkboard::sideSize || nextColumn >= Checkboard::sideSize) || numberOfSteps == Bishop::maxSteps) {
        shouldTerminate = { true };
        continue;
      }
      ++numberOfSteps;

      auto checkboard { static_cast<App *>(graphics::getUserData())->getGame()->getCheckboard() };
      std::pair<int, int> squareCoordinates { std::make_pair<int, int>(nextRow, nextColumn) };
      auto [hasPawn, pawnColor] { checkboard->getSquareInfo(squareCoordinates) };

      if (hasPawn && pawnColor != Pawn::getColor() && foundPawn && checkboard->isKing(pawn->getColor(), squareCoordinates)) {
        return pawn;
      }

      if (hasPawn && pawnColor != Pawn::getColor() && foundPawn) {
        shouldTerminate = { true };
      }

      if (hasPawn && pawnColor != Pawn::getColor()) {
        pawn = { checkboard->getSquare(squareCoordinates)->getPawn() };
        foundPawn = { true };
      }
    }

    nextRow = { currentRow };
    nextColumn = { currentColumn };
  }

  return nullptr;
}