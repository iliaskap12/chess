#ifndef PAWN_H
#define PAWN_H

#include <graphics/Drawable.h>
#include <graphics/Updateable.h>
#include "Movable.h"
#include "PawnColor.h"
#include "paths.h"
#include "Square.h"
#include <graphics/Rectangle.h>
#include <sounds/ClickSound.h>
#include <sounds/MoveSound.h>
#include <sounds/CaptureSound.h>

class Square;// break cyclic dependency

class Pawn : public Drawable,
             public Updateable,
             public Movable,
             public std::enable_shared_from_this<Pawn> {

  using pair = std::pair<int, int>;

  PawnColor color;
  std::shared_ptr<Square> square_{nullptr};
  std::shared_ptr<Square> movingSquare{nullptr};
  std::shared_ptr<Rectangle> drawingArea{std::make_shared<Rectangle>()};
  std::string texture_{};
  const std::string png{".png"};
  bool shouldMove{false};
  std::pair<float, float> moveSteps{};
  std::shared_ptr<Square> destination_{nullptr};
  std::shared_ptr<Pawn> self_{nullptr};
  bool blocked{false};
  std::weak_ptr<Pawn> blockingPawn{std::weak_ptr<Pawn>()};
  ClickSound clickSound{ClickSound()};
  MoveSound moveSound{MoveSound()};
  CaptureSound captureSound{CaptureSound()};

public:
  explicit Pawn(PawnColor color);

  // square
  void setSquare(const std::shared_ptr<Square> &square);
  void capture(const std::shared_ptr<Pawn> &pawn);
  [[nodiscard]] std::weak_ptr<Square> getSquare() const;

  // Rectangle
  [[nodiscard]] PawnColor getColor() const;
  void setTexture(std::string texture);
  [[nodiscard]] const std::string &getTexture() const;
  [[nodiscard]] std::weak_ptr<Rectangle> getDrawingArea() const;

  // Interfaces
  void draw() override;
  void update(float ms) override;

  // Moving
  void move(float ms) override;
  void moveTo(const std::shared_ptr<Square> &squarePtr, const std::shared_ptr<Pawn> &self);
  virtual std::vector<std::pair<int, int>> getAdvanceableSquares() = 0;
  virtual std::vector<std::pair<int, int>> getHoldingSquares() = 0;
  [[nodiscard]] virtual std::vector<std::pair<int, int>>
  getAdvanceableSquares(const std::vector<pair> &steps, unsigned short int maxSteps, bool holding) const;
  [[nodiscard]] std::vector<std::pair<int, int>> correctDirection(std::vector<std::pair<int, int>> steps) const;

  virtual std::weak_ptr<Pawn> getBlockedPawn();
  std::weak_ptr<Pawn> getBlockingPawn();
  [[nodiscard]] bool isBlocked() const;
  void block();
  void unblock();
  void blockedBy(const std::shared_ptr<Pawn> &blocking);
  void playCaptureSound();
};

#endif // PAWN_H
