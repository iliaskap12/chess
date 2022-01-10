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
#include <algorithm>
#include <App.h>

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
          [[fallthrough]];
        case 7:
          (*this->squares)[row][column]->registerPawn(std::make_shared<Rook>(color));
          break;
        case 1:
          [[fallthrough]];
        case 6:
          (*this->squares)[row][column]->registerPawn(std::make_shared<Knight>(color));
          break;
        case 2:
          [[fallthrough]];
        case 5:
          (*this->squares)[row][column]->registerPawn(std::make_shared<Bishop>(color));
          break;
        case 3:
          (*this->squares)[row][column]->registerPawn(std::make_shared<Queen>(color));
          break;
        default:
          (*this->squares)[row][column]->registerPawn(std::make_shared<King>(color));
          row == 0 ? (this->whiteKingId = { std::make_optional((*this->squares)[row][column]->getDrawingArea().getId()) })
                   : (this->blackKingId = { std::make_optional((*this->squares)[row][column]->getDrawingArea().getId()) });
          row == 0 ? (this->whiteKing = { (*this->squares)[row][column]->getPawn() })
                   : (this->blackKing = { (*this->squares)[row][column]->getPawn() });
          break;
      }
    }
  }
}

std::shared_ptr<Squares> Checkboard::getSquares() const {
  return this->squares;
}

void Checkboard::draw() {
  this->drawingArea.draw();
  for (const auto& row : *this->squares) {
    for (auto& square : row) {
      square->draw();
    }
  }
  if (this->movingSquare_ != nullptr) {
    this->movingSquare_->draw();
  }
}

void Checkboard::update(float ms) {
  for (const auto& row : *this->squares) {
    for (auto& square : row) {
      square->update(ms);
    }
  }
  if (this->movingSquare_ != nullptr) {
    this->movingSquare_->update(ms);
  }

  graphics::MouseState mouse { graphics::MouseState() };
  graphics::getMouseState(mouse);
  if (mouse.button_left_pressed && !this->drawingArea.clicked()) {
    this->markedSquares.clear();
    this->markedPawn = { nullptr };
    this->selectedPawn = { nullptr };
  }
}

void Checkboard::notify(Square *square) {
  if (this->movingSquare_ != nullptr && *this->movingSquare_ == *square) {
    return;
  }

  Game* game { static_cast<App*>(graphics::getUserData())->getGame() };

  if (this->markedSquares.empty()) {
    if (square->hasPawn()) {
      if (this->selectedPawn != nullptr) {
        this->selectedPawn = { nullptr };
        return;
      }

      if (!(game->isWhiteTurn() && square->getPawn()->getColor() == PawnColor::WHITE || !game->isWhiteTurn() && square->getPawn()->getColor() == PawnColor::BLACK)) {
        this->markedPawn = { nullptr };
        return;
      }

      this->markedPawn = { square->getPawn() };
      for (const auto &[rowIndex, columnIndex] : this->markedPawn->getAdvanceableSquares()) {
        this->markedSquares.push_back((*this->squares)[rowIndex][columnIndex]);
      }
    } else {
      this->markedPawn = { nullptr };
      this->selectedPawn = { nullptr };
      return;
    }
  } else {
    if (std::input_iterator auto result { std::ranges::find_if(
            this->markedSquares.begin(),
            this->markedSquares.end(),
            [&square](const std::shared_ptr<Square> &markedSquare) {
              return *markedSquare == *square;
            })
        };
        result != this->markedSquares.end()) {
      if (this->whiteKingId.has_value() && this->whiteKingId == this->markedPawn->getSquare()->getDrawingArea().getId()) {
        this->whiteKingId.reset();
        this->whiteKingId = { std::make_optional(square->getDrawingArea().getId()) };
      }
      if (this->blackKingId.has_value() && this->blackKingId == this->markedPawn->getSquare()->getDrawingArea().getId()) {
        this->blackKingId.reset();
        this->blackKingId = { std::make_optional(square->getDrawingArea().getId()) };
      }
      this->markedPawn->moveTo(square, this->markedPawn);
      game->setWhiteTurn(!game->isWhiteTurn());
    }
    this->markedPawn = { nullptr };
    this->markedSquares.clear();
  }

  this->selectedPawn == nullptr ? this->selectedPawn = { std::make_shared<Rectangle>(square->getDrawingArea()) } : this->selectedPawn = { nullptr };
}

std::pair<bool, std::optional<PawnColor>> Checkboard::getSquareInfo(std::pair<int, int> indexes) const {
  std::shared_ptr<Square> square { (*this->squares)[indexes.first][indexes.second] };
  bool hasPawn { square->hasPawn() };
  std::optional<PawnColor> pawnColor;
  if (hasPawn) {
    pawnColor = { square->getPawn()->getColor() };
  }

  return std::make_pair(hasPawn, pawnColor);
}

bool Checkboard::shouldMark(const Rectangle* rect) {
  if (std::input_iterator auto result { std::ranges::find_if(
          this->markedSquares.begin(),
          this->markedSquares.end(),
          [&rect](const std::shared_ptr<Square> &markedSquare) {
            return markedSquare->getDrawingArea() == *rect;
          })
      };
      result != this->markedSquares.end()) {
    return true;
  }
  return false;
}

const std::shared_ptr<Square> &Checkboard::getMovingSquare() const {
  return this->movingSquare_;
}

void Checkboard::setMovingSquare(Point leftBottom, const graphics::Brush &brush, Brush type) const {
  this->movingSquare_->initialize(leftBottom, brush, type);
}

void Checkboard::resetMovingSquare() {
  this->movingSquare_ = { nullptr };
  this->movingSquare_ = { std::make_shared<Square>(10, 10) };
}

bool Checkboard::amISelected(const Rectangle *rect) const {
  if (this->selectedPawn == nullptr) {
    return false;
  }

  if (*this->selectedPawn != *rect) {
    return false;
  }

  for (const auto& row : *this->squares) {
    for (auto& square : row) {
      if (square->getDrawingArea() == *rect && square->hasPawn()) {
        return true;
      }
    }
  }

  return false;
}

std::shared_ptr<Square> Checkboard::getSquare(const std::pair<int, int> &coordinates) const {
  for (const auto& row : *this->squares) {
    for (auto& square : row) {
      if (square->getRow() == coordinates.first && square->getColumn() == coordinates.second) {
        return square;
      }
    }
  }
  return nullptr;
}

bool Checkboard::amIinDanger(const Rectangle *rect) const {
  if (this->whiteKingId.has_value() && this->whiteKingId == rect->getId() && static_pointer_cast<King>(this->whiteKing)->isChecked()) {
    return true;
  }

  if (this->blackKingId.has_value() && this->blackKingId == rect->getId() && static_pointer_cast<King>(this->blackKing)->isChecked()) {
    return true;
  }

  return false;
}
