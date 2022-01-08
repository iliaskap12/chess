#include <game/Pawn.h>
#include <vector>
#include <utility>
#include <algorithm>
#include <App.h>
#include <graphics/PlayingScreen.h>

Pawn::Pawn(PawnColor color) : color(color) {}

void Pawn::setSquare(Square* square) {
  this->square_ = { square };
  this->drawingArea.setHeight(this->square_->getDrawingArea().getHeight());
  this->drawingArea.setWidth(this->square_->getDrawingArea().getWidth());
  this->drawingArea.setLeftBottom(this->square_->getDrawingArea().getLeftBottom());
  graphics::Brush pawn { Rectangle::colors.at(Brush::TEXTURE) };
  pawn.texture = { getImagesPath() + this->texture_ + "-" + this->getColor() + this->png };
  this->drawingArea.setBrush(Brush::TEXTURE, pawn);
}

Square *Pawn::getSquare() const {
  return this->square_;
}

PawnColor Pawn::getColor() const {
  return this->color;
}

void Pawn::draw() {
  this->drawingArea.draw();
}

void Pawn::update(float ms) {
  this->move(ms);
}

void Pawn::setTexture(std::string texture) {
  this->texture_ = { std::move(texture) };
}

void Pawn::move(float ms) {
  if (this->shouldMove && this->square_ != nullptr) {
    std::shared_ptr<Checkboard> checkboard { static_cast<App *>(graphics::getUserData())->getGame()->getCheckboard() };

    this->drawingArea.setLeftBottom(this->drawingArea.getLeftBottom() + Point(this->moveSteps.second, this->moveSteps.first));
    checkboard->setMovingSquare(this->drawingArea.getLeftBottom(), this->drawingArea.getBrush(), this->drawingArea.getBrushType());

    if (this->square_->getDrawingArea().getLeftBottom() == this->destination_->getDrawingArea().getLeftBottom()) {
      this->movingSquare->unregisterPawn();
      this->movingSquare = { nullptr };
      this->square_->unregisterPawn();
      if (this->destination_->hasPawn()) {
        this->capture(this->destination_->getPawn());
      }
      this->square_ = { this->destination_ };
      this->square_->registerPawn(self_);
      this->destination_ = { nullptr };
      this->moveSteps = {  };
      this->shouldMove = { false };
      checkboard->resetMovingSquare();
    }
  }
}

void Pawn::capture(std::shared_ptr<Pawn>) {
  // capture pawn
}

std::vector<std::pair<int, int>> Pawn::getAdvanceableSquares(std::vector<std::pair<int, int>> const& steps, unsigned short int maxSteps) const {
  std::vector<std::pair<int, int>> advanceableSquares { std::vector<std::pair<int, int>>() };
  const unsigned short int currentRow { this->getSquare()->getRow() };
  const unsigned short int currentColumn { this->getSquare()->getColumn() };
  auto checkboard { static_pointer_cast<PlayingScreen>(static_cast<App*>(graphics::getUserData())->getScreen())->getGame()->getCheckboard() };

  unsigned short int nextRow { currentRow };
  unsigned short int nextColumn { currentColumn };
  std::vector<std::pair<int, int>> reverseSteps { std::vector<std::pair<int, int>>(steps.size()) };
  if (this->color == PawnColor::BLACK) {
    std::ranges::transform(steps.begin(), steps.end(), reverseSteps.begin(), [](const std::pair<int, int> &pair){
      return std::make_pair(-pair.first, -pair.second);
    });
  }
  for (const auto& [rowStep, columnStep] : (this->color == PawnColor::WHITE ? steps : reverseSteps)) {
    bool shouldTerminate { false };

    unsigned short int numberOfSteps { 0 };
    while (!shouldTerminate) {
      nextRow += rowStep;
      nextColumn += columnStep;
      if ((nextRow > 7 || nextColumn > 7) || numberOfSteps == maxSteps) {
        shouldTerminate = { true };
        continue;
      }
      ++numberOfSteps;

      std::pair<int, int> squareCoordinates { std::make_pair<int, int>(nextRow, nextColumn) };
      const auto [hasPawn, pawnColor] { checkboard->getSquareInfo(squareCoordinates) };

      if (hasPawn) {
        shouldTerminate = { true };
      }

      if ((hasPawn && *pawnColor != this->getColor()) || !hasPawn) {
        advanceableSquares.push_back(squareCoordinates);
      }
    }

    nextRow = { currentRow };
    nextColumn = { currentColumn };
  }

  return advanceableSquares;
}

const Rectangle &Pawn::getDrawingArea() const {
  return this->drawingArea;
}

void Pawn::moveTo(Square *squarePtr, const std::shared_ptr<Pawn>& self) {
  this->shouldMove = { true };
  this->destination_ = { squarePtr };
  this->movingSquare = { this->square_ };
  constexpr long ms { 2 };
  const float rowDirection { -static_cast<float>(this->destination_->getRow() - this->square_->getRow()) };
  const float columnDirection { static_cast<float>(this->destination_->getColumn() - this->square_->getColumn()) };
  this->moveSteps = { std::make_pair(rowDirection / ms, columnDirection / ms) };
  if (this->self_ == nullptr) {
    this->self_ = { self };
  }

  std::shared_ptr<Checkboard> checkboard { static_cast<App *>(graphics::getUserData())->getGame()->getCheckboard() };
  checkboard->setMovingSquare(this->drawingArea.getLeftBottom(), this->drawingArea.getBrush(), this->drawingArea.getBrushType());
  this->square_ = { &(*checkboard->getMovingSquare()) };
  this->square_->setRow(this->destination_->getRow());
  this->square_->setColumn(this->destination_->getColumn());
  this->square_->registerPawn(self_);
}
