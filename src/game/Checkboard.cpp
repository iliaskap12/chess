#include <game/Checkboard.h>
#include <memory>
#include <game/PawnColor.h>
#include <game/Soldier.h>

using Squares = std::array<std::array<Square, Checkboard::sideSize>, Checkboard::sideSize>;

Checkboard::Checkboard() {
  for (unsigned int i = 0; i < Checkboard::sideSize; ++i) {
    PawnColor color = i < 2 ? PawnColor::WHITE : PawnColor::BLACK;
    for (unsigned int j = 0; j < Checkboard::sideSize; ++j) {
      (*this->squares)[i][j] = Square(i, j);
      if (i == 1 || i == 6) {
        (*this->squares)[i][j].registerPawn(std::make_shared<Soldier>(color));
      }
      if (i == 0) {
        switch (j) {
          case 0:
          case 7:
            (*this->squares)[i][j].registerPawn(std::make_shared<Rook>(color));
            break;
          case 1:
          case 6:
            (*this->squares)[i][j].registerPawn(std::make_shared<Knight>(color));
            break;
          case 2:
          case 5:
            (*this->squares)[i][j].registerPawn(std::make_shared<Bishop>(color));
            break;
          case 4:
            (*this->squares)[i][j].registerPawn(std::make_shared<Queen>(color));
            break;
          default:
            (*this->squares)[i][j].registerPawn(std::make_shared<King>(color));
            break;
        }
      }
    }
  }
}

const Squares *Checkboard::getSquares() const {
  return this->squares;
}

void Checkboard::draw() {
}

void Checkboard::update(float ms) {
}

Checkboard::~Checkboard() {
  delete this->squares;
}
