#ifndef CHECKBOARD_H
#define CHECKBOARD_H

#include "Pawn.h"
#include "Square.h"
#include "King.h"
#include <array>
#include <optional>
#include <sounds/EndGameSound.h>
#include <sounds/CheckSound.h>

class Square;
class Pawn;

class Checkboard : public Drawable, public Updateable {
public:
  static const std::size_t sideSize = 8;

private:
  using Squares = std::array<std::array<std::shared_ptr<Square>, Checkboard::sideSize>, Checkboard::sideSize>;

  std::shared_ptr<Squares> squares{std::make_shared<Squares>()};
  std::vector<std::shared_ptr<Square>> markedSquares{std::vector<std::shared_ptr<Square>>()};
  std::weak_ptr<Pawn> markedPawn{std::weak_ptr<Pawn>()};
  std::shared_ptr<Square> movingSquare_{std::make_shared<Square>(10, 10)};
  std::weak_ptr<Rectangle> selectedPawn{std::weak_ptr<Rectangle>()};
  std::shared_ptr<Rectangle> drawingArea{std::make_shared<Rectangle>(Point(1000, 1550), 1200, 1200, Rectangle::colors.at(Brush::CHECKBOARD), Brush::CHECKBOARD)};
  std::optional<long> whiteKingId{std::optional<long>()};
  std::optional<long> blackKingId{std::optional<long>()};
  std::weak_ptr<Pawn> whiteKing{std::weak_ptr<Pawn>()};
  std::weak_ptr<Pawn> blackKing{std::weak_ptr<Pawn>()};
  std::weak_ptr<Pawn> whiteKingThreat{std::weak_ptr<Pawn>()};
  std::weak_ptr<Pawn> blackKingThreat{std::weak_ptr<Pawn>()};
  std::weak_ptr<Pawn> enPassantCapture{std::weak_ptr<Pawn>()};
  bool castling{false};
  bool leftRookCastling{false};
  bool rightRookCastling{false};
  bool pawnMoving{false};

public:
  Checkboard();

  // squares
  [[nodiscard]] std::weak_ptr<Squares> getSquares() const;
  [[nodiscard]] std::weak_ptr<Square> getSquare(const std::pair<int, int> &coordinates) const;
  [[nodiscard]] std::pair<bool, std::optional<PawnColor>> getSquareInfo(std::pair<int, int> indexes) const;
  bool markSquares(const std::shared_ptr<Square> &square);
  void moveKing(const std::shared_ptr<Square> &square);
  void movePawn(const std::shared_ptr<Square> &square);
  void resetReferenceCounts();
  void setReferenceCounts();
  void setBlockedPawns() const;
  void resetBlockedPawns() const;
  void tryMoveBlockedPawn(const std::shared_ptr<Square> &square, std::vector<std::shared_ptr<Square>> &squaresVec);
  void secureTheKing(const std::shared_ptr<Square> &square);
  std::vector<std::shared_ptr<Square>> tryBlockCheck(const std::pair<int, int> &pair, const std::shared_ptr<Pawn> &king, const std::shared_ptr<Pawn> &kingThreat);

  [[nodiscard]] bool shouldMark(const std::shared_ptr<Rectangle> &rect);
  [[nodiscard]] bool amISelected(const std::shared_ptr<Rectangle> &rect) const;
  [[nodiscard]] bool amIinDanger(const std::shared_ptr<Rectangle> &rect) const;
  [[nodiscard]] bool isKing(const PawnColor &color, const std::pair<int, int> &coordinates) const;
  void draw() override;
  void update(float ms) override;
  void notify(const std::shared_ptr<Square> &square);

  // moving square
  [[nodiscard]] const std::weak_ptr<Square> getMovingSquare() const;
  void setMovingSquare(const Point &leftBottom, const graphics::Brush &brush, const Brush &type) const;
  void resetMovingSquare();
  void checkmate(const PawnColor &winner);
  void checkForCheckmate(const std::shared_ptr<Pawn> &threat);
  std::weak_ptr<King> getKing(const PawnColor &color) const;
  void setPawnMoving(bool pawn_moving);
  bool isPawnMoving() const;
};

#endif// CHECKBOARD_H
