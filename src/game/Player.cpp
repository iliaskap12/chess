#include <game/Player.h>
#include <utility>

Player::Player(std::string name, Side side) : side(side) {
  name = std::move(name);
}
const Side &Player::getSide() const {
  return this->side;
}
