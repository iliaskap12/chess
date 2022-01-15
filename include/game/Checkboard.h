
#ifndef CHECKBOARD_H
#define CHECKBOARD_H

#include "Pawn.h"
#include "Square.h"
#include <array>
#include <optional>

class Square;
class Pawn;

class Checkboard : public Drawable, public Updateable {
public:
  static const std::size_t sideSize = 8;

private:
  using Squares = std::array<std::array<std::shared_ptr<Square>, Checkboard::sideSize>, Checkboard::sideSize>;

  std::shared_ptr<Squares> squares{std::make_shared<Squares>()};
  std::vector<std::shared_ptr<Square>> markedSquares{std::vector<std::shared_ptr<Square>>()};
  std::shared_ptr<Pawn> markedPawn{nullptr};
  std::shared_ptr<Square> movingSquare_{std::make_shared<Square>(10, 10)};
  std::shared_ptr<Rectangle> selectedPawn{nullptr};
  Rectangle drawingArea{Rectangle(Point(400, 900), 800, 800, Rectangle::colors.at(Brush::CHECKBOARD), Brush::CHECKBOARD)};
  std::optional<long> whiteKingId{std::optional<long>()};
  std::optional<long> blackKingId{std::optional<long>()};
  std::shared_ptr<Pawn> whiteKing{nullptr};
  std::shared_ptr<Pawn> blackKing{nullptr};
  std::shared_ptr<Pawn> whiteKingThreat{nullptr};
  std::shared_ptr<Pawn> blackKingThreat{nullptr};

public:
  Checkboard();

  // squares
  [[nodiscard]] std::shared_ptr<Squares> getSquares() const;
  [[nodiscard]] std::shared_ptr<Square> getSquare(const std::pair<int, int> &coordinates) const;
  [[nodiscard]] std::pair<bool, std::optional<PawnColor>> getSquareInfo(std::pair<int, int> indexes) const;
  bool markSquares(const Square *square);
  void moveKing(const Square *square);
  void movePawn(Square *square);
  void resetReferenceCounts();
  void setReferenceCounts();
  void setBlockedPawns() const;
  void resetBlockedPawns() const;
  void tryMoveBlockedPawn(const Square *square);
  void secureTheKing(const Square *square);
  void tryBlockCheck(const std::pair<int, int> &pair, const Square *square, const std::shared_ptr<Pawn> &king);

  [[nodiscard]] bool shouldMark(const Rectangle *rect);
  [[nodiscard]] bool amISelected(const Rectangle *rect) const;
  [[nodiscard]] bool amIinDanger(const Rectangle *rect) const;
  [[nodiscard]] bool isKing(PawnColor color, const std::pair<int, int> &coordinates) const;
  void draw() override;
  void update(float ms) override;
  void notify(Square *square);

  // moving square
  [[nodiscard]] const std::shared_ptr<Square> &getMovingSquare() const;
  void setMovingSquare(Point leftBottom, const graphics::Brush &brush, Brush type) const;
  void resetMovingSquare();
  static void checkmate(PawnColor winner);
};

#endif// CHECKBOARD_H