#include <game/Player.h>

Player::Player(PawnColor side) : side(side) {}

const PawnColor &Player::getSide() const {
  return this->side;
}
