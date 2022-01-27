#include <App.h>
#include <algorithm>
#include <game/Bishop.h>
#include <game/Checkboard.h>
#include <game/King.h>
#include <game/Knight.h>
#include <game/PawnColor.h>
#include <game/Queen.h>
#include <game/Rook.h>
#include <game/Soldier.h>
#include <memory>
#include <sgg/graphics.h>

using Squares = std::array<std::array<std::shared_ptr<Square>, Checkboard::sideSize>, Checkboard::sideSize>;

Checkboard::Checkboard() {
  for (unsigned short int i = 0; i < Checkboard::sideSize * Checkboard::sideSize; ++i) {
    const std::size_t row{i / Checkboard::sideSize};
    constexpr unsigned short int firstRow{0};
    const size_t column{row == firstRow ? i : i % Checkboard::sideSize};
    const PawnColor color{row < 2 ? PawnColor::WHITE : PawnColor::BLACK};

    (*this->squares)[row][column] = {std::make_shared<Square>(row, column)};

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
          row == 0 ? (this->whiteKingId = {std::make_optional((*this->squares)[row][column]->getDrawingArea()->getId())})
                   : (this->blackKingId = {std::make_optional((*this->squares)[row][column]->getDrawingArea()->getId())});
          row == 0 ? (this->whiteKing = {(*this->squares)[row][column]->getPawn()})
                   : (this->blackKing = {(*this->squares)[row][column]->getPawn()});
          break;
      }
    }
  }
}

std::shared_ptr<Squares> Checkboard::getSquares() const {
  return this->squares;
}

void Checkboard::draw() {
  if (const auto *const game{static_cast<App *>(graphics::getUserData())->getGame()}; (nullptr == game) || (game->getCheckboard() == nullptr)) {
    return;
  }

  this->drawingArea.draw();
  for (const auto &row: *this->squares) {
    for (auto &square: row) {
      square->draw();
    }
  }
  if (this->movingSquare_ != nullptr) {
    this->movingSquare_->draw();
  }
}

void Checkboard::resetReferenceCounts() {
  this->whiteKingThreat = {nullptr};
  this->blackKingThreat = {nullptr};
  for (const auto &row: *this->squares) {
    for (auto &square: row) {
      square->resetDangerReferenceCount();
    }
  }
}

void Checkboard::setReferenceCounts() {
  this->resetReferenceCounts();
  for (const auto &row: *this->squares) {
    for (auto &square: row) {
      if (!square->hasPawn()) continue;
      auto holdingSquares{square->getPawn()->getHoldingSquares()};
      std::ranges::for_each(holdingSquares.begin(), holdingSquares.end(), [this, &square](const auto &item) {
        this->getSquare(item)->increaseDangerReferenceCount(square->getPawn()->getColor());
        auto king{square->getPawn()->getColor() == PawnColor::WHITE ? this->blackKing : this->whiteKing};
        if (*this->getSquare(item) == *king->getSquare()) {
          (square->getPawn()->getColor() == PawnColor::WHITE ? (this->blackKingThreat = {square->getPawn()}) : (this->whiteKingThreat = {square->getPawn()}));
        }
      });
    }
  }
}

void Checkboard::resetBlockedPawns() const {
  for (const auto &row: *this->squares) {
    for (auto &square: row) {
      if (square->hasPawn()) {
        square->getPawn()->unblock();
      }
    }
  }
}

void Checkboard::setBlockedPawns() const {
  this->resetBlockedPawns();
  for (const auto &row: *this->squares) {
    for (auto &square: row) {
      if (!square->hasPawn()) continue;
      if (auto pawn{square->getPawn()->getBlockedPawn()}; pawn != nullptr) {
        pawn->block();
        pawn->blockedBy(square->getPawn());
      }
    }
  }
}

void Checkboard::update(float ms) {
  const auto *const game{static_cast<App *>(graphics::getUserData())->getGame()};
  if ((nullptr == game) || (game->getCheckboard() == nullptr)) {
    return;
  }

  this->setReferenceCounts();
  this->setBlockedPawns();
  for (const auto &row: *this->squares) {
    for (auto &square: row) {
      square->update(ms);
    }
  }

  if (this->movingSquare_ != nullptr) {
    this->movingSquare_->update(ms);
  }

  graphics::MouseState mouse{graphics::MouseState()};
  graphics::getMouseState(mouse);
  if (mouse.button_left_pressed && !this->drawingArea.clicked()) {
    this->markedSquares.clear();
    this->markedPawn = {nullptr};
    this->selectedPawn = {nullptr};
  }
}

void Checkboard::notify(Square *square) {
  if ((this->movingSquare_ != nullptr) && (*this->movingSquare_ == *square)) {
    return;
  }

  if (this->markedSquares.empty()) {
    if (const bool shouldExit{this->markSquares(square)}; shouldExit) {
      return;
    }
  } else {
    this->movePawn(square);
  }

  if (this->selectedPawn == nullptr) {
    this->selectedPawn = {square->getDrawingArea()};
  } else {
    this->selectedPawn = {nullptr};
  }
}

std::pair<bool, std::optional<PawnColor>> Checkboard::getSquareInfo(std::pair<int, int> indexes) const {
  std::shared_ptr<Square> square{(*this->squares)[indexes.first][indexes.second]};
  bool hasPawn{square->hasPawn()};
  std::optional<PawnColor> pawnColor;
  if (hasPawn) {
    pawnColor = {square->getPawn()->getColor()};
  }

  return std::make_pair(hasPawn, pawnColor);
}

bool Checkboard::shouldMark(const Rectangle *rect) {
  if (std::input_iterator auto result{std::ranges::find_if(
          this->markedSquares.begin(),
          this->markedSquares.end(),
          [&rect](const std::shared_ptr<Square> &markedSquare) {
            return *markedSquare->getDrawingArea() == *rect;
          })};
      result != this->markedSquares.end()) {
    return true;
  }
  return false;
}

bool Checkboard::markSquares(const Square *square) {
  if (const Game * game{static_cast<App *>(graphics::getUserData())->getGame()}; square->hasPawn()) {
    if (this->selectedPawn != nullptr) {
      this->selectedPawn = {nullptr};
      return true;
    }

    PawnColor squareColor{square->getPawn()->getColor()};
    auto king{squareColor == PawnColor::WHITE ? this->whiteKing : this->blackKing};
    if (!(game->isWhiteTurn() && squareColor == PawnColor::WHITE || !game->isWhiteTurn() && squareColor == PawnColor::BLACK)) {
      this->markedPawn = {nullptr};
      return true;
    }

    this->markedPawn = {square->getPawn()};

    if (std::static_pointer_cast<King>(king)->isChecked()) {
      this->secureTheKing(square);
      if (this->markedSquares.empty()) {
        this->markedPawn = {nullptr};
        this->selectedPawn = {nullptr};
        return true;
      } else {
        return false;
      }
    }

    if (square->getPawn()->isBlocked()) {
      this->tryMoveBlockedPawn(square);
      if (this->markedSquares.empty()) {
        this->markedPawn = {nullptr};
        this->selectedPawn = {nullptr};
        return true;
      } else {
        return false;
      }
    }

    for (const auto &pair: this->markedPawn->getAdvanceableSquares()) {
      this->markedSquares.push_back(this->getSquare(pair));
    }
  } else {
    this->markedPawn = {nullptr};
    this->selectedPawn = {nullptr};
    return true;
  }
  return false;
}

void Checkboard::moveKing(const Square *square) {
  if (this->whiteKingId.has_value() && this->whiteKingId == this->markedPawn->getSquare()->getDrawingArea()->getId()) {
    this->whiteKingId.reset();
    this->whiteKingId = {std::make_optional(square->getDrawingArea()->getId())};
  }
  if (this->blackKingId.has_value() && this->blackKingId == this->markedPawn->getSquare()->getDrawingArea()->getId()) {
    this->blackKingId.reset();
    this->blackKingId = {std::make_optional(square->getDrawingArea()->getId())};
  }
}

void Checkboard::movePawn(Square *square) {
  if (std::input_iterator auto result{std::ranges::find_if(
          this->markedSquares.begin(),
          this->markedSquares.end(),
          [&square](const std::shared_ptr<Square> &markedSquare) {
            return *markedSquare == *square;
          })};
      result != this->markedSquares.end()) {
    this->moveKing(square);
    this->markedPawn->moveTo(square, this->markedPawn);
    Game *game{static_cast<App *>(graphics::getUserData())->getGame()};
    game->setWhiteTurn(!game->isWhiteTurn());
  }
  this->markedPawn = {nullptr};
  this->markedSquares.clear();
}

const std::shared_ptr<Square> &Checkboard::getMovingSquare() const {
  return this->movingSquare_;
}

void Checkboard::setMovingSquare(Point leftBottom, const graphics::Brush &brush, Brush type) const {
  this->movingSquare_->initialize(leftBottom, brush, type);
}

void Checkboard::resetMovingSquare() {
  this->movingSquare_ = {nullptr};
  this->movingSquare_ = {std::make_shared<Square>(10, 10)};
}

bool Checkboard::amISelected(const Rectangle *rect) const {
  if (this->selectedPawn == nullptr) {
    return false;
  }

  if (*this->selectedPawn != *rect) {
    return false;
  }

  for (const auto &row: *this->squares) {
    for (auto &square: row) {
      if (*square->getDrawingArea() == *rect && square->hasPawn()) {
        return true;
      }
    }
  }

  return false;
}

std::shared_ptr<Square> Checkboard::getSquare(const std::pair<int, int> &coordinates) const {
  for (const auto &row: *this->squares) {
    for (auto &square: row) {
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

bool Checkboard::isKing(PawnColor color, const std::pair<int, int> &coordinates) const {
  if (color == PawnColor::WHITE) {
    return *this->whiteKing->getSquare() == *this->getSquare(coordinates);
  }
  return *this->blackKing->getSquare() == *this->getSquare(coordinates);
}

void Checkboard::tryMoveBlockedPawn(const Square *square) {
  auto advanceableSquares{this->markedPawn->getAdvanceableSquares()};
  auto king{this->markedPawn->getColor() == PawnColor::WHITE ? this->whiteKing : this->blackKing};

  const int kingsRow{king->getSquare()->getRow()};
  const int kingsColumn{king->getSquare()->getColumn()};
  const int blockingPawnRow{square->getPawn()->getBlockingPawn()->getSquare()->getRow()};
  const int blockingPawnColumn{square->getPawn()->getBlockingPawn()->getSquare()->getColumn()};
  const int blockingPawnUpwardsDiagonal{blockingPawnRow - blockingPawnColumn};
  const int blockingPawnDownwardsDiagonal{blockingPawnRow + blockingPawnColumn};

  std::ranges::for_each(advanceableSquares,
                        [&square,
                         this,
                         &kingsRow,
                         &kingsColumn,
                         &blockingPawnRow,
                         &blockingPawnColumn,
                         &blockingPawnUpwardsDiagonal,
                         &blockingPawnDownwardsDiagonal](const std::pair<int, int> &pair) {
                          const bool sameRow{blockingPawnRow == pair.first && kingsRow == pair.first};
                          const bool sameColumn{blockingPawnColumn == pair.second && kingsColumn == pair.second};
                          const bool sameUpwardsDiagonal{(blockingPawnUpwardsDiagonal == pair.first - pair.second) && (kingsRow - kingsColumn == pair.first - pair.second)};
                          const bool sameDownwardsDiagonal{(blockingPawnDownwardsDiagonal == pair.first + pair.second) && (kingsRow + kingsColumn == pair.first + pair.second)};
                          const bool canCapture{*square->getPawn()->getBlockingPawn()->getSquare() == *this->getSquare(pair)};

                          if (canCapture) {
                            this->markedSquares.push_back(std::make_shared<Square>(*this->markedPawn->getBlockingPawn()->getSquare()));
                          } else if (sameRow || sameColumn || sameUpwardsDiagonal || sameDownwardsDiagonal) {
                            this->markedSquares.push_back(this->getSquare(pair));
                          }
                        });
}

void Checkboard::secureTheKing(const Square *square) {
  std::shared_ptr<Pawn> king{square->getPawn()->getColor() == PawnColor::WHITE ? this->whiteKing : this->blackKing};
  auto kingThreat{square->getPawn()->getColor() == PawnColor::WHITE ? this->whiteKingThreat : this->blackKingThreat};
  if (*king->getSquare() == *square) {
    auto advanceableSquares{king->getAdvanceableSquares()};
    std::ranges::for_each(advanceableSquares, [this](const std::pair<int, int> &pair) {
      this->markedSquares.push_back(this->getSquare(pair));
    });
  } else {
    auto advanceableSquares{square->getPawn()->getAdvanceableSquares()};
    std::ranges::for_each(advanceableSquares, [this, &kingThreat, &king](const std::pair<int, int> &pair) {
      if (*kingThreat->getSquare() == *this->getSquare(pair)) {
        this->markedSquares.push_back(this->getSquare(pair));
      } else {
        std::ranges::for_each(this->tryBlockCheck(pair, king, kingThreat), [this](const std::shared_ptr<Square> step) {
          this->markedSquares.push_back(step);
        });
      }
    });
  }
}

std::vector<std::shared_ptr<Square>> Checkboard::tryBlockCheck(const std::pair<int, int> &pair, const std::shared_ptr<Pawn> &king, const std::shared_ptr<Pawn> &kingThreat) {
  const int kingsRow{king->getSquare()->getRow()};
  const int kingsColumn{king->getSquare()->getColumn()};
  const int kingsUpwardsDiagonal{kingsRow - kingsColumn};
  const int kingsDownwardsDiagonal{kingsRow + kingsColumn};
  const int kingsThreatRow{kingThreat->getSquare()->getRow()};
  const int kingsThreatColumn{kingThreat->getSquare()->getColumn()};
  const int kingsThreatUpwardsDiagonal{kingsThreatRow - kingsThreatColumn};
  const int kingsThreatDownwardsDiagonal{kingsThreatRow + kingsThreatColumn};

  const bool sameRow{kingsThreatRow == kingsRow && kingsRow == pair.first};
  const bool sameColumn{kingsThreatColumn == kingsColumn && kingsColumn == pair.second};
  const bool sameUpwardsDiagonal{(kingsThreatUpwardsDiagonal == kingsUpwardsDiagonal) && (kingsUpwardsDiagonal == pair.first - pair.second)};
  const bool sameDownwardsDiagonal{(kingsThreatDownwardsDiagonal == kingsDownwardsDiagonal) && (kingsDownwardsDiagonal == pair.first + pair.second)};

  const bool sameRowAndBetween{sameRow && ((pair.second > kingsColumn && pair.second <= kingsThreatColumn) || (pair.second < kingsColumn && pair.second >= kingsThreatColumn))};

  const bool sameColumnAndBetween{sameColumn && ((pair.first > kingsRow && pair.first <= kingsThreatRow) || (pair.first < kingsRow && pair.first >= kingsThreatRow))};

  const bool sameDiagonalAndBetween{(sameUpwardsDiagonal || sameDownwardsDiagonal) && ((pair.second > kingsColumn && pair.second <= kingsThreatColumn) || (pair.second < kingsColumn && pair.second >= kingsThreatColumn))};

  auto squaresToMark{std::vector<std::shared_ptr<Square>>()};
  if (sameRowAndBetween || sameColumnAndBetween || sameDiagonalAndBetween) {
    squaresToMark.push_back(this->getSquare(pair));
  }
  return squaresToMark;
}

void Checkboard::checkmate(PawnColor winner) {
  static_cast<App *>(graphics::getUserData())->getGame()->end(winner);
}

void Checkboard::checkForCheckmate(const std::shared_ptr<Pawn> &threat) {
  auto game{static_cast<App *>(graphics::getUserData())->getGame()};
  std::shared_ptr<Pawn> king{nullptr};
  bool shouldCheckmate{true};

  const int blackRefCount{threat->getSquare()->getDangerReferenceCount(PawnColor::BLACK)};
  const int whiteRefCount{threat->getSquare()->getDangerReferenceCount(PawnColor::WHITE)};

  if (threat->getColor() == PawnColor::WHITE) {
    if (blackRefCount > whiteRefCount) {
      shouldCheckmate = {false};
    }
    king = {this->blackKing};
  } else {
    if (whiteRefCount > blackRefCount) {
      shouldCheckmate = {false};
    }
    king = {this->whiteKing};
  }

  if (!std::static_pointer_cast<King>(king)->isChecked()) {
    shouldCheckmate = {false};
  }

  if (const auto advanceableSquares{king->getAdvanceableSquares()}; !advanceableSquares.empty()) {
    shouldCheckmate = {false};
  }

  if (!shouldCheckmate) {
    game->playCheckSound();
    return;
  }

  for (const auto &row: *this->squares) {
    for (auto &square: row) {
      if (!square->hasPawn() || square->getPawn()->getColor() != king->getColor()) {
        continue;
      }
      auto availableSquares{std::vector<std::shared_ptr<Square>>()};
      auto advanceableSquares{square->getPawn()->getAdvanceableSquares()};
      std::ranges::for_each(advanceableSquares, [this, &threat, &king, &availableSquares](const std::pair<int, int> &pair) {
        if (*threat->getSquare() == *this->getSquare(pair)) {
          availableSquares.push_back(this->getSquare(pair));
        } else {
          std::ranges::for_each(this->tryBlockCheck(pair, king, threat), [&availableSquares](const std::shared_ptr<Square> step) {
            availableSquares.push_back(step);
          });
        }
      });

      if (!availableSquares.empty()) {
        game->playCheckSound();
        return;
      }
    }
  }
  this->checkmate(threat->getColor());
}

std::shared_ptr<King> Checkboard::getKing(PawnColor color) const {
  if (PawnColor::WHITE == color) {
    return std::static_pointer_cast<King>(this->whiteKing);
  } else {
    return std::static_pointer_cast<King>(this->blackKing);
  }
}
