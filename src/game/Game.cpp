#include <game/Game.h>
#include <stdexcept>

Game::Game() = default;

void Game::registerPlayers(const std::pair<Player, Player> &pair) {
  this->players = pair;
}

const Player &Game::getPlayer(PawnColor side) {
  if (this->players->first.getSide() == side) {
    return this->players->first;
  }

  if (this->players->second.getSide() == side) {
    return this->players->second;
  }

  throw std::runtime_error("PawnColor not found.");
}

bool Game::start() {
  // Start game code
  return true;
}

void Game::draw() {
}

void Game::update(float ms) {
}

const Checkboard &Game::getCheckboard() const {
  return this->checkboard;
}
