#include <game/Square.h>
#include <sgg/graphics.h>

Square::Square() = default;

Square::Square(unsigned short int row, unsigned short int column) : row(row), column(column) {
  graphics::Brush square { graphics::Brush() };
  if ((this->column + this->row) % 2 == 0) {
    square.fill_color[0] = { 0.4588f };
    square.fill_color[1] = { 0.2901f };
    square.fill_color[2] = { 0.0f };
  } else {
    square.fill_color[0] = { 1.0f };
    square.fill_color[1] = { 0.9137f };
    square.fill_color[2] = { 0.7725f };
  }
  square.fill_opacity = { 1.0f };
  square.outline_opacity = { 0.0f };
  square.outline_width = { 0.0f };
  constexpr float offset { 200.0f };
  constexpr float squareWidth { 100.0f };
  const float reverseRowIndex { static_cast<float>(7 - this->row) }; // coordinates start top left (0, 0) but checkboard row index start from bottom.
  this->drawingArea = { Rectangle(Point(offset + squareWidth * static_cast<float>(this->column), offset + squareWidth * reverseRowIndex), squareWidth, squareWidth) };
  this->drawingArea.setBrush(square);
}

void Square::draw() {
  this->drawingArea.draw();
  if (this->hasPawn()) {
    this->pawn_->draw();
  }
}

void Square::update(float ms) {
}

unsigned short int Square::getRow() const { return this->row; }
unsigned short int Square::getColumn() const { return this->column; }
char Square::getColumnAsChar() const {
  const char A = 'A';
  return static_cast<char>(A + static_cast<char>(this->column));
}

void Square::registerPawn(std::shared_ptr<Pawn> pawn) {
  this->pawn_ = std::move(pawn);
  this->pawn_->setSquare(this);
}

void Square::unregisterPawn() {
  this->pawn_ = nullptr;
}

std::shared_ptr<Pawn> Square::getPawn() const {
  return this->pawn_;
}

bool Square::hasPawn() const {
  return this->pawn_ != nullptr;
}

Rectangle Square::getDrawingArea() const {
  return this->drawingArea;
}
