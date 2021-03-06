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
  app->registerGame(this->shared_from_this());

  return true;
}

void Game::draw() {
  this->checkboard->draw();
}

void Game::update(float ms) {
  this->checkboard->update(ms);

  if (const App * app{static_cast<App *>(graphics::getUserData())}; app->getGame().expired()) {
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
  this->whiteTurn_ = {whiteTurn};
}

void Game::end(PawnColor color) {
  this->checkmateSound.play();
  this->isGameEnded = {true};
  this->winner.emplace(color);
}

std::pair<bool, std::optional<PawnColor>> Game::hasGameEnded() const {
  return std::make_pair(this->isGameEnded, this->winner);
}

std::optional<PawnColor> Game::isChecked() {
  const auto whiteKing{this->checkboard->getKing(PawnColor::WHITE)};
  const auto blackKing{this->checkboard->getKing(PawnColor::BLACK)};
  if ((!blackKing.expired()) && (!whiteKing.expired())) {
    if (whiteKing.lock()->isChecked()) {
      this->checkedColor = {std::make_optional(PawnColor::WHITE)};
    }
    if (blackKing.lock()->isChecked()) {
      this->checkedColor = {std::make_optional(PawnColor::BLACK)};
    }
    if (!whiteKing.lock()->isChecked() && !blackKing.lock()->isChecked()) {
      this->checkedColor.reset();
    }
  }
  return this->checkedColor;
}

void Game::playCheckSound() const {
  const auto whiteKing{this->checkboard->getKing(PawnColor::WHITE)};
  const auto blackKing{this->checkboard->getKing(PawnColor::BLACK)};
  if ((whiteKing.lock()->isChecked() && this->whiteTurn_) || (blackKing.lock()->isChecked() && !this->whiteTurn_)) {
    this->checkSound.play();
  }
}
