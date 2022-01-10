
#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "PawnColor.h"

class Player {
private:
  PawnColor side;

public:
  explicit Player(PawnColor side);
  [[nodiscard]] const PawnColor &getSide() const;
};

#endif // PLAYER_H
