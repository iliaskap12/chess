#include <game/Square.h>
#include <sgg/graphics.h>
#include <App.h>

Square::Square() = default;

Square::Square(unsigned short int row, unsigned short int column) : row_(row), column_(column) {
  constexpr float offset { 400.0f };
  constexpr float squareWidth { 100.0f };
  const float reverseRowIndex { static_cast<float>(Checkboard::sideSize - 1 - this->row_) }; // coordinates start top left (0, 0) but checkboard row index start from bottom.
  this->drawingArea->setWidth(squareWidth);
  this->drawingArea->setHeight(squareWidth);
  this->drawingArea->setLeftBottom(Point(offset + squareWidth * static_cast<float>(this->column_), offset / 2 + squareWidth * reverseRowIndex));
  if ((this->column_ + this->row_) % 2 == 0) {
    this->drawingArea->setBrush(Brush::DARK_BROWN, Rectangle::colors.at(Brush::DARK_BROWN));
    this->drawingArea->setMarkBrush(Brush::DARK_GREEN);
  } else {
    this->drawingArea->setBrush(Brush::LIGHT_BROWN, Rectangle::colors.at(Brush::LIGHT_BROWN));
    this->drawingArea->setMarkBrush(Brush::LIGHT_GREEN);
  }
}

void Square::initialize(Point leftBottom, const graphics::Brush &brush, Brush type, float squareWidth) {
  this->drawingArea->setWidth(squareWidth);
  this->drawingArea->setHeight(squareWidth);
  this->drawingArea->setLeftBottom(leftBottom);
  this->drawingArea->setBrush(type, brush);
}

void Square::draw() {
  this->drawingArea->draw();
  if (this->hasPawn()) {
    this->pawn_->draw();
  }
}

void Square::update(float ms) {
  if (this->hasPawn()) {
    this->pawn_->update(ms);
  }

  if (this->drawingArea->clicked()) {
    static_cast<App*>(graphics::getUserData())->getGame()->getCheckboard()->notify(this);
  }
  this->drawingArea->update(ms);
}
unsigned short int Square::getRow() const { return this->row_; }
unsigned short int Square::getColumn() const { return this->column_; }

char Square::getColumnAsChar() const {
  const char A = 'A';
  return static_cast<char>(A + static_cast<char>(this->column_));
}

void Square::registerPawn(std::shared_ptr<Pawn> pawn) {
  this->pawn_ = { std::move(pawn) };
  this->pawn_->setSquare(this);
}

void Square::unregisterPawn() {
  this->pawn_ = { nullptr };
}

std::shared_ptr<Pawn> Square::getPawn() const {
  return this->pawn_;
}

bool Square::hasPawn() const {
  return this->pawn_ != nullptr;
}

std::shared_ptr<Rectangle> Square::getDrawingArea() const {
  return this->drawingArea;
}

bool operator==(const Square &lhs, const Square &rhs) {
  return lhs.row_ == rhs.row_ && lhs.column_ == rhs.column_;
}

void Square::setRow(unsigned short row) {
  this->row_ = { row };
}

void Square::setColumn(unsigned short column) {
  this->column_ = { column };
}

void Square::increaseDangerReferenceCount(PawnColor color) {
  if (color == PawnColor::WHITE) {
    ++this->whiteDangerReferenceCount_;
  } else {
    ++this->blackDangerReferenceCount_;
  }
}

void Square::resetDangerReferenceCount() {
  this->whiteDangerReferenceCount_ = { 0 };
  this->blackDangerReferenceCount_ = { 0 };
}

unsigned short int Square::getDangerReferenceCount(PawnColor color) const {
  if (color == PawnColor::WHITE) {
    return this->whiteDangerReferenceCount_;
  } else {
    return this->blackDangerReferenceCount_;
  }
}
