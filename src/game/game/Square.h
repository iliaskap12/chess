#ifndef SQUARE_H
#define SQUARE_H

#include <memory>
#include <graphics/Drawable.h>
#include <graphics/Updateable.h>
#include <graphics/Rectangle.h>
#include "Pawn.h"

class Pawn;// break cyclic dependency

class Square : public Drawable, public Updateable, public std::enable_shared_from_this<Square> {
  unsigned short int row_{0};
  unsigned short int column_{0};
  std::shared_ptr<Pawn> pawn_{nullptr};
  std::shared_ptr<Rectangle> drawingArea{std::make_shared<Rectangle>()};
  unsigned short int whiteDangerReferenceCount_{0};
  unsigned short int blackDangerReferenceCount_{0};

public:
  Square();
  Square(unsigned short int row, unsigned short int column);
  void initialize(Point leftBottom, const graphics::Brush &brush, Brush type, float squareWidth = 150.0f);

  [[nodiscard]] unsigned short int getRow() const;
  [[nodiscard]] unsigned short int getColumn() const;
  void setRow(unsigned short row);
  void setColumn(unsigned short column);
  [[nodiscard]] char getColumnAsChar() const;

  void registerPawn(std::shared_ptr<Pawn> pawn);
  void unregisterPawn();
  [[nodiscard]] std::shared_ptr<Pawn> getPawn() const;
  [[nodiscard]] bool hasPawn() const;

  [[nodiscard]] std::weak_ptr<Rectangle> getDrawingArea() const;

  void draw() override;
  void update(float ms) override;

  friend bool operator==(const Square& lhs, const Square& rhs);
  void increaseDangerReferenceCount(PawnColor color);
  void resetDangerReferenceCount();
  [[nodiscard]] unsigned short int getDangerReferenceCount(PawnColor color) const;
};

#endif // SQUARE_H
