#include <game/Game.h>

Game::Game() = default;

void Game::registerPlayers(const std::pair<Player, Player> &pair) {
  this->players = pair;
}

const Player &Game::getPlayer(PawnColor side) {
  if (this->players->first.getSide() == side) {
    return this->players->first;
  }

  return this->players->second;
}

bool Game::start() {
  // Start game code
  return true;
}

void Game::draw() {
  this->checkboard.draw();
}

void Game::update(float ms) {
  this->checkboard.update(ms);
}

const Checkboard &Game::getCheckboard() const {
  return this->checkboard;
}
