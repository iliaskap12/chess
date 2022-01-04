#include <game/Square.h>

Square::Square() = default;

Square::Square(unsigned short int row, unsigned short int column) : row(row), column(column) {}

void Square::draw() {
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
