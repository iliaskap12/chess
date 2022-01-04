
#ifndef SQUARE_H
#define SQUARE_H

#include <memory>
#include "graphics/Drawable.h"
#include "graphics/Updateable.h"
#include "Pawn.h"

class Square : public Drawable, public Updateable {
  unsigned short int row {};
  unsigned short int column {};
  std::shared_ptr<Pawn> pawn_{ nullptr };

public:
  Square();
  Square(unsigned short int row, unsigned short int column);
  [[nodiscard]] unsigned short int getRow() const;
  [[nodiscard]] unsigned short int getColumn() const;
  [[nodiscard]] char getColumnAsChar() const;

  void registerPawn(std::shared_ptr<Pawn> pawn);
  void unregisterPawn();
  [[nodiscard]] std::shared_ptr<Pawn> getPawn() const;
  [[nodiscard]] bool hasPawn() const;

  void draw() override;
  void update(float ms) override;
};

#endif // SQUARE_H
