
#ifndef PAWN_H
#define PAWN_H

#include "graphics/Drawable.h"
#include "graphics/Updateable.h"
#include "PawnColor.h"
#include "util/paths.h"
#include "Square.h"
#include "graphics/Rectangle.h"

class Square; // break cyclic dependency

class Pawn : public Drawable, public Updateable {
  PawnColor color;
  Square* square_ { nullptr };
  std::optional<Rectangle> drawingArea;
  std::string texture_ { };
  const std::string png { ".png" };

public:
  explicit Pawn(PawnColor color);
  void setSquare(Square* square);
  [[nodiscard]] Square *getSquare() const;
  [[nodiscard]] PawnColor getColor() const;
  void setTexture(std::string texture);
  void draw() override;
  void update(float ms) override = 0;
};

#endif // PAWN_H
