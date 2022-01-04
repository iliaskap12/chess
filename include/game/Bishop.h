
#ifndef BISHOP_H
#define BISHOP_H

#include "Pawn.h"

class Bishop : public Pawn {

public:
  explicit Bishop(PawnColor color);
  void draw() override;
  void update(float ms) override;
};


#endif // BISHOP_H
