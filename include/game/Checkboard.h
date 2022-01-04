
#ifndef CHECKBOARD_H
#define CHECKBOARD_H

#include <array>
#include "Square.h"

class Checkboard : public Drawable, public Updateable {
public:
  static const std::size_t sideSize = 8;

private:
  using Squares = std::array<std::array<Square, Checkboard::sideSize>, Checkboard::sideSize>;

  Squares *squares = new Squares;

public:
  Checkboard();
  [[nodiscard]] const Squares* getSquares() const;
  void draw() override;
  void update(float ms) override;
  ~Checkboard() override;
};

#endif // CHECKBOARD_H
