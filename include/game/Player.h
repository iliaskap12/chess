
#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Side.h"

class Player {
private:
  std::string name;
  Side side;

public:
  Player(std::string name, Side side);
  [[nodiscard]] const Side &getSide() const;
};

#endif // PLAYER_H
