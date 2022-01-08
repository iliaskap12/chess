
#ifndef PAWN_H
#define PAWN_H

#include "graphics/Drawable.h"
#include "graphics/Updateable.h"
#include "Movable.h"
#include "PawnColor.h"
#include "util/paths.h"
#include "Square.h"
#include "graphics/Rectangle.h"

class Square; // break cyclic dependency
class Movable;

class Pawn : public Drawable, public Updateable, public Movable {
  PawnColor color;
  Square* square_ { nullptr };
  Square* movingSquare { nullptr };
  Rectangle drawingArea { Rectangle() };
  std::string texture_ { };
  const std::string png { ".png" };
  bool shouldMove { false };
  std::pair<float, float> moveSteps {  };
  Square* destination_ { nullptr };
  std::shared_ptr<Pawn> self_{ nullptr };

public:
  explicit Pawn(PawnColor color);
  void setSquare(Square* square);
  [[nodiscard]] Square *getSquare() const;
  [[nodiscard]] PawnColor getColor() const;
  void setTexture(std::string texture);
  void draw() override;
  void update(float ms) override;
  void move(float ms) override;
  [[nodiscard]] virtual std::vector<std::pair<int, int>> getAdvanceableSquares(const std::vector<std::pair<int, int>> &steps, unsigned short int maxSteps) const;
  virtual std::vector<std::pair<int, int>> getAdvanceableSquares() = 0;
  void capture(std::shared_ptr<Pawn> pawn);
  [[nodiscard]] const Rectangle &getDrawingArea() const;
  void moveTo(Square *squarePtr, const std::shared_ptr<Pawn>& self);
};

#endif // PAWN_H
