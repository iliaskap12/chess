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
  bool blocked { false };
  std::shared_ptr<Pawn> blockingPawn { nullptr };

public:
  explicit Pawn(PawnColor color);

  // square
  void setSquare(Square* square);
  static void capture(const std::shared_ptr<Pawn>& pawn);
  [[nodiscard]] Square *getSquare() const;

  // Rectangle
  [[nodiscard]] PawnColor getColor() const;
  void setTexture(std::string texture);
  [[nodiscard]] const std::string &getTexture() const;
  [[nodiscard]] std::shared_ptr<Rectangle> getDrawingArea() const;

  // Interfaces
  void draw() override;
  void update(float ms) override;

  // Moving
  void move(float ms) override;
  void moveTo(Square *squarePtr, const std::shared_ptr<Pawn>& self);
  virtual std::vector<std::pair<int, int>> getAdvanceableSquares() = 0;
  virtual std::vector<std::pair<int, int>> getHoldingSquares() = 0;
  [[nodiscard]] virtual std::vector<std::pair<int, int>>
  getAdvanceableSquares(const std::vector<pair> &steps, unsigned short int maxSteps, bool holding) const;
  [[nodiscard]] std::vector<std::pair<int, int>> correctDirection(std::vector<std::pair<int, int>> steps) const;

  virtual std::shared_ptr<Pawn> getBlockedPawn();
  std::shared_ptr<Pawn> getBlockingPawn();
  [[nodiscard]] bool isBlocked() const;
  void block();
  void unblock();
  void blockedBy(const std::shared_ptr<Pawn> &blocking);
};

#endif // PAWN_H
