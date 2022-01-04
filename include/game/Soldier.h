
#ifndef SOLDIER_H
#define SOLDIER_H

#include "PawnColor.h"
#include "Pawn.h"

class Soldier : public Pawn {

public:
  explicit Soldier(PawnColor color);
  void draw() override;
  void update(float ms) override;
};

#endif // SOLDIER_H
