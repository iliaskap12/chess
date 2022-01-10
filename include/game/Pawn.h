#ifndef PAWN_H
#define PAWN_H

#include "graphics/Drawable.h"
#include "graphics/Updateable.h"
#include "Movable.h"
#include "PawnColor.h"
#include "util/paths.h"
#include "Square.h"
#include "Checkboard.h"
#include "graphics/Rectangle.h"

class Square; // break cyclic dependency
class Checkboard;

class Pawn : public Drawable, public Updateable, public Movable {

  using pair = std::pair<int, int>;

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

protected:
  std::shared_ptr<Checkboard> checkboard { nullptr };

public:
  explicit Pawn(PawnColor color);
  void setSquare(Square* square);
  [[nodiscard]] Square *getSquare() const;
  [[nodiscard]] PawnColor getColor() const;
  void setTexture(std::string texture);
  [[nodiscard]] const std::string &getTexture() const;
  void draw() override;
  void update(float ms) override;
  void move(float ms) override;
  [[nodiscard]] virtual std::vector<std::pair<int, int>> getAdvanceableSquares(const std::vector<pair> &steps, unsigned short int maxSteps);
  virtual std::vector<std::pair<int, int>> getAdvanceableSquares() = 0;
  static void capture(const std::shared_ptr<Pawn>& pawn);
  [[nodiscard]] std::shared_ptr<Rectangle> getDrawingArea() const;
  void moveTo(Square *squarePtr, const std::shared_ptr<Pawn>& self);
};

#endif // PAWN_H
