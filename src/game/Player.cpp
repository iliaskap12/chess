#include <game/Player.h>
#include <utility>

Player::Player(std::string name, PawnColor side) : side(side) {
  name = std::move(name);
}
const PawnColor &Player::getSide() const {
  return this->side;
}
