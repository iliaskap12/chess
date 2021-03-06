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
#include "graphics/PlayingScreen.h"

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
          row == 0 ? (this->whiteKingId = {std::make_optional((*this->squares)[row][column]->getDrawingArea().lock()->getId())})
                   : (this->blackKingId = {std::make_optional((*this->squares)[row][column]->getDrawingArea().lock()->getId())});
          row == 0 ? (this->whiteKing = {(*this->squares)[row][column]->getPawn()})
                   : (this->blackKing = {(*this->squares)[row][column]->getPawn()});
          break;
      }
    }
  }
}

std::weak_ptr<Squares> Checkboard::getSquares() const {
  return this->squares;
}

void Checkboard::draw() {
  this->drawingArea->draw();
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
  this->whiteKingThreat.reset();
  this->blackKingThreat.reset();
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
      for (const auto &item: holdingSquares) {
        this->getSquare(item).lock()->increaseDangerReferenceCount(square->getPawn()->getColor());
        auto king{square->getPawn()->getColor() == PawnColor::WHITE ? this->blackKing : this->whiteKing};
        if (*this->getSquare(item).lock() == *king.lock()->getSquare().lock()) {
          (square->getPawn()->getColor() == PawnColor::WHITE ? (this->blackKingThreat = {square->getPawn()}) : (this->whiteKingThreat = {square->getPawn()}));
        }
      }
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
      if (auto pawn{square->getPawn()->getBlockedPawn()}; !pawn.expired()) {
        pawn.lock()->block();
        pawn.lock()->blockedBy(square->getPawn());
      }
    }
  }
}

void Checkboard::update(float ms) {
  graphics::MouseState mouse{graphics::MouseState()};
  graphics::getMouseState(mouse);


  if (this->pawnMoving && mouse.button_left_pressed) {
    return;
  }

  this->setReferenceCounts();
  this->setBlockedPawns();

  for (const auto &row: *this->squares) {
    for (auto &square: row) {
      square->update(ms);
    }
  }

  if (!this->pawnMoving && this->movingSquare_ != nullptr) {
    this->movingSquare_->update(ms);
  }

  if (mouse.button_left_pressed && !this->drawingArea->clicked()) {
    this->markedSquares.clear();
    this->markedPawn.reset();
    this->selectedPawn.reset();
  }
}

void Checkboard::notify(const std::shared_ptr<Square> &square) {
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

  if (this->selectedPawn.expired()) {
    this->selectedPawn = {square->getDrawingArea()};
  } else {
    this->selectedPawn.reset();
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

bool Checkboard::shouldMark(const std::shared_ptr<Rectangle> &rect) {
  if (std::input_iterator auto result{std::ranges::find_if(
          this->markedSquares.begin(),
          this->markedSquares.end(),
          [&rect](const std::shared_ptr<Square> &markedSquare) {
            return *markedSquare->getDrawingArea().lock() == *rect;
          })};
      result != this->markedSquares.end()) {
    return true;
  }
  return false;
}

bool Checkboard::markSquares(const std::shared_ptr<Square> &square) {
  if (const auto game{static_cast<App *>(graphics::getUserData())->getGame()}; square->hasPawn()) {
    if (!this->selectedPawn.expired()) {
      this->selectedPawn.reset();
      return true;
    }

    PawnColor squareColor{square->getPawn()->getColor()};
    auto king{squareColor == PawnColor::WHITE ? this->whiteKing : this->blackKing};
    if (!(game.lock()->isWhiteTurn() && squareColor == PawnColor::WHITE || !game.lock()->isWhiteTurn() && squareColor == PawnColor::BLACK)) {
      this->markedPawn.reset();
      return true;
    }

    this->markedPawn = {square->getPawn()};

    if (std::static_pointer_cast<King>(king.lock())->isChecked()) {
      this->secureTheKing(square);
      if (this->markedSquares.empty()) {
        this->markedPawn.reset();
        this->selectedPawn.reset();
        return true;
      } else {
        return false;
      }
    }

    if (square->getPawn()->isBlocked()) {
      this->tryMoveBlockedPawn(square, this->markedSquares);
      if (this->markedSquares.empty()) {
        this->markedPawn.reset();
        this->selectedPawn.reset();
        return true;
      } else {
        return false;
      }
    }

    for (const auto &pair: this->markedPawn.lock()->getAdvanceableSquares()) {
      this->markedSquares.push_back(this->getSquare(pair).lock());
    }
  } else {
    this->markedPawn.reset();
    this->selectedPawn.reset();
    return true;
  }
  return false;
}

void Checkboard::moveKing(const std::shared_ptr<Square> &square) {
  if (this->whiteKingId.has_value() && this->whiteKingId == this->markedPawn.lock()->getSquare().lock()->getDrawingArea().lock()->getId()) {
    this->whiteKingId.reset();
    this->whiteKingId = {std::make_optional(square->getDrawingArea().lock()->getId())};
  }
  if (this->blackKingId.has_value() && this->blackKingId == this->markedPawn.lock()->getSquare().lock()->getDrawingArea().lock()->getId()) {
    this->blackKingId.reset();
    this->blackKingId = {std::make_optional(square->getDrawingArea().lock()->getId())};
  }
}

void Checkboard::movePawn(const std::shared_ptr<Square> &square) {
  if (std::input_iterator auto result{std::ranges::find_if(
          this->markedSquares.begin(),
          this->markedSquares.end(),
          [&square](const std::shared_ptr<Square> &markedSquare) {
            return *markedSquare == *square;
          })};
      result != this->markedSquares.end()) {
    this->moveKing(square);
    if (const auto rook{std::dynamic_pointer_cast<Rook>(this->markedPawn.lock())}; (nullptr != rook) && (!rook->getMoved())) {
      std::shared_ptr<King> currentKing{nullptr};
      if (this->markedPawn.lock()->getColor() == PawnColor::WHITE) {
        currentKing = {std::static_pointer_cast<King>(this->whiteKing.lock())};
      } else {
        currentKing = {std::static_pointer_cast<King>(this->blackKing.lock())};
      }
      currentKing->setRookMoved(rook->getSquare().lock()->getColumn());
      rook->setMoved();
    }

    if (const auto king{std::dynamic_pointer_cast<King>(this->markedPawn.lock())}; (nullptr != king) && (!king->moved())) {
      king->setMoved();
      this->leftRookCastling = {2 == square->getColumn()};
      this->rightRookCastling = {6 == square->getColumn()};
      if (this->leftRookCastling || this->rightRookCastling) {
        this->castling = {true};
      }
    }

    if (const auto soldier{std::dynamic_pointer_cast<Soldier>(this->markedPawn.lock())}; nullptr != soldier) {
      bool firstMove{2 == std::abs(square->getRow() - soldier->getSquare().lock()->getRow())};
      if (firstMove) {
        soldier->setEnPassant(true);
      } else {
        soldier->setEnPassant(false);
      }
    }

    // soldier != markedPawn, if en passant, set en passant = false
    for (const auto &row: *this->squares) {
      for (auto &soldierSquare: row) {
        if (*soldierSquare == *this->markedPawn.lock()->getSquare().lock()) {
          continue;
        }

        if (soldierSquare->hasPawn()) {
          const auto soldier{std::dynamic_pointer_cast<Soldier>(soldierSquare->getPawn())};
          const int currectRow{this->markedPawn.lock()->getSquare().lock()->getRow()};
          const int currectColumn{this->markedPawn.lock()->getSquare().lock()->getColumn()};

          const int soldierDirection{square->getColumn() - currectColumn};

          if ((soldier != nullptr) && (soldier->isEnPassant())) {
            const auto sameRow{std::abs(soldier->getSquare().lock()->getRow() - currectRow) == 0};
            const auto nextColumn{std::abs(soldierDirection) == 1};
            const auto diagonalMove{(soldier->getSquare().lock()->getColumn() - square->getColumn()) == 0};
            if ((std::dynamic_pointer_cast<Soldier>(this->markedPawn.lock()) != nullptr) && (sameRow && nextColumn && diagonalMove)) {
              this->enPassantCapture = {soldier};
            }
            soldier->setEnPassant(false);
          }
        }
      }
    }

    this->pawnMoving = {true};
    this->markedPawn.lock()->moveTo(square, this->markedPawn.lock());
    if (!this->castling) {
      auto game{static_cast<App *>(graphics::getUserData())->getGame()};
      game.lock()->setWhiteTurn(!game.lock()->isWhiteTurn());
    }
  }
  this->markedPawn.reset();
  this->markedSquares.clear();
}

const std::weak_ptr<Square> Checkboard::getMovingSquare() const {
  return this->movingSquare_;
}

void Checkboard::setMovingSquare(const Point &leftBottom, const graphics::Brush &brush, const Brush &type) const {
  this->movingSquare_->initialize(leftBottom, brush, type);
}

void Checkboard::resetMovingSquare() {
  this->movingSquare_.reset();
  this->movingSquare_ = {std::make_shared<Square>(10, 10)};
}

bool Checkboard::amISelected(const std::shared_ptr<Rectangle> &rect) const {
  if (this->selectedPawn.expired()) {
    return false;
  }

  if (*this->selectedPawn.lock() != *rect) {
    return false;
  }

  for (const auto &row: *this->squares) {
    for (auto &square: row) {
      if (*square->getDrawingArea().lock() == *rect && square->hasPawn()) {
        return true;
      }
    }
  }

  return false;
}

std::weak_ptr<Square> Checkboard::getSquare(const std::pair<int, int> &coordinates) const {
  for (const auto &row: *this->squares) {
    for (auto &square: row) {
      if (square->getRow() == coordinates.first && square->getColumn() == coordinates.second) {
        return square;
      }
    }
  }
  return std::weak_ptr<Square>();
}

bool Checkboard::amIinDanger(const std::shared_ptr<Rectangle> &rect) const {
  if (this->whiteKingId.has_value() && this->whiteKingId == rect->getId() && static_pointer_cast<King>(this->whiteKing.lock())->isChecked()) {
    return true;
  }

  if (this->blackKingId.has_value() && this->blackKingId == rect->getId() && static_pointer_cast<King>(this->blackKing.lock())->isChecked()) {
    return true;
  }

  return false;
}

bool Checkboard::isKing(const PawnColor &color, const std::pair<int, int> &coordinates) const {
  if (color == PawnColor::WHITE) {
    return *this->whiteKing.lock()->getSquare().lock() == *this->getSquare(coordinates).lock();
  }
  return *this->blackKing.lock()->getSquare().lock() == *this->getSquare(coordinates).lock();
}

void Checkboard::tryMoveBlockedPawn(const std::shared_ptr<Square> &square, std::vector<std::shared_ptr<Square>> &squaresVec) {
  auto advanceableSquares{square->getPawn()->getAdvanceableSquares()};
  auto king{square->getPawn()->getColor() == PawnColor::WHITE ? this->whiteKing : this->blackKing};

  const int kingsRow{king.lock()->getSquare().lock()->getRow()};
  const int kingsColumn{king.lock()->getSquare().lock()->getColumn()};
  const int blockingPawnRow{square->getPawn()->getBlockingPawn().lock()->getSquare().lock()->getRow()};
  const int blockingPawnColumn{square->getPawn()->getBlockingPawn().lock()->getSquare().lock()->getColumn()};
  const int blockingPawnUpwardsDiagonal{blockingPawnRow - blockingPawnColumn};
  const int blockingPawnDownwardsDiagonal{blockingPawnRow + blockingPawnColumn};

  std::ranges::for_each(advanceableSquares,
                        [&square,
                         this,
                         &squaresVec,
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
                          const bool canCapture{*square->getPawn()->getBlockingPawn().lock()->getSquare().lock() == *this->getSquare(pair).lock()};

                          if (canCapture) {
                            squaresVec.push_back(std::make_shared<Square>(*square->getPawn()->getBlockingPawn().lock()->getSquare().lock()));
                          } else if (sameRow || sameColumn || sameUpwardsDiagonal || sameDownwardsDiagonal) {
                            squaresVec.push_back(this->getSquare(pair).lock());
                          }
                        });
}

void Checkboard::secureTheKing(const std::shared_ptr<Square> &square) {
  std::shared_ptr<Pawn> king{square->getPawn()->getColor() == PawnColor::WHITE ? this->whiteKing : this->blackKing};
  auto kingThreat{square->getPawn()->getColor() == PawnColor::WHITE ? this->whiteKingThreat : this->blackKingThreat};
  if (*king->getSquare().lock() == *square) {
    auto advanceableSquares{king->getAdvanceableSquares()};
    std::ranges::for_each(advanceableSquares, [this](const std::pair<int, int> &pair) {
      this->markedSquares.push_back(this->getSquare(pair).lock());
    });
  } else {
    auto advanceableSquares{square->getPawn()->getAdvanceableSquares()};
    std::ranges::for_each(advanceableSquares, [&square, this, &kingThreat, &king](const std::pair<int, int> &pair) {
      if (*kingThreat.lock()->getSquare().lock() == *this->getSquare(pair).lock()) {
        this->markedSquares.push_back(this->getSquare(pair).lock());
      } else {
        if (square->getPawn()->isBlocked()) {
          return;
        }
        std::ranges::for_each(this->tryBlockCheck(pair, king, kingThreat.lock()), [this](const std::shared_ptr<Square> step) {
          this->markedSquares.push_back(step);
        });
      }
    });
  }
}

std::vector<std::shared_ptr<Square>> Checkboard::tryBlockCheck(const std::pair<int, int> &pair, const std::shared_ptr<Pawn> &king, const std::shared_ptr<Pawn> &kingThreat) {
  const int kingsRow{king->getSquare().lock()->getRow()};
  const int kingsColumn{king->getSquare().lock()->getColumn()};
  const int kingsUpwardsDiagonal{kingsRow - kingsColumn};
  const int kingsDownwardsDiagonal{kingsRow + kingsColumn};
  const int kingsThreatRow{kingThreat->getSquare().lock()->getRow()};
  const int kingsThreatColumn{kingThreat->getSquare().lock()->getColumn()};
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
    squaresToMark.push_back(this->getSquare(pair).lock());
  }
  return squaresToMark;
}

void Checkboard::checkmate(const PawnColor &winner) {
  static_cast<App *>(graphics::getUserData())->getGame().lock()->end(winner);
}

void Checkboard::checkForCheckmate(const std::shared_ptr<Pawn> &threat) {
  auto game{static_cast<App *>(graphics::getUserData())->getGame()};

  std::shared_ptr<Pawn> king{nullptr};
  bool shouldCheckmate{true};

  this->setReferenceCounts();
  const int blackRefCount{threat->getSquare().lock()->getDangerReferenceCount(PawnColor::BLACK)};
  const int whiteRefCount{threat->getSquare().lock()->getDangerReferenceCount(PawnColor::WHITE)};

  if (threat->getColor() == PawnColor::WHITE) {
    if (blackRefCount > whiteRefCount) {
      shouldCheckmate = {false};
    }
    king = {this->blackKing.lock()};
  } else {
    if (whiteRefCount > blackRefCount) {
      shouldCheckmate = {false};
    }
    king = {this->whiteKing.lock()};
  }

  if (!std::static_pointer_cast<King>(king)->isChecked()) {
    shouldCheckmate = {false};
  }

  if (const auto advanceableSquares{king->getAdvanceableSquares()}; !advanceableSquares.empty()) {
    shouldCheckmate = {false};
  }

  if (!shouldCheckmate) {
    game.lock()->playCheckSound();
    return;
  }

  for (const auto &row: *this->squares) {
    for (auto &square: row) {
      if (!square->hasPawn() || square->getPawn()->getColor() != king->getColor()) {
        continue;
      }
      auto availableSquares{std::vector<std::shared_ptr<Square>>()};
      auto advanceableSquares{square->getPawn()->getAdvanceableSquares()};

      if (square->getPawn()->isBlocked()) {
        continue;
      }

      std::ranges::for_each(advanceableSquares, [this, &threat, &king, &availableSquares](const std::pair<int, int> &pair) {
        if (*threat->getSquare().lock() == *this->getSquare(pair).lock()) {
          availableSquares.push_back(this->getSquare(pair).lock());
        } else {
          std::ranges::for_each(this->tryBlockCheck(pair, king, threat), [&availableSquares](const std::shared_ptr<Square> step) {
            availableSquares.push_back(step);
          });
        }
      });

      if (!availableSquares.empty()) {
        game.lock()->playCheckSound();
        return;
      }
    }
  }
  this->checkmate(threat->getColor());
}

std::weak_ptr<King> Checkboard::getKing(const PawnColor &color) const {
  if (PawnColor::WHITE == color) {
    return std::static_pointer_cast<King>(this->whiteKing.lock());
  } else {
    return std::static_pointer_cast<King>(this->blackKing.lock());
  }
}

void Checkboard::setPawnMoving(bool pawn_moving) {
  this->pawnMoving = pawn_moving;
  if (!this->enPassantCapture.expired()) {
    std::shared_ptr<PlayingScreen> playingScreen{static_pointer_cast<PlayingScreen>(static_cast<App *>(graphics::getUserData())->getScreen())};
    std::shared_ptr<Square> square{playingScreen->getSquare(this->enPassantCapture.lock())};
    if (square != nullptr) {
      square->setRow(20);
      this->enPassantCapture.lock()->getSquare().lock()->unregisterPawn();
      square->registerPawn(this->enPassantCapture.lock());
    } else {
      this->enPassantCapture.lock()->getSquare().lock()->unregisterPawn();
    }
    this->enPassantCapture.lock()->playCaptureSound();
    this->enPassantCapture.reset();
  }

  auto game{static_cast<App *>(graphics::getUserData())->getGame()};
  if (this->castling) {
    this->castling = {false};
    int row;
    if (game.lock()->isWhiteTurn()) {
      row = {0};
    } else {
      row = {7};
    }
    if (this->leftRookCastling) {
      auto rook{std::dynamic_pointer_cast<Rook>(this->getSquare(std::make_pair(row, 0)).lock()->getPawn())};
      rook->moveTo((*this->squares)[row][3], rook);
      this->pawnMoving = {true};
    }
    if (this->rightRookCastling) {
      auto rook{std::dynamic_pointer_cast<Rook>(this->getSquare(std::make_pair(row, 7)).lock()->getPawn())};
      rook->moveTo((*this->squares)[row][5], rook);
      this->pawnMoving = {true};
    }
    game.lock()->setWhiteTurn(!game.lock()->isWhiteTurn());
  }
}

bool Checkboard::isPawnMoving() const {
  return this->pawnMoving;
}
