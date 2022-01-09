#include <game/Player.h>
#include <utility>

Player::Player(std::string name, PawnColor side) : name(std::move(name)), side(side) {}

const PawnColor &Player::getSide() const {
  return this->side;
}
