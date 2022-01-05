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

using Squares = std::array<std::array<std::shared_ptr<Square>, Checkboard::sideSize>, Checkboard::sideSize>;

Checkboard::Checkboard() {
  for (unsigned short int i = 0; i < Checkboard::sideSize * Checkboard::sideSize; ++i) {
    const std::size_t row { i / Checkboard::sideSize };
    constexpr unsigned short int firstRow { 0 };
    const size_t column { row == firstRow ? i : i % Checkboard::sideSize };
    const PawnColor color { row < 2 ? PawnColor::WHITE : PawnColor::BLACK };

    (*this->squares)[row][column] = { std::make_shared<Square>(row, column) };

    if (row == 1 || row == 6) {
      (*this->squares)[row][column]->registerPawn(std::make_shared<Soldier>(color));
    }

    if (row == 0 || row == 7) {
      switch (column) {
        case 0:
        case 7:
          (*this->squares)[row][column]->registerPawn(std::make_shared<Rook>(color));
          break;
        case 1:
        case 6:
          (*this->squares)[row][column]->registerPawn(std::make_shared<Knight>(color));
          break;
        case 2:
        case 5:
          (*this->squares)[row][column]->registerPawn(std::make_shared<Bishop>(color));
          break;
        case 3:
          (*this->squares)[row][column]->registerPawn(std::make_shared<Queen>(color));
          break;
        default:
          (*this->squares)[row][column]->registerPawn(std::make_shared<King>(color));
          break;
      }
    }
  }
}

std::shared_ptr<Squares> Checkboard::getSquares() const {
  return this->squares;
}

void Checkboard::draw() {
  graphics::Brush checkboard { graphics::Brush() };
  checkboard.fill_color[0] = { 1.0f };
  checkboard.fill_color[1] = { 1.0f };
  checkboard.fill_color[2] = { 1.0f };
  checkboard.fill_opacity = { 1.0f };
  checkboard.outline_width = { 10 };
  checkboard.outline_opacity = { 1.0f };
  checkboard.outline_color[0] = { 0.4588f };
  checkboard.outline_color[1] = { 0.2901f };
  checkboard.outline_color[2] = { 0.0f };
  graphics::drawRect(600, 500, 800, 800, checkboard);
  for (const auto& row : *this->squares) {
    for (auto& square : row) {
      square->draw();
    }
  }
}

void Checkboard::update(float ms) {
  for (const auto& row : *this->squares) {
    for (auto& square : row) {
      square->update(ms);
    }
  }
}
