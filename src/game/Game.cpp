#include <game/Game.h>
#include <App.h>

Game::Game() = default;

void Game::registerPlayers(const std::pair<Player, Player> &pair) {
  this->players = { pair };
}

const Player &Game::getPlayer(PawnColor side) {
  if (this->players->first.getSide() == side) {
    return this->players->first;
  }

  return this->players->second;
}

bool Game::start() {
  App* app { static_cast<App*>(graphics::getUserData()) };
  app->registerGame(this);

  return true;
}

void Game::draw() {
  this->checkboard->draw();
}

void Game::update(float ms) {
  this->checkboard->update(ms);

  if (const App* app { static_cast<App*>(graphics::getUserData()) }; app->getGame() == nullptr) {
    this->start();
  }
}

std::shared_ptr<Checkboard> Game::getCheckboard() const {
  return this->checkboard;
}

bool Game::isWhiteTurn() const {
  return this->whiteTurn_;
}

void Game::setWhiteTurn(bool whiteTurn) {
  this->whiteTurn_ = { whiteTurn };
}

void Game::end(PawnColor color) {
}
