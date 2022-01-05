#include <graphics/PlayingScreen.h>

PlayingScreen::PlayingScreen() = default;

std::shared_ptr<Game> PlayingScreen::getGame() const {
  return this->game;
}

void PlayingScreen::draw() {
  this->game->draw();
}

void PlayingScreen::update(float ms) {
  this->game->update(ms);
}
