
#ifndef CHECKBOARD_H
#define CHECKBOARD_H

#include <array>
#include "Square.h"

class Checkboard : public Drawable, public Updateable {
public:
  static const std::size_t sideSize = 8;

private:
  using Squares = std::array<std::array<std::shared_ptr<Square>, Checkboard::sideSize>, Checkboard::sideSize>;

  std::shared_ptr<Squares> squares = std::make_shared<Squares>();
  std::vector<std::shared_ptr<Square>> markedSquares { std::vector<std::shared_ptr<Square>>() };
  std::shared_ptr<Pawn> markedPawn { nullptr };
  std::shared_ptr<Square> movingSquare_{ std::make_shared<Square>(10, 10) };
  std::shared_ptr<Rectangle> selectedPawn { nullptr };
  Rectangle drawingArea { Rectangle(Point(200, 900), 800, 800, Rectangle::colors.at(Brush::CHECKBOARD), Brush::CHECKBOARD) };

public:
  Checkboard();
  [[nodiscard]] std::shared_ptr<Squares> getSquares() const;
  [[nodiscard]] std::pair<bool, std::optional<PawnColor>> getSquareInfo(std::pair<int, int> indexes) const;
  void notify(Square *square);
  [[nodiscard]] bool shouldMark(const Rectangle* rect);
  void draw() override;
  void update(float ms) override;
  [[nodiscard]] const std::shared_ptr<Square> &getMovingSquare() const;
  void setMovingSquare(Point leftBottom, const graphics::Brush &brush, Brush type) const;
  void resetMovingSquare();
  bool amISelected(const Rectangle *rect) const;
};

#endif // CHECKBOARD_H
