#include <game/Pawn.h>
#include <vector>
#include <utility>
#include <algorithm>
#include <App.h>
#include <graphics/PlayingScreen.h>
#include <game/Checkboard.h>
#include <util/paths.h>

Pawn::Pawn(PawnColor color) : color(color) {}

void Pawn::setSquare(const std::shared_ptr<Square> &square) {
  this->square_ = {square};
  this->drawingArea->setHeight(square->getDrawingArea().lock()->getHeight());
  this->drawingArea->setWidth(square->getDrawingArea().lock()->getWidth());
  this->drawingArea->setLeftBottom(square->getDrawingArea().lock()->getLeftBottom());
  graphics::Brush pawn{Rectangle::colors.at(Brush::TEXTURE)};
  pawn.texture = {paths::getImagesPath() + this->texture_ + "-" + this->getColor() + this->png};
  this->drawingArea->setBrush(Brush::TEXTURE, pawn);
}

std::weak_ptr<Square> Pawn::getSquare() const {
  return this->square_;
}

PawnColor Pawn::getColor() const {
  return this->color;
}

void Pawn::draw() {
  this->drawingArea->draw();
}

void Pawn::update(float ms) {
  if (this->drawingArea->clicked()) {
    this->clickSound.play();
  }
  this->move(ms);
}

void Pawn::setTexture(std::string texture) {
  this->texture_ = { std::move(texture) };
}

void Pawn::move(float ms) {
  if (this->shouldMove && this->square_ != nullptr) {
    auto checkboard{static_cast<App *>(graphics::getUserData())->getGame().lock()->getCheckboard()};
    this->drawingArea->setLeftBottom(this->drawingArea->getLeftBottom() + Point(this->moveSteps.second, this->moveSteps.first));
    checkboard->setMovingSquare(this->drawingArea->getLeftBottom(), this->drawingArea->getBrush(), this->drawingArea->getBrushType());

    auto squareDrawingArea{this->square_->getDrawingArea().lock()};
    auto destinationDrawingArea{this->destination_->getDrawingArea().lock()};

    if (squareDrawingArea->getLeftBottom() == destinationDrawingArea->getLeftBottom()) {
      if (this->destination_->hasPawn()) {
        this->capture(this->destination_->getPawn());
      }
      this->movingSquare->unregisterPawn();
      this->movingSquare.reset();
      this->square_->unregisterPawn();
      this->square_ = {this->destination_};
      this->square_->registerPawn(this->shared_from_this());
      this->destination_.reset();
      this->moveSteps = {};
      this->shouldMove = {false};
      checkboard->checkForCheckmate(this->shared_from_this());
      checkboard->resetMovingSquare();
      checkboard->setPawnMoving(false);
    }
  }
}

void Pawn::capture(const std::shared_ptr<Pawn> &pawn) {
  this->captureSound.play();
  std::shared_ptr<PlayingScreen> playingScreen{static_pointer_cast<PlayingScreen>(static_cast<App *>(graphics::getUserData())->getScreen())};
  std::shared_ptr<Square> square{playingScreen->getSquare(pawn)};
  if (square != nullptr) {
    square->registerPawn(pawn);
    pawn->getSquare().lock()->unregisterPawn();
  }
}

std::vector<std::pair<int, int>> Pawn::correctDirection(std::vector<std::pair<int, int>> steps) const {
  std::vector<std::pair<int, int>> reverseSteps { std::vector<std::pair<int, int>>(steps) };
  if (this->color == PawnColor::BLACK) {
    std::transform(steps.begin(), steps.end(), reverseSteps.begin(), [](const std::pair<int, int> &pair) {
      return std::make_pair(-pair.first, -pair.second);
    });
  }
  return reverseSteps;
}

std::vector<std::pair<int, int>> Pawn::getAdvanceableSquares(const std::vector<pair> &steps, unsigned short int maxSteps, bool holding) const {
  std::vector<std::pair<int, int>> advanceableSquares{std::vector<std::pair<int, int>>()};

  auto game{static_cast<App *>(graphics::getUserData())->getGame().lock()};
  auto checkboard{game->getCheckboard()};
  if (checkboard == nullptr) {
    return advanceableSquares;
  }

  const unsigned short int currentRow{this->square_->getRow()};
  const unsigned short int currentColumn{this->square_->getColumn()};

  unsigned short int nextRow{currentRow};
  unsigned short int nextColumn{currentColumn};
  for (const auto &[rowStep, columnStep]: this->correctDirection(steps)) {
    bool shouldTerminate{false};

    unsigned short int numberOfSteps{0};
    while (!shouldTerminate) {
      nextRow += rowStep;
      nextColumn += columnStep;
      if ((nextRow >= Checkboard::sideSize || nextColumn >= Checkboard::sideSize) || numberOfSteps == maxSteps) {
        shouldTerminate = { true };
        continue;
      }
      ++numberOfSteps;

      std::pair<int, int> squareCoordinates { std::make_pair<int, int>(nextRow, nextColumn) };
      auto [hasPawn, pawnColor] { checkboard->getSquareInfo(squareCoordinates) };

      if (hasPawn) {
        shouldTerminate = { true };
      }

      if (holding && hasPawn && pawnColor.value() != this->getColor() && checkboard->isKing(pawnColor.value(), squareCoordinates)) {
        shouldTerminate = { false };
      }

      if (const bool advanceOnPawn { hasPawn && (holding || pawnColor.value() != this->getColor()) }; advanceOnPawn || !hasPawn) {
        advanceableSquares.push_back(squareCoordinates);
      }
    }

    nextRow = { currentRow };
    nextColumn = { currentColumn };
  }

  return advanceableSquares;
}

std::weak_ptr<Rectangle> Pawn::getDrawingArea() const {
  return this->drawingArea;
}

void Pawn::moveTo(const std::shared_ptr<Square> &squarePtr, const std::shared_ptr<Pawn> &self) {
  this->shouldMove = {true};
  this->destination_ = {squarePtr};
  this->movingSquare = {this->square_};
  constexpr long ms{2};
  const float rowDirection{-static_cast<float>(this->destination_->getRow() - this->square_->getRow())};
  const float columnDirection{static_cast<float>(this->destination_->getColumn() - this->square_->getColumn())};
  this->moveSteps = {std::make_pair(rowDirection / ms, columnDirection / ms)};
  if (this->self_ == nullptr) {
    this->self_ = {self};
  }

  auto checkboard{static_cast<App *>(graphics::getUserData())->getGame().lock()->getCheckboard()};
  checkboard->setMovingSquare(this->drawingArea->getLeftBottom(), this->drawingArea->getBrush(), this->drawingArea->getBrushType());
  this->square_ = {checkboard->getMovingSquare().lock()};
  this->square_->setRow(this->destination_->getRow());
  this->square_->setColumn(this->destination_->getColumn());
  this->square_->registerPawn(this->shared_from_this());
  this->moveSound.play();
}

const std::string &Pawn::getTexture() const {
  return this->texture_;
}

std::weak_ptr<Pawn> Pawn::getBlockedPawn() {
  return std::weak_ptr<Pawn>();
}

bool Pawn::isBlocked() const {
  return this->blocked;
}

void Pawn::block() {
  this->blocked = { true };
}

void Pawn::unblock() {
  this->blocked = {false};
  this->blockingPawn.reset();
}

void Pawn::blockedBy(const std::shared_ptr<Pawn> &blocking) {
  this->blockingPawn = {blocking};
}

std::weak_ptr<Pawn> Pawn::getBlockingPawn() {
  return this->blockingPawn;
}

void Pawn::playCaptureSound() {
  this->captureSound.play();
}
