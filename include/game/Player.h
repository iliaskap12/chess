
#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "PawnColor.h"

class Player {
private:
  std::string name;
  PawnColor side;

public:
  Player(std::string name, PawnColor side);
  [[nodiscard]] const PawnColor &getSide() const;
};

#endif // PLAYER_H
