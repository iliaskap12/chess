#include <App.h>
#include <functional>
#include <util/paths.h>
#include "graphics/PlayingScreen.h"

App::App() = default;

std::shared_ptr<Screen> App::getScreen() const {
  return this->activeScreen;
}

void App::run() {
  graphics::createWindow(1920, 1080, "Chess");
  graphics::preloadBitmaps(paths::getImagesPath());

  graphics::setUserData(this);
  graphics::setDrawFunction(std::bind_front(&App::draw, this));
  graphics::setUpdateFunction(std::bind_front(&App::update, this));
  graphics::setCanvasSize(3200, 1900);
  graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);
  graphics::setFont(paths::getFontsPath() + "typography-times.ttf");
  Rectangle::populateBrushes();
  this->activeScreen = {std::make_shared<OpeningScreen>()};

  graphics::startMessageLoop();
  graphics::destroyWindow();
}

void App::draw() {
  if (this->activeScreen != nullptr) {
    this->activeScreen->draw();
  }
}

void App::update(float ms) {
  if (this->activeScreen != nullptr) {
    this->activeScreen->update(ms);
  }
}

void App::changeScreen(const std::shared_ptr<Screen> &screen) {
  this->activeScreen = {nullptr};
  this->game_.reset();
  this->activeScreen = {screen};
}

void App::registerGame(const std::shared_ptr<Game> &game) {
  this->game_ = {game};
}

std::weak_ptr<Game> App::getGame() const {
  if (this->game_.lock() == nullptr) {
    if (const auto playingScreen{std::dynamic_pointer_cast<PlayingScreen>(this->activeScreen)}; nullptr != playingScreen) {
      return playingScreen->getGame();
    }
  }
  return this->game_;
}
