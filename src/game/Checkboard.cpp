#include <memory>
#include <game/Checkboard.h>
#include <game/PawnColor.h>
#include <game/Soldier.h>
#include <game/Rook.h>
#include <game/Knight.h>
#include <game/Bishop.h>
#include <game/Queen.h>
#include <game/King.h>
#include <sgg/graphics.h>
#include <util/paths.h>

using Squares = std::array<std::array<Square, Checkboard::sideSize>, Checkboard::sideSize>;

Checkboard::Checkboard() {
  for (unsigned short int i = 0; i < Checkboard::sideSize * Checkboard::sideSize; ++i) {
    PawnColor color = i / Checkboard::sideSize < 2 ? PawnColor::WHITE : PawnColor::BLACK;
    (*this->squares)[i / Checkboard::sideSize][i % Checkboard::sideSize] = Square(i / Checkboard::sideSize, i % Checkboard::sideSize);
    if (i / Checkboard::sideSize == 1 || i / Checkboard::sideSize == 6) {
      (*this->squares)[i / Checkboard::sideSize][i % Checkboard::sideSize].registerPawn(std::make_shared<Soldier>(color));
    }
    if (i / Checkboard::sideSize == 0 || i / Checkboard::sideSize == 7) {
      switch (i % Checkboard::sideSize) {
        case 0:
        case 7:
          (*this->squares)[i / Checkboard::sideSize][i % Checkboard::sideSize].registerPawn(std::make_shared<Rook>(color));
          break;
        case 1:
        case 6:
          (*this->squares)[i / Checkboard::sideSize][i % Checkboard::sideSize].registerPawn(std::make_shared<Knight>(color));
          break;
        case 2:
        case 5:
          (*this->squares)[i / Checkboard::sideSize][i % Checkboard::sideSize].registerPawn(std::make_shared<Bishop>(color));
          break;
        case 4:
          (*this->squares)[i / Checkboard::sideSize][i % Checkboard::sideSize].registerPawn(std::make_shared<Queen>(color));
          break;
        default:
          (*this->squares)[i / Checkboard::sideSize][i % Checkboard::sideSize].registerPawn(std::make_shared<King>(color));
          break;
      }
    }
  }
}

const Squares *Checkboard::getSquares() const {
  return this->squares;
}

void Checkboard::draw() {
  graphics::Brush checkboard { graphics::Brush() };
  checkboard.fill_color[0] = { 1.0f };
  checkboard.fill_color[1] = { 1.0f };
  checkboard.fill_color[2] = { 1.0f };
  checkboard.fill_opacity = { 1.0f };
  checkboard.outline_width = { 0.0f };
  checkboard.outline_opacity = { 0.0f };
  checkboard.texture = getImagesPath() + "chessboard.png";
  graphics::drawRect(50.0f, 50.0f, 100.0f, 100.0f, checkboard);
}

void Checkboard::update(float ms) {
//  this->draw();
}

Checkboard::~Checkboard() {
  delete this->squares;
}
