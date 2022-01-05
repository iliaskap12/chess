
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

public:
  Checkboard();
  [[nodiscard]] std::shared_ptr<Squares> getSquares() const;
  void draw() override;
  void update(float ms) override;
};

#endif // CHECKBOARD_H
