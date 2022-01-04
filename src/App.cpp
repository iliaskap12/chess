//
// Created by ilias on 2/1/22.
//

#include <App.h>

App::App() = default;

std::shared_ptr<Screen> App::getScreen() const {
  return this->activeScreen;
}

std::unique_ptr<Game> App::getGame() const {
  if (!this->game) {
    return nullptr;
  }
  return std::make_unique<Game>(*this->game);
}

void App::createNewGame() {
  this->game = Game();
}

void App::run() {
  graphics::createWindow(1024, 768, "Chess");
  graphics::setUserData(this);
  graphics::setDrawFunction(std::bind_front(&App::draw, this));
  graphics::setUpdateFunction(std::bind_front(&App::update, this));
  graphics::setCanvasSize(100.0f, 100.0f);
  graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

  graphics::startMessageLoop();
  graphics::destroyWindow();
}

void App::draw() {
  if (this->game) {
    this->game.draw();
  }
}

void App::update(float ms) {

}

