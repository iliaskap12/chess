#include <game/Rook.h>
#include <App.h>

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

std::shared_ptr<Pawn> Rook::getBlockedPawn() {
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
      if ((nextRow >= Checkboard::sideSize || nextColumn >= Checkboard::sideSize) || numberOfSteps == Rook::maxSteps) {
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